using System;
using System.Collections;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace Scintilla
{

	public class ScintillaControl : Control
	{

		#region "custom code"
		public ScintillaControl()
		{
			try
			{
				IntPtr lib = WinAPI.LoadLibrary("SciLexer.dll");
				hwndScintilla = WinAPI.CreateWindowEx(0, "Scintilla","", WS_CHILD_VISIBLE_TABSTOP, 0,0,this.Width,this.Height,this.Handle ,0, new IntPtr(0) ,null);
				_directPointer = (int)SlowPerform(2185, 0, 0);
				Resize+=( new EventHandler( doResize ) );
				CodePage = 65001; // Set to Unicode from the getgo.

				_directPointer = DirectPointer;
			}
			catch( Exception x )
			{
				throw x;
			}

			_indexMarginType = new Indexed.MarginType(this);
			_indexIndicatorStyle = new Indexed.IndicatorStyle(this);

		}

		public void doResize(object sender, EventArgs e)
		{
			SetWindowPos(this.hwndScintilla, 0, base.Location.X ,  base.Location.Y , base.Width, base.Height, 0);
		} 

		public override string Text
		{
			get
			{
				return GetText(Length);
			}

			set
			{
				CodePage = 65001;
				SetText( value );
			}

		}

		public virtual void AddIgnoredKey(Shortcut shortcutkey)
		{
			int key = (int)shortcutkey;
			this.ignoredKeys.Add(key, key);
		}
 
		public virtual void AddIgnoredKey(System.Windows.Forms.Keys key, System.Windows.Forms.Keys modifier)
		{
			this.ignoredKeys.Add((int)key + (int)modifier, (int)key + (int)modifier);
		}
 
		protected virtual void addShortcuts(Menu m)
		{
			foreach( MenuItem mi in m.MenuItems )
			{
				if( mi.Shortcut != Shortcut.None )
					AddIgnoredKey(mi.Shortcut );
				if( mi.MenuItems.Count > 0 )
					addShortcuts( mi );
			}
		}
 
		public virtual void AddShortcutsFromForm(Form parentForm)
		{
			if ((parentForm != null) && (parentForm.Menu != null))
			{
				addShortcuts(parentForm.Menu);
 			}
		}

		public override bool PreProcessMessage(ref Message m)
		{
			switch( m.Msg  )
			{
				case WM_KEYDOWN:
				{
					if( ignoredKeys.ContainsKey( (int)Control.ModifierKeys+(int)m.WParam) )
						return base.PreProcessMessage(ref m );
				}
				break;
			}
			return false;
		}

		public Scintilla.Configuration.Scintilla Configuration
		{
			get
			{
				return this._configuration;
			}
			set
			{
				this._configuration = value;
			}
		}
 
		public String ConfigurationLanguage
		{
			set
			{
				if( value == null || value.Equals("") )
					return;

				Scintilla.Configuration.Language lang = _configuration.GetLanguage( value );
				if( lang == null )
					return;

				StyleClearAll();
				System.Type enumtype = typeof(Enums.Lexer);
				try
				{
					Lexer =  (int)Enum.Parse( typeof(Enums.Lexer) , lang.lexer.name , true );
				}
				catch( Exception )
				{
					// try by key instead
					Lexer = lang.lexer.key;
				}
				if( lang.lexer.stylebits > 0 ) 
					StyleBits = lang.lexer.stylebits;

				for( int j =0 ; j < lang.usestyles.Length ; j++)
				{
					Scintilla.Configuration.UseStyle usestyle = lang.usestyles[j];

					if(usestyle.HasForegroundColor)
						StyleSetFore( usestyle.key , usestyle.ForegroundColor );
					if(usestyle.HasBackgroundColor )
						StyleSetBack( usestyle.key , usestyle.BackgroundColor );
					if( usestyle.HasFontName )
						StyleSetFont( usestyle.key , usestyle.FontName );
					if( usestyle.HasFontSize )
						StyleSetSize( usestyle.key , usestyle.FontSize );
					if( usestyle.HasBold )
						StyleSetBold( usestyle.key , usestyle.IsBold );
					if( usestyle.HasItalics )
						StyleSetItalic( usestyle.key , usestyle.IsItalics );
					if( usestyle.HasEolFilled)
						StyleSetEOLFilled( usestyle.key , usestyle.IsEolFilled);
				}

				// clear the keywords lists	
				for( int j=0; j < 9; j++ )
					KeyWords(j, "" );

				for( int j=0; j < lang.usekeywords.Length ; j++ )
				{
					Scintilla.Configuration.UseKeyword usekeyword = lang.usekeywords[j];
					Scintilla.Configuration.KeywordClass kc = _configuration.GetKeywordClass( usekeyword.cls );
					if(kc != null )
						KeyWords(usekeyword.key, kc.val);
				}
			}
		}

		#endregion

		#region "New,Extended Interface"
		/// <summary>
		/// Are white space characters currently visible?
		/// Returns one of SCWS_* constants.
		/// </summary>
		public Enums.WhiteSpace ViewWhitespace
		{
			get
			{
				return (Enums.WhiteSpace)ViewWS;
			}
			set
			{
				ViewWS = (int)value;
			}
		}

		/// <summary>
		/// Retrieve the current end of line mode - one of CRLF, CR, or LF.
		/// </summary>
		public Enums.EndOfLine EndOfLineMode
		{
			get 
			{
				return (Enums.EndOfLine)EOLMode;
			}
			set
			{
				EOLMode=(int)value;
			}
		}	

		/// <summary>
		/// Convert all line endings in the document to one mode.
		/// </summary>
		public void ConvertEOLs(Enums.EndOfLine eolMode)
		{
			ConvertEOLs( (int) eolMode );
		}	

		/// <summary>
		/// Set the symbol used for a particular marker number.
		/// </summary>
		public void MarkerDefine(int markerNumber, Enums.MarkerSymbol markerSymbol )
		{
			MarkerDefine(markerNumber , (int)markerSymbol);
		}	

		/// <summary>
		/// The type of a margin.
		/// </summary>
		public Indexed.MarginType MarginType
		{
			get
			{
				return _indexMarginType;
			}
		}

		/// <summary>
		/// The type of a margin.
		/// </summary>
		public Indexed.IndicatorStyle IndicatorStyle
		{
			get
			{
				return _indexIndicatorStyle;
			}
		}

		/// <summary>
		/// Set the character set of the font in a style.
		/// </summary>
		public void StyleSetCharacterSet(int style, Enums.CharacterSet characterSet )
		{
			StyleSetCharacterSet( style, (int)characterSet );
		}	

		/// <summary>
		/// Set a style to be mixed case, or to force upper or lower case.
		/// </summary>
		public void StyleSetCase(int style, Enums.CaseVisible caseForce )
		{
			StyleSetCase( style, (int)caseForce );
		}	



		#endregion


		#region "Constants"
		private static uint WS_CHILD = (uint)0x40000000L;
		private static uint WS_VISIBLE =(uint)0x10000000L;
		private static uint WS_TABSTOP =(uint)0x00010000L;
		private static uint WS_CHILD_VISIBLE_TABSTOP = WS_CHILD|WS_VISIBLE|WS_TABSTOP;
		private static int  WM_NOTIFY = 0x004e;
		private const  int WM_KEYDOWN = 0x0100;
		#endregion

		#region ".NET side Data"
		private Hashtable ignoredKeys = new Hashtable(); 
		private IntPtr hwndScintilla; 
		Scintilla.Configuration.Scintilla _configuration;
		private int _directPointer;

		private Indexed.MarginType _indexMarginType;
		private Indexed.IndicatorStyle _indexIndicatorStyle;
		#endregion

		#region "scintilla-event-members"
        public event StyleNeededHandler StyleNeeded;
        public event CharAddedHandler CharAdded;
        public event SavePointReachedHandler SavePointReached;
        public event SavePointLeftHandler SavePointLeft;
        public event ModifyAttemptROHandler ModifyAttemptRO;
        public event KeyHandler Key;
        public new event DoubleClickHandler DoubleClick;
        public event UpdateUIHandler UpdateUI;
        public event ModifiedHandler Modified;
        public event MacroRecordHandler MacroRecord;
        public event MarginClickHandler MarginClick;
        public event NeedShownHandler NeedShown;
        public event PaintedHandler Painted;
        public event UserListSelectionHandler UserListSelection;
        public event URIDroppedHandler URIDropped;
        public event DwellStartHandler DwellStart;
        public event DwellEndHandler DwellEnd;
        public event ZoomHandler Zoom;
        public event HotSpotClickHandler HotSpotClick;
        public event HotSpotDoubleClickHandler HotSpotDoubleClick;
        public event CallTipClickHandler CallTipClick;
		#endregion

		#region "Custom Modified Events"
		public event TextInsertedHandler TextInserted ;
		public event TextDeletedHandler TextDeleted ;
		public event FoldChangedHandler FoldChanged ;
		public event UserPerformedHandler UserPerformed ;
		public event UndoPerformedHandler UndoPerformed ;
		public event RedoPerformedHandler RedoPerformed ;
		public event LastStepInUndoRedoHandler LastStepInUndoRedo ;
		public event MarkerChangedHandler MarkerChanged ;
		public event BeforeInsertHandler BeforeInsert ;
		public event BeforeDeleteHandler BeforeDelete ;
		public new event StyleChangedHandler StyleChanged;
		#endregion

		#region "Scintilla Jumppoint"
		[DllImport("user32.dll")] 
		public static extern int SendMessage( 
			int hWnd,      // handle to destination window 
			uint Msg,     // message 
			int wParam,  // first message parameter 
			int lParam   // second message parameter 
			); 

		[DllImport("user32.dll")] 
		public static extern int SetWindowPos(          
			IntPtr hWnd,
			int hWndInsertAfter,
			int X,
			int Y,
			int cx,
			int cy,
			int uFlags
			);

		[DllImport("scilexer.dll",EntryPoint="Scintilla_DirectFunction")]
		public static extern int Perform(
			int directPointer,
			UInt32 message,
			UInt32 wParam,
			UInt32 lParam);

		public UInt32 SlowPerform( UInt32 message,UInt32 wParam,UInt32 lParam)
		{
			return (UInt32)SendMessage( (int)hwndScintilla, message , (int)wParam , (int)lParam);
		}

		public UInt32 FastPerform( UInt32 message,UInt32 wParam,UInt32 lParam)
		{
			return (UInt32)Perform ((int)_directPointer , message , (UInt32)wParam , (UInt32)lParam);
		}

		public UInt32 SPerform( UInt32 message,UInt32 wParam,UInt32 lParam)
		{
			return (UInt32)Perform ((int)_directPointer , message , (UInt32)wParam , (UInt32)lParam);
		}

		#endregion

		#region "Window Proc"
		protected override void WndProc( ref System.Windows.Forms.Message m )
		{
			if( m.Msg == WM_NOTIFY )
			{
				SCNotification scn = (SCNotification)Marshal.PtrToStructure(m.LParam, typeof(SCNotification));

				if( scn.nmhdr.hwndFrom == hwndScintilla )
					switch( scn.nmhdr.code )
					{
							#region "scintilla-event-dispatch"

						case (uint)ScintillaEvents.styleneeded:
							if( StyleNeeded!=null )
								StyleNeeded( this ,scn.position );
							break;

						case (uint)ScintillaEvents.charadded:
							if( CharAdded!=null )
								CharAdded( this ,scn.ch );
							break;

						case (uint)ScintillaEvents.savepointreached:
							if( SavePointReached!=null )
								SavePointReached( this  );
							break;

						case (uint)ScintillaEvents.savepointleft:
							if( SavePointLeft!=null )
								SavePointLeft( this  );
							break;

						case (uint)ScintillaEvents.modifyattemptro:
							if( ModifyAttemptRO!=null )
								ModifyAttemptRO( this  );
							break;

						case (uint)ScintillaEvents.key:
							if( Key!=null )
								Key( this ,scn.ch,scn.modifiers );
							break;

					case (uint)ScintillaEvents.doubleclick:
						if( DoubleClick!=null )
							DoubleClick( this  );
						break;

						case (uint)ScintillaEvents.updateui:
							if( UpdateUI!=null )
								UpdateUI( this  );
							break;

						case (uint)ScintillaEvents.macrorecord:
							if( MacroRecord!=null )
								MacroRecord( this ,scn.message,scn.wParam,scn.lParam );
							break;

						case (uint)ScintillaEvents.marginclick:
							if( MarginClick!=null )
								MarginClick( this ,scn.modifiers,scn.position,scn.margin );
							break;

						case (uint)ScintillaEvents.needshown:
							if( NeedShown!=null )
								NeedShown( this ,scn.position,scn.length );
							break;

						case (uint)ScintillaEvents.painted:
							if( Painted!=null )
								Painted( this  );
							break;

						case (uint)ScintillaEvents.userlistselection:
							if( UserListSelection!=null )
								UserListSelection( this ,scn.listType,System.Runtime.InteropServices.Marshal.PtrToStringAuto(scn.text) );
							break;

						case (uint)ScintillaEvents.uridropped:
							if( URIDropped!=null )
								URIDropped( this ,System.Runtime.InteropServices.Marshal.PtrToStringAuto(scn.text) );
							break;

						case (uint)ScintillaEvents.dwellstart:
							if( DwellStart!=null )
								DwellStart( this ,scn.position );
							break;

						case (uint)ScintillaEvents.dwellend:
							if( DwellEnd!=null )
								DwellEnd( this ,scn.position );
							break;

						case (uint)ScintillaEvents.zoom:
							if( Zoom!=null )
								Zoom( this  );
							break;

						case (uint)ScintillaEvents.hotspotclick:
							if( HotSpotClick!=null )
								HotSpotClick( this ,scn.modifiers,scn.position );
							break;

						case (uint)ScintillaEvents.hotspotdoubleclick:
							if( HotSpotDoubleClick!=null )
								HotSpotDoubleClick( this ,scn.modifiers,scn.position );
							break;

						case (uint)ScintillaEvents.calltipclick:
							if( CallTipClick!=null )
								CallTipClick( this ,scn.position );
							break;
							#endregion

						case (uint)ScintillaEvents.modified:
							if(( scn.modificationType & (uint)Enums.ModificationFlags.inserttext ) >0 )
								if( TextInserted!= null ) 
									TextInserted( this ,scn.position ,scn.length , scn.linesAdded );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.deletetext )>0 )
								if( TextDeleted != null ) 
									TextDeleted( this ,scn.position ,scn.length , scn.linesAdded  );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.changestyle )>0 )
								if( StyleChanged != null)
									StyleChanged( this ,scn.position ,scn.length );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.changefold )>0 )
								if( FoldChanged != null ) 
									FoldChanged( this , scn.line , scn.foldLevelNow , scn.foldLevelPrev );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.user )>0 )
								if( UserPerformed != null ) 
									UserPerformed( this );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.undo )>0 )
								if( UndoPerformed != null ) 
									UndoPerformed( this );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.redo )>0 )
								if( RedoPerformed != null ) 
									RedoPerformed( this);
							if(( scn.modificationType & (uint)Enums.ModificationFlags.stepinundoredo  )>0 )
								if( LastStepInUndoRedo != null ) 
									LastStepInUndoRedo( this );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.changemarker )>0 )
								if( MarkerChanged != null ) 
									MarkerChanged( this , scn.line );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.beforeinsert )>0 )
								if( BeforeInsert != null ) 
									BeforeInsert( this , scn.position , scn.length  );
							if(( scn.modificationType & (uint)Enums.ModificationFlags.beforedelete )>0 )
								if( BeforeDelete != null ) 
									BeforeDelete( this , scn.position , scn.length );

							if( Modified != null ) 
								Modified( this ,scn.position,scn.modificationType,System.Runtime.InteropServices.Marshal.PtrToStringAuto(scn.text),scn.length,scn.linesAdded,scn.line,scn.foldLevelNow,scn.foldLevelPrev );
							break;
	
					}

			}
			else
				base.WndProc( ref m );			
		}
		#endregion

		#region "scintilla-properties"

		/// <summary>
		/// Are there any redoable actions in the undo history?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN09</remarks>
		public bool CanRedo
		{
			get 
			{
				return SPerform(2016, 0, 0)!=0?true:false;
			}
		}	

		/// <summary>
		/// Is there an auto-completion list visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN09</remarks>
		public bool IsAutoCActive
		{
			get 
			{
				return SPerform(2102, 0, 0)!=0?true:false;
			}
		}	

		/// <summary>
		/// Retrieve the position of the caret when the auto-completion list was displayed.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN10</remarks>
		public int AutoCPosStart
		{
			get 
			{
				return (int)SPerform(2103, 0, 0);
			}
		}	

		/// <summary>
		/// Will a paste succeed?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN09</remarks>
		public bool CanPaste
		{
			get 
			{
				return SPerform(2173, 0, 0)!=0?true:false;
			}
		}	

		/// <summary>
		/// Are there any undoable actions in the undo history?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN09</remarks>
		public bool CanUndo
		{
			get 
			{
				return SPerform(2174, 0, 0)!=0?true:false;
			}
		}	

		/// <summary>
		/// Is there an active call tip?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN09</remarks>
		public bool IsCallTipActive
		{
			get 
			{
				return SPerform(2202, 0, 0)!=0?true:false;
			}
		}	

		/// <summary>
		/// Retrieve the position where the caret was before displaying the call tip.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN10</remarks>
		public int CallTipPosStart
		{
			get 
			{
				return (int)SPerform(2203, 0, 0);
			}
		}	

		/// <summary>
		/// Create a new document object.
		/// Starts with reference count of 1 and not selected into editor.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN10</remarks>
		public int CreateDocument
		{
			get 
			{
				return (int)SPerform(2375, 0, 0);
			}
		}	

		/// <summary>
		/// Get currently selected item position in the auto-completion list
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN10</remarks>
		public int AutoCGetCurrent
		{
			get 
			{
				return (int)SPerform(2445, 0, 0);
			}
		}	

		/// <summary>
		/// Returns the number of characters in the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int Length
		{
			get 
			{
				return (int)SPerform(2006, 0, 0);
			}
		}	

		/// <summary>
		/// Returns the character byte at the position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int CharAt(int pos)
		{
			return (int)SPerform(2007, (uint)pos, 0);
		}	

		/// <summary>
		/// Returns the position of the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CurrentPos
		{
			get 
			{
				return (int)SPerform(2008, 0, 0);
			}
			set
			{
				SPerform(2141, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the position of the opposite end of the selection to the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int AnchorPosition
		{
			get 
			{
				return (int)SPerform(2009, 0, 0);
			}
			set
			{
				SPerform(2026, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the style byte at the position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int StyleAt(int pos)
		{
			return (int)SPerform(2010, (uint)pos, 0);
		}	

		/// <summary>
		/// Is undo history being collected?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsUndoCollection
		{
			get 
			{
				return SPerform(2019, 0, 0)!=0;
			}
			set
			{
				SPerform(2012 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Are white space characters currently visible?
		/// Returns one of SCWS_* constants.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int ViewWS
		{
			get 
			{
				return (int)SPerform(2020, 0, 0);
			}
			set
			{
				SPerform(2021, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the position of the last correctly styled character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int EndStyled
		{
			get 
			{
				return (int)SPerform(2028, 0, 0);
			}
		}	

		/// <summary>
		/// Retrieve the current end of line mode - one of CRLF, CR, or LF.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int EOLMode
		{
			get 
			{
				return (int)SPerform(2030, 0, 0);
			}
			set
			{
				SPerform(2031, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Is drawing done first into a buffer or direct to the screen?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsBufferedDraw
		{
			get 
			{
				return SPerform(2034, 0, 0)!=0;
			}
			set
			{
				SPerform(2035 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve the visible size of a tab.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int TabWidth
		{
			get 
			{
				return (int)SPerform(2121, 0, 0);
			}
			set
			{
				SPerform(2036, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the type of a margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetMarginTypeN( int margin )
		{
			return (int)SPerform(2241,(uint)margin, 0);
		}

		/// <summary>
		/// Set a margin to be either numeric or symbolic.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetMarginTypeN( int margin, int marginType  )
		{
			SPerform(2240, (uint)margin , (uint)marginType);
		}	

		/// <summary>
		/// Retrieve the width of a margin in pixels.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetMarginWidthN( int margin )
		{
			return (int)SPerform(2243,(uint)margin, 0);
		}

		/// <summary>
		/// Set the width of a margin to a width expressed in pixels.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetMarginWidthN( int margin, int pixelWidth  )
		{
			SPerform(2242, (uint)margin , (uint)pixelWidth);
		}	

		/// <summary>
		/// Retrieve the marker mask of a margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetMarginMaskN( int margin )
		{
			return (int)SPerform(2245,(uint)margin, 0);
		}

		/// <summary>
		/// Set a mask that determines which markers are displayed in a margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetMarginMaskN( int margin, int mask  )
		{
			SPerform(2244, (uint)margin , (uint)mask);
		}	

		/// <summary>
		/// Retrieve the mouse click sensitivity of a margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN31</remarks>
		public bool MarginSensitiveN( int margin )
		{
			return SPerform(2247,(uint)margin, 0)!=0;
		}

		/// <summary>
		/// Make a margin sensitive or insensitive to mouse clicks.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN32</remarks>
		public void MarginSensitiveN( int margin, bool sensitive  )
		{
			SPerform(2246, (uint)margin , (uint)(sensitive?1:0));
		}	

		/// <summary>
		/// Get the time in milliseconds that the caret is on and off.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CaretPeriod
		{
			get 
			{
				return (int)SPerform(2075, 0, 0);
			}
			set
			{
				SPerform(2076, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the style of an indicator.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetIndicStyle( int indic )
		{
			return (int)SPerform(2081,(uint)indic, 0);
		}

		/// <summary>
		/// Set an indicator to plain, squiggle or TT.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetIndicStyle( int indic, int style  )
		{
			SPerform(2080, (uint)indic , (uint)style);
		}	

		/// <summary>
		/// Retrieve the foreground colour of an indicator.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetIndicFore( int indic )
		{
			return (int)SPerform(2083,(uint)indic, 0);
		}

		/// <summary>
		/// Set the foreground colour of an indicator.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetIndicFore( int indic, int fore  )
		{
			SPerform(2082, (uint)indic , (uint)fore);
		}	

		/// <summary>
		/// Retrieve number of bits in style bytes used to hold the lexical state.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int StyleBits
		{
			get 
			{
				return (int)SPerform(2091, 0, 0);
			}
			set
			{
				SPerform(2090, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the extra styling information for a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetLineState( int line )
		{
			return (int)SPerform(2093,(uint)line, 0);
		}

		/// <summary>
		/// Used to hold extra styling information for each line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetLineState( int line, int state  )
		{
			SPerform(2092, (uint)line , (uint)state);
		}	

		/// <summary>
		/// Retrieve the last line number that has line state.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int MaxLineState
		{
			get 
			{
				return (int)SPerform(2094, 0, 0);
			}
		}	

		/// <summary>
		/// Is the background of the line containing the caret in a different colour?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsCaretLineVisible
		{
			get 
			{
				return SPerform(2095, 0, 0)!=0;
			}
			set
			{
				SPerform(2096 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Get the colour of the background of the line containing the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CaretLineBack
		{
			get 
			{
				return (int)SPerform(2097, 0, 0);
			}
			set
			{
				SPerform(2098, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the auto-completion list separator character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int AutoCSeparator
		{
			get 
			{
				return (int)SPerform(2107, 0, 0);
			}
			set
			{
				SPerform(2106, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve whether auto-completion cancelled by backspacing before start.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsAutoCGetCancelAtStart
		{
			get 
			{
				return SPerform(2111, 0, 0)!=0;
			}
			set
			{
				SPerform(2110 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve whether a single item auto-completion list automatically choose the item.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsAutoCGetChooseSingle
		{
			get 
			{
				return SPerform(2114, 0, 0)!=0;
			}
			set
			{
				SPerform(2113 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve state of ignore case flag.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsAutoCGetIgnoreCase
		{
			get 
			{
				return SPerform(2116, 0, 0)!=0;
			}
			set
			{
				SPerform(2115 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve whether or not autocompletion is hidden automatically when nothing matches.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsAutoCGetAutoHide
		{
			get 
			{
				return SPerform(2119, 0, 0)!=0;
			}
			set
			{
				SPerform(2118 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve whether or not autocompletion deletes any word characters
		/// after the inserted text upon completion.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsAutoCGetDropRestOfWord
		{
			get 
			{
				return SPerform(2271, 0, 0)!=0;
			}
			set
			{
				SPerform(2270 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve the auto-completion list type-separator character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int AutoCTypeSeparator
		{
			get 
			{
				return (int)SPerform(2285, 0, 0);
			}
			set
			{
				SPerform(2286, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve indentation size.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int Indent
		{
			get 
			{
				return (int)SPerform(2123, 0, 0);
			}
			set
			{
				SPerform(2122, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve whether tabs will be used in indentation.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsUseTabs
		{
			get 
			{
				return SPerform(2125, 0, 0)!=0;
			}
			set
			{
				SPerform(2124 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve the number of columns that a line is indented.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetLineIndentation( int line )
		{
			return (int)SPerform(2127,(uint)line, 0);
		}

		/// <summary>
		/// Change the indentation of a line to a number of columns.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetLineIndentation( int line, int indentSize  )
		{
			SPerform(2126, (uint)line , (uint)indentSize);
		}	

		/// <summary>
		/// Retrieve the position before the first non indentation character on a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int LineIndentPosition(int line)
		{
			return (int)SPerform(2128, (uint)line, 0);
		}	

		/// <summary>
		/// Retrieve the column number of a position, taking tab width into account.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int Column(int pos)
		{
			return (int)SPerform(2129, (uint)pos, 0);
		}	

		/// <summary>
		/// Is the horizontal scroll bar visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsHScrollBar
		{
			get 
			{
				return SPerform(2131, 0, 0)!=0;
			}
			set
			{
				SPerform(2130 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Are the indentation guides visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsIndentationGuides
		{
			get 
			{
				return SPerform(2133, 0, 0)!=0;
			}
			set
			{
				SPerform(2132 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Get the highlighted indentation guide column.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int HighlightGuide
		{
			get 
			{
				return (int)SPerform(2135, 0, 0);
			}
			set
			{
				SPerform(2134, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the position after the last visible characters on a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int LineEndPosition(int line)
		{
			return (int)SPerform(2136, (uint)line, 0);
		}	

		/// <summary>
		/// Get the code page used to interpret the bytes of the document as characters.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CodePage
		{
			get 
			{
				return (int)SPerform(2137, 0, 0);
			}
			set
			{
				SPerform(2037, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the foreground colour of the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CaretFore
		{
			get 
			{
				return (int)SPerform(2138, 0, 0);
			}
			set
			{
				SPerform(2069, (uint)value , 0);
			}
		}	

		/// <summary>
		/// In palette mode?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsUsePalette
		{
			get 
			{
				return SPerform(2139, 0, 0)!=0;
			}
			set
			{
				SPerform(2039 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// In read-only mode?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsReadOnly
		{
			get 
			{
				return SPerform(2140, 0, 0)!=0;
			}
			set
			{
				SPerform(2171 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Returns the position at the start of the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int SelectionStart
		{
			get 
			{
				return (int)SPerform(2143, 0, 0);
			}
			set
			{
				SPerform(2142, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the position at the end of the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int SelectionEnd
		{
			get 
			{
				return (int)SPerform(2145, 0, 0);
			}
			set
			{
				SPerform(2144, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the print magnification.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int PrintMagnification
		{
			get 
			{
				return (int)SPerform(2147, 0, 0);
			}
			set
			{
				SPerform(2146, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the print colour mode.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int PrintColourMode
		{
			get 
			{
				return (int)SPerform(2149, 0, 0);
			}
			set
			{
				SPerform(2148, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the display line at the top of the display.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int FirstVisibleLine
		{
			get 
			{
				return (int)SPerform(2152, 0, 0);
			}
		}	

		/// <summary>
		/// Returns the number of lines in the document. There is always at least one.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int LineCount
		{
			get 
			{
				return (int)SPerform(2154, 0, 0);
			}
		}	

		/// <summary>
		/// Returns the size in pixels of the left margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int MarginLeft
		{
			get 
			{
				return (int)SPerform(2156, 0, 0);
			}
			set
			{
				SPerform(2155, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Returns the size in pixels of the right margin.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int MarginRight
		{
			get 
			{
				return (int)SPerform(2158, 0, 0);
			}
			set
			{
				SPerform(2157, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Is the document different from when it was last saved?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN05</remarks>
		public bool IsModify
		{
			get 
			{
				return SPerform(2159, 0, 0)!=0;
			}
		}	

		/// <summary>
		/// Retrieve the number of characters in the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int TextLength
		{
			get 
			{
				return (int)SPerform(2183, 0, 0);
			}
		}	

		/// <summary>
		/// Retrieve a pointer to a function that processes messages for this Scintilla.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int DirectFunction
		{
			get 
			{
				return (int)SPerform(2184, 0, 0);
			}
		}	

		/// <summary>
		/// Retrieve a pointer value to use as the first argument when calling
		/// the function returned by GetDirectFunction.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int DirectPointer
		{
			get 
			{
				return (int)SPerform(2185, 0, 0);
			}
		}	

		/// <summary>
		/// Returns true if overtype mode is active otherwise false is returned.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsOvertype
		{
			get 
			{
				return SPerform(2187, 0, 0)!=0;
			}
			set
			{
				SPerform(2186 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Returns the width of the insert mode caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CaretWidth
		{
			get 
			{
				return (int)SPerform(2189, 0, 0);
			}
			set
			{
				SPerform(2188, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the position that starts the target.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int TargetStart
		{
			get 
			{
				return (int)SPerform(2191, 0, 0);
			}
			set
			{
				SPerform(2190, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the position that ends the target.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int TargetEnd
		{
			get 
			{
				return (int)SPerform(2193, 0, 0);
			}
			set
			{
				SPerform(2192, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the search flags used by SearchInTarget.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int SearchFlags
		{
			get 
			{
				return (int)SPerform(2199, 0, 0);
			}
			set
			{
				SPerform(2198, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the fold level of a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN29</remarks>
		public int GetFoldLevel( int line )
		{
			return (int)SPerform(2223,(uint)line, 0);
		}

		/// <summary>
		/// Set the fold level of a line.
		/// This encodes an integer level along with flags indicating whether the
		/// line is a header and whether it is effectively white space.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN30</remarks>
		public void SetFoldLevel( int line, int level  )
		{
			SPerform(2222, (uint)line , (uint)level);
		}	

		/// <summary>
		/// Find the last child line of a header line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN19</remarks>
		public int LastChild(int line, int level)
		{
				return (int)SPerform(2224, (uint)line, (uint)level);
		}	

		/// <summary>
		/// Find the last child line of a header line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int LastChild(int line)
		{
			return (int)SPerform(2224, (uint)line, 0);
		}	

		/// <summary>
		/// Find the parent line of a child line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN18</remarks>
		public int FoldParent(int line)
		{
			return (int)SPerform(2225, (uint)line, 0);
		}	

		/// <summary>
		/// Is a line visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN05</remarks>
		public bool IsLineVisible
		{
			get 
			{
				return SPerform(2228, 0, 0)!=0;
			}
		}	

		/// <summary>
		/// Is a header line expanded?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN31</remarks>
		public bool FoldExpanded( int line )
		{
			return SPerform(2230,(uint)line, 0)!=0;
		}

		/// <summary>
		/// Show the children of a header line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN32</remarks>
		public void FoldExpanded( int line, bool expanded  )
		{
			SPerform(2229, (uint)line , (uint)(expanded?1:0));
		}	

		/// <summary>
		/// Does a tab pressed when caret is within indentation indent?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsTabIndents
		{
			get 
			{
				return SPerform(2261, 0, 0)!=0;
			}
			set
			{
				SPerform(2260 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Does a backspace pressed when caret is within indentation unindent?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsBackSpaceUnIndents
		{
			get 
			{
				return SPerform(2263, 0, 0)!=0;
			}
			set
			{
				SPerform(2262 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve the time the mouse must sit still to generate a mouse dwell event.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int MouseDwellTime
		{
			get 
			{
				return (int)SPerform(2265, 0, 0);
			}
			set
			{
				SPerform(2264, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve whether text is word wrapped.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int WrapMode
		{
			get 
			{
				return (int)SPerform(2269, 0, 0);
			}
			set
			{
				SPerform(2268, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrive the display mode of visual flags for wrapped lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int WrapVisualFlags
		{
			get 
			{
				return (int)SPerform(2461, 0, 0);
			}
			set
			{
				SPerform(2460, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrive the location of visual flags for wrapped lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int WrapVisualFlagsLocation
		{
			get 
			{
				return (int)SPerform(2463, 0, 0);
			}
			set
			{
				SPerform(2462, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrive the start indent for wrapped lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int WrapStartIndent
		{
			get 
			{
				return (int)SPerform(2465, 0, 0);
			}
			set
			{
				SPerform(2464, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the degree of caching of layout information.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int LayoutCache
		{
			get 
			{
				return (int)SPerform(2273, 0, 0);
			}
			set
			{
				SPerform(2272, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the document width assumed for scrolling.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int ScrollWidth
		{
			get 
			{
				return (int)SPerform(2275, 0, 0);
			}
			set
			{
				SPerform(2274, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve whether the maximum scroll position has the last
		/// line at the bottom of the view.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int EndAtLastLine
		{
			get 
			{
				return (int)SPerform(2278, 0, 0);
			}
			set
			{
				SPerform(2277, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Is the vertical scroll bar visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsVScrollBar
		{
			get 
			{
				return SPerform(2281, 0, 0)!=0;
			}
			set
			{
				SPerform(2280 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Is drawing done in two phases with backgrounds drawn before faoregrounds?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsTwoPhaseDraw
		{
			get 
			{
				return SPerform(2283, 0, 0)!=0;
			}
			set
			{
				SPerform(2284 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Are the end of line characters visible?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsViewEOL
		{
			get 
			{
				return SPerform(2355, 0, 0)!=0;
			}
			set
			{
				SPerform(2356 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Retrieve a pointer to the document object.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int DocPointer
		{
			get 
			{
				return (int)SPerform(2357, 0, 0);
			}
			set
			{
				SPerform(2358, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the column number which text should be kept within.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int EdgeColumn
		{
			get 
			{
				return (int)SPerform(2360, 0, 0);
			}
			set
			{
				SPerform(2361, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the edge highlight mode.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int EdgeMode
		{
			get 
			{
				return (int)SPerform(2362, 0, 0);
			}
			set
			{
				SPerform(2363, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the colour used in edge indication.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int EdgeColour
		{
			get 
			{
				return (int)SPerform(2364, 0, 0);
			}
			set
			{
				SPerform(2365, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieves the number of lines completely visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN06</remarks>
		public int LinesOnScreen
		{
			get 
			{
				return (int)SPerform(2370, 0, 0);
			}
		}	

		/// <summary>
		/// Is the selection rectangular? The alternative is the more common stream selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN05</remarks>
		public bool IsSelectionIsRectangle
		{
			get 
			{
				return SPerform(2372, 0, 0)!=0;
			}
		}	

		/// <summary>
		/// Set the zoom level. This number of points is added to the size of all fonts.
		/// It may be positive to magnify or negative to reduce.
		/// Retrieve the zoom level.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int ZoomLevel
		{
			get 
			{
				return (int)SPerform(2374, 0, 0);
			}
			set
			{
				SPerform(2373, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get which document modification events are sent to the container.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int ModEventMask
		{
			get 
			{
				return (int)SPerform(2378, 0, 0);
			}
			set
			{
				SPerform(2359, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Change internal focus flag.
		/// Get internal focus flag.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsFocus
		{
			get 
			{
				return SPerform(2381, 0, 0)!=0;
			}
			set
			{
				SPerform(2380 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Change error status - 0 = OK.
		/// Get error status.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int Status
		{
			get 
			{
				return (int)SPerform(2383, 0, 0);
			}
			set
			{
				SPerform(2382, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Set whether the mouse is captured when its button is pressed.
		/// Get whether mouse gets captured.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN07</remarks>
		public bool IsMouseDownCaptures
		{
			get 
			{
				return SPerform(2385, 0, 0)!=0;
			}
			set
			{
				SPerform(2384 , (uint)(value?1:0), 0 );
			}
		}	

		/// <summary>
		/// Sets the cursor to one of the SC_CURSOR* values.
		/// Get cursor type.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int CursorType
		{
			get 
			{
				return (int)SPerform(2387, 0, 0);
			}
			set
			{
				SPerform(2386, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Change the way control characters are displayed:
		/// If symbol is < 32, keep the drawn way, else, use the given character.
		/// Get the way control characters are displayed.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int ControlCharSymbol
		{
			get 
			{
				return (int)SPerform(2389, 0, 0);
			}
			set
			{
				SPerform(2388, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get and Set the xOffset (ie, horizonal scroll position).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int XOffset
		{
			get 
			{
				return (int)SPerform(2398, 0, 0);
			}
			set
			{
				SPerform(2397, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Is printing line wrapped?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int PrintWrapMode
		{
			get 
			{
				return (int)SPerform(2407, 0, 0);
			}
			set
			{
				SPerform(2406, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Get the mode of the current selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int SelectionMode
		{
			get 
			{
				return (int)SPerform(2423, 0, 0);
			}
			set
			{
				SPerform(2422, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Retrieve the lexing language of the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN08</remarks>
		public int Lexer
		{
			get 
			{
				return (int)SPerform(4002, 0, 0);
			}
			set
			{
				SPerform(4001, (uint)value , 0);
			}
		}	

		/// <summary>
		/// Clear all the styles and make equivalent to the global default style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN20</remarks>
		public void StyleClearAll()
		{
			SPerform(2050, 0, 0);
		}	

		/// <summary>
		/// Set the foreground colour of a style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN24</remarks>
		public void StyleSetFore(int style, int fore )
		{
			SPerform(2051, (uint)style, (uint)fore );
		}	

		/// <summary>
		/// Set the background colour of a style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN24</remarks>
		public void StyleSetBack(int style, int back )
		{
			SPerform(2052, (uint)style, (uint)back );
		}	

		/// <summary>
		/// Set a style to be bold or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetBold(int style, bool bold )
		{
			SPerform(2053, (uint)style, (uint)(bold?1:0) );
		}	

		/// <summary>
		/// Set a style to be italic or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetItalic(int style, bool italic )
		{
			SPerform(2054, (uint)style, (uint)(italic?1:0) );
		}	

		/// <summary>
		/// Set the size of characters of a style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN24</remarks>
		public void StyleSetSize(int style, int sizePoints )
		{
			SPerform(2055, (uint)style, (uint)sizePoints );
		}	

		/// <summary>
		/// Set the font of a style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN27</remarks>
		unsafe public void StyleSetFont(int style, string fontName )
		{
			if(fontName == null ||  fontName.Equals("")  )
				fontName = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( fontName ))
				SPerform(2056,(uint)style, (uint)b );
		}	
						

		/// <summary>
		/// Set a style to have its end of line filled or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetEOLFilled(int style, bool filled )
		{
			SPerform(2057, (uint)style, (uint)(filled?1:0) );
		}	

		/// <summary>
		/// Set a style to be underlined or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetUnderline(int style, bool underline )
		{
			SPerform(2059, (uint)style, (uint)(underline?1:0) );
		}	

		/// <summary>
		/// Set a style to be mixed case, or to force upper or lower case.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN24</remarks>
		public void StyleSetCase(int style, int caseForce )
		{
			SPerform(2060, (uint)style, (uint)caseForce );
		}	

		/// <summary>
		/// Set the character set of the font in a style.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN24</remarks>
		public void StyleSetCharacterSet(int style, int characterSet )
		{
			SPerform(2066, (uint)style, (uint)characterSet );
		}	

		/// <summary>
		/// Set a style to be a hotspot or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetHotSpot(int style, bool hotspot )
		{
			SPerform(2409, (uint)style, (uint)(hotspot?1:0) );
		}	

		/// <summary>
		/// Set a style to be visible or not.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetVisible(int style, bool visible )
		{
			SPerform(2074, (uint)style, (uint)(visible?1:0) );
		}	

		/// <summary>
		/// Set the set of characters making up words for when moving or selecting by word.
		/// First sets deaults like SetCharsDefault.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN28</remarks>
		unsafe public void WordChars(string characters )
		{
			if(characters == null ||  characters.Equals("")  )
				characters = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( characters ))
				SPerform(2077,0, (uint)b );
		}	
						

		/// <summary>
		/// Set a style to be changeable or not (read only).
		/// Experimental feature, currently buggy.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN25</remarks>
		public void StyleSetChangeable(int style, bool changeable )
		{
			SPerform(2099, (uint)style, (uint)(changeable?1:0) );
		}	

		/// <summary>
		/// Define a set of characters that when typed will cause the autocompletion to
		/// choose the selected item.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN28</remarks>
		unsafe public void AutoCSetFillUps(string characterSet )
		{
			if(characterSet == null ||  characterSet.Equals("")  )
				characterSet = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( characterSet ))
				SPerform(2112,0, (uint)b );
		}	
						

		/// <summary>
		/// Set a fore colour for active hotspots.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN26</remarks>
		public void HotspotActiveFore(bool useSetting, int fore )
		{
			SPerform(2410, (uint)(useSetting?1:0), (uint)fore );
		}	

		/// <summary>
		/// Set a back colour for active hotspots.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN26</remarks>
		public void HotspotActiveBack(bool useSetting, int back )
		{
			SPerform(2411, (uint)(useSetting?1:0), (uint)back );
		}	

		/// <summary>
		/// Set the set of characters making up whitespace for when moving or selecting by word.
		/// Should be called after SetWordChars.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN28</remarks>
		unsafe public void WhitespaceChars(string characters )
		{
			if(characters == null ||  characters.Equals("")  )
				characters = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( characters ))
				SPerform(2443,0, (uint)b );
		}	
						

		/// <summary>
		/// Set up a value that may be used by a lexer for some optional feature.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN27</remarks>
		unsafe public void Property(string key, string value )
		{
			if(key == null ||  key.Equals("")  )
				key = "\0\0";
			if(value == null ||  value.Equals("")  )
				value = "\0\0";
	
			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( value ))
				fixed (byte* b2 = System.Text.UTF8Encoding.UTF8.GetBytes( key ))
					SPerform(4004,(uint)b2, (uint)b );
		}	
						

		/// <summary>
		/// Set up the key words used by the lexer.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN27</remarks>
		unsafe public void KeyWords(int keywordSet, string keyWords )
		{
			if(keyWords == null ||  keyWords.Equals("")  )
				keyWords = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( keyWords ))
				SPerform(4005,(uint)keywordSet, (uint)b );
		}	
						

		/// <summary>
		/// Set the lexing language of the document based on string name.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN28</remarks>
		unsafe public void LexerLanguage(string language )
		{
			if(language == null ||  language.Equals("")  )
				language = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( language ))
				SPerform(4006,0, (uint)b );
		}	
						
		#endregion

		#region "scintilla-functions"

		/// <summary>
		/// Add text to the document at current position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void AddText(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2001,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Insert string at a position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void InsertText(int pos, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2003,(uint)pos, (uint)b );
		}	
						

		/// <summary>
		/// Delete all text in the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ClearAll()
		{
			SPerform(2004, 0, 0);
		}	
						

		/// <summary>
		/// Set all style bytes to 0, remove all folding information.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ClearDocumentStyle()
		{
			SPerform(2005, 0, 0);
		}	
						

		/// <summary>
		/// Redoes the next action on the undo history.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Redo()
		{
			SPerform(2011, 0, 0);
		}	
						

		/// <summary>
		/// Select all the text in the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void SelectAll()
		{
			SPerform(2013, 0, 0);
		}	
						

		/// <summary>
		/// Remember the current position in the undo history as the position
		/// at which the document was saved.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void SetSavePoint()
		{
			SPerform(2014, 0, 0);
		}	
						

		/// <summary>
		/// Retrieve the line number at which a particular marker is located.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int MarkerLineFromHandle(int handle)
		{
			return (int) SPerform(2017, (uint)handle, 0);
		}	
						

		/// <summary>
		/// Delete a marker.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void MarkerDeleteHandle(int handle)
		{
			 SPerform(2018, (uint)handle, 0);
		}	
						

		/// <summary>
		/// Find the position from a point within the window.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public int PositionFromPoint(int x, int y )
		{
			return (int) SPerform(2022, (uint)x, (uint)y );
		}	
						

		/// <summary>
		/// Find the position from a point within the window but return
		/// INVALID_POSITION if not close to text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public int PositionFromPointClose(int x, int y )
		{
			return (int) SPerform(2023, (uint)x, (uint)y );
		}	
						

		/// <summary>
		/// Set caret to start of a line and ensure it is visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void GotoLine(int line)
		{
			 SPerform(2024, (uint)line, 0);
		}	
						

		/// <summary>
		/// Set caret to a position and ensure it is visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void GotoPos(int pos)
		{
			 SPerform(2025, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Retrieve the text of the line containing the caret.
		/// Returns the index of the caret on the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN14</remarks>
		unsafe public string GetCurLine( int length )
		{
				int sz = (int)SPerform(2027,(uint)length ,0);

				byte[] buffer = new byte[sz+1];
				fixed (byte* b = buffer)
					SPerform( 2027 ,(uint)length+1 , (uint)b );
				return System.Text.UTF8Encoding.UTF8.GetString( buffer,0,sz);
		}
	
		/// <summary>
		/// Length Method for : Retrieve the text of the line containing the caret.
		/// Returns the index of the caret on the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN15</remarks>
		public int CurLineSize
		{	
			get
			{
				return (int)SPerform(2027,0 ,0);
			}
		}

		/// <summary>
		/// Convert all line endings in the document to one mode.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void ConvertEOLs(int eolMode)
		{
			 SPerform(2029, (uint)eolMode, 0);
		}	
						

		/// <summary>
		/// Set the current styling position to pos and the styling mask to mask.
		/// The styling mask can be used to protect some bits in each styling byte from modification.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void StartStyling(int pos, int mask )
		{
			 SPerform(2032, (uint)pos, (uint)mask );
		}	
						

		/// <summary>
		/// Change style from current styling position for length characters to a style
		/// and move the current styling position to after this newly styled segment.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void SetStyling(int length, int style )
		{
			 SPerform(2033, (uint)length, (uint)style );
		}	
						

		/// <summary>
		/// Set the symbol used for a particular marker number.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void MarkerDefine(int markerNumber, int markerSymbol )
		{
			 SPerform(2040, (uint)markerNumber, (uint)markerSymbol );
		}	
						

		/// <summary>
		/// Set the foreground colour used for a particular marker number.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void MarkerSetFore(int markerNumber, int fore )
		{
			 SPerform(2041, (uint)markerNumber, (uint)fore );
		}	
						

		/// <summary>
		/// Set the background colour used for a particular marker number.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void MarkerSetBack(int markerNumber, int back )
		{
			 SPerform(2042, (uint)markerNumber, (uint)back );
		}	
						

		/// <summary>
		/// Add a marker to a line, returning an ID which can be used to find or delete the marker.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public int MarkerAdd(int line, int markerNumber )
		{
			return (int) SPerform(2043, (uint)line, (uint)markerNumber );
		}	
						

		/// <summary>
		/// Delete a marker from a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void MarkerDelete(int line, int markerNumber )
		{
			 SPerform(2044, (uint)line, (uint)markerNumber );
		}	
						

		/// <summary>
		/// Delete all markers with a particular number from all lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void MarkerDeleteAll(int markerNumber)
		{
			 SPerform(2045, (uint)markerNumber, 0);
		}	
						

		/// <summary>
		/// Get a bit mask of all the markers set on a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int MarkerGet(int line)
		{
			return (int) SPerform(2046, (uint)line, 0);
		}	
						

		/// <summary>
		/// Find the next line after lineStart that includes a marker in mask.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public int MarkerNext(int lineStart, int markerMask )
		{
			return (int) SPerform(2047, (uint)lineStart, (uint)markerMask );
		}	
						

		/// <summary>
		/// Find the previous line before lineStart that includes a marker in mask.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public int MarkerPrevious(int lineStart, int markerMask )
		{
			return (int) SPerform(2048, (uint)lineStart, (uint)markerMask );
		}	
						

		/// <summary>
		/// Define a marker from a pixmap.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void MarkerDefinePixmap(int markerNumber, string pixmap )
		{
			if(pixmap == null ||  pixmap.Equals("")  )
				pixmap = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( pixmap ))
				 SPerform(2049,(uint)markerNumber, (uint)b );
		}	
						

		/// <summary>
		/// Reset the default style to its state at startup
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StyleResetDefault()
		{
			SPerform(2058, 0, 0);
		}	
						

		/// <summary>
		/// Set the foreground colour of the selection and whether to use this setting.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetSelFore(bool useSetting, int fore )
		{
			 SPerform(2067,(uint)(useSetting?1:0), (uint)fore );
		}	
						

		/// <summary>
		/// Set the background colour of the selection and whether to use this setting.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetSelBack(bool useSetting, int back )
		{
			 SPerform(2068,(uint)(useSetting?1:0), (uint)back );
		}	
						

		/// <summary>
		/// When key+modifier combination km is pressed perform msg.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void AssignCmdKey(int km, int msg )
		{
			 SPerform(2070, (uint)km, (uint)msg );
		}	
						

		/// <summary>
		/// When key+modifier combination km is pressed do nothing.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void ClearCmdKey(int km)
		{
			 SPerform(2071, (uint)km, 0);
		}	
						

		/// <summary>
		/// Drop all key mappings.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ClearAllCmdKeys()
		{
			SPerform(2072, 0, 0);
		}	
						

		/// <summary>
		/// Set the styles for a segment of the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void SetStylingEx(int length, string styles )
		{
			if(styles == null ||  styles.Equals("")  )
				styles = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( styles ))
				 SPerform(2073,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Start a sequence of actions that is undone and redone as a unit.
		/// May be nested.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void BeginUndoAction()
		{
			SPerform(2078, 0, 0);
		}	
						

		/// <summary>
		/// End a sequence of actions that is undone and redone as a unit.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void EndUndoAction()
		{
			SPerform(2079, 0, 0);
		}	
						

		/// <summary>
		/// Set the foreground colour of all whitespace and whether to use this setting.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetWhitespaceFore(bool useSetting, int fore )
		{
			 SPerform(2084,(uint)(useSetting?1:0), (uint)fore );
		}	
						

		/// <summary>
		/// Set the background colour of all whitespace and whether to use this setting.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetWhitespaceBack(bool useSetting, int back )
		{
			 SPerform(2085,(uint)(useSetting?1:0), (uint)back );
		}	
						

		/// <summary>
		/// Display a auto-completion list.
		/// The lenEntered parameter indicates how many characters before
		/// the caret should be used to provide context.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void AutoCShow(int lenEntered, string itemList )
		{
			if(itemList == null ||  itemList.Equals("")  )
				itemList = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( itemList ))
				 SPerform(2100,(uint)lenEntered, (uint)b );
		}	
						

		/// <summary>
		/// Remove the auto-completion list from the screen.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void AutoCCancel()
		{
			SPerform(2101, 0, 0);
		}	
						

		/// <summary>
		/// User has selected an item so remove the list and insert the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void AutoCComplete()
		{
			SPerform(2104, 0, 0);
		}	
						

		/// <summary>
		/// Define a set of character that when typed cancel the auto-completion list.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN04</remarks>
		unsafe public void AutoCStops(string characterSet)
		{
			if(characterSet == null ||  characterSet.Equals("")  )
				characterSet = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( characterSet ))
				 SPerform(2105,0 ,  (uint)b);
		}	
						

		/// <summary>
		/// Select the item in the auto-completion list that starts with a string.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN04</remarks>
		unsafe public void AutoCSelect(string text)
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2108,0 ,  (uint)b);
		}	
						

		/// <summary>
		/// Display a list of strings and send notification when user chooses one.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void UserListShow(int listType, string itemList )
		{
			if(itemList == null ||  itemList.Equals("")  )
				itemList = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( itemList ))
				 SPerform(2117,(uint)listType, (uint)b );
		}	
						

		/// <summary>
		/// Register an XPM image for use in autocompletion lists.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void RegisterImage(int type, string xpmData )
		{
			if(xpmData == null ||  xpmData.Equals("")  )
				xpmData = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( xpmData ))
				 SPerform(2405,(uint)type, (uint)b );
		}	
						

		/// <summary>
		/// Clear all the registered XPM images.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ClearRegisteredImages()
		{
			SPerform(2408, 0, 0);
		}	
						

		/// <summary>
		/// Retrieve the contents of a line.
		/// Returns the length of the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN14</remarks>
		unsafe public string GetLine( int line )
		{
				int sz = (int)SPerform(2153,(uint)line ,0);

				byte[] buffer = new byte[sz+1];
				fixed (byte* b = buffer)
					SPerform( 2153 ,(uint)line+1 , (uint)b );
				return System.Text.UTF8Encoding.UTF8.GetString( buffer,0,sz);
		}
	
		/// <summary>
		/// Length Method for : Retrieve the contents of a line.
		/// Returns the length of the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN15</remarks>
		public int LineSize
		{	
			get
			{
				return (int)SPerform(2153,0 ,0);
			}
		}

		/// <summary>
		/// Select a range of text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void SetSel(int start, int end )
		{
			 SPerform(2160, (uint)start, (uint)end );
		}	
						

		/// <summary>
		/// Retrieve the selected text.
		/// Return the length of the text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN12</remarks>
		unsafe public string SelText
		{
			get
			{
				int sz = (int)SPerform(2161,0 ,0);

				byte[] buffer = new byte[sz+1];
				fixed (byte* b = buffer)
					SPerform( 2161 ,(UInt32)sz+1 , (uint)b );
				return System.Text.UTF8Encoding.UTF8.GetString( buffer,0,sz );
			}
		}
	
		/// <summary>
		/// Length Method for : Retrieve the selected text.
		/// Return the length of the text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN13</remarks>
		public int SelTextSize
		{	
			get
			{
				return (int)SPerform(2161,0 ,0);
			}
		}

		/// <summary>
		/// Draw the selection in normal style or with selection highlighted.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN02</remarks>
		public void HideSelection(bool normal)
		{
			 SPerform(2163, (uint)(normal?1:0), 0);
		}	
						

		/// <summary>
		/// Retrieve the x value of the point in the window where a position is displayed.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN11</remarks>
		public int PointXFromPosition(int pos)
		{
			return (int) SPerform(2164, 0, (uint)pos );
		}	
						

		/// <summary>
		/// Retrieve the y value of the point in the window where a position is displayed.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN11</remarks>
		public int PointYFromPosition(int pos)
		{
			return (int) SPerform(2165, 0, (uint)pos );
		}	
						

		/// <summary>
		/// Retrieve the line containing a position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int LineFromPosition(int pos)
		{
			return (int) SPerform(2166, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Retrieve the position at the start of a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int PositionFromLine(int line)
		{
			return (int) SPerform(2167, (uint)line, 0);
		}	
						

		/// <summary>
		/// Scroll horizontally and vertically.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void LineScroll(int columns, int lines )
		{
			 SPerform(2168, (uint)columns, (uint)lines );
		}	
						

		/// <summary>
		/// Ensure the caret is visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ScrollCaret()
		{
			SPerform(2169, 0, 0);
		}	
						

		/// <summary>
		/// Replace the selected text with the argument text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN04</remarks>
		unsafe public void ReplaceSel(string text)
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2170,0 ,  (uint)b);
		}	
						

		/// <summary>
		/// Null operation.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Null()
		{
			SPerform(2172, 0, 0);
		}	
						

		/// <summary>
		/// Delete the undo history.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void EmptyUndoBuffer()
		{
			SPerform(2175, 0, 0);
		}	
						

		/// <summary>
		/// Undo one action in the undo history.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Undo()
		{
			SPerform(2176, 0, 0);
		}	
						

		/// <summary>
		/// Cut the selection to the clipboard.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Cut()
		{
			SPerform(2177, 0, 0);
		}	
						

		/// <summary>
		/// Copy the selection to the clipboard.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Copy()
		{
			SPerform(2178, 0, 0);
		}	
						

		/// <summary>
		/// Paste the contents of the clipboard into the document replacing the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Paste()
		{
			SPerform(2179, 0, 0);
		}	
						

		/// <summary>
		/// Clear the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Clear()
		{
			SPerform(2180, 0, 0);
		}	
						

		/// <summary>
		/// Replace the contents of the document with the argument text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN04</remarks>
		unsafe public void SetText(string text)
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2181,0 ,  (uint)b);
		}	
						

		/// <summary>
		/// Retrieve all the text in the document.
		/// Returns number of characters retrieved.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN14</remarks>
		unsafe public string GetText( int length )
		{
				int sz = (int)SPerform(2182,(uint)length ,0);
				byte[] buffer = new byte[sz+1];
				fixed (byte* b = buffer)
					SPerform( 2182 ,(uint)length+1 , (uint)b );
				return System.Text.UTF8Encoding.UTF8.GetString( buffer,0,sz-1);
		}
	
		/// <summary>
		/// Length Method for : Retrieve all the text in the document.
		/// Returns number of characters retrieved.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN15</remarks>
		public int TextSize
		{	
			get
			{
				return (int)SPerform(2182,0 ,0);
			}
		}

		/// <summary>
		/// Replace the target text with the argument text.
		/// Text is counted so it can contain NULs.
		/// Returns the length of the replacement text.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int ReplaceTarget(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2194,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Replace the target text with the argument text after \d processing.
		/// Text is counted so it can contain NULs.
		/// Looks for \d where d is between 1 and 9 and replaces these with the strings
		/// matched in the last search operation which were surrounded by \( and \).
		/// Returns the length of the replacement text including any change
		/// caused by processing the \d patterns.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int ReplaceTargetRE(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2195,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Search for a counted string in the target and set the target to the found
		/// range. Text is counted so it can contain NULs.
		/// Returns length of range or -1 for failure in which case target is not moved.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int SearchInTarget(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2197,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Show a call tip containing a definition near position pos.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void CallTipShow(int pos, string definition )
		{
			if(definition == null ||  definition.Equals("")  )
				definition = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( definition ))
				 SPerform(2200,(uint)pos, (uint)b );
		}	
						

		/// <summary>
		/// Remove the call tip from the screen.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CallTipCancel()
		{
			SPerform(2201, 0, 0);
		}	
						

		/// <summary>
		/// Highlight a segment of the definition.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void CallTipSetHlt(int start, int end )
		{
			 SPerform(2204, (uint)start, (uint)end );
		}	
						

		/// <summary>
		/// Find the display line of a document line taking hidden lines into account.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int VisibleFromDocLine(int line)
		{
			return (int) SPerform(2220, (uint)line, 0);
		}	
						

		/// <summary>
		/// Find the document line of a display line taking hidden lines into account.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int DocLineFromVisible(int lineDisplay)
		{
			return (int) SPerform(2221, (uint)lineDisplay, 0);
		}	
						

		/// <summary>
		/// Make a range of lines visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void ShowLines(int lineStart, int lineEnd )
		{
			 SPerform(2226, (uint)lineStart, (uint)lineEnd );
		}	
						

		/// <summary>
		/// Make a range of lines invisible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void HideLines(int lineStart, int lineEnd )
		{
			 SPerform(2227, (uint)lineStart, (uint)lineEnd );
		}	
						

		/// <summary>
		/// Switch a header line between expanded and contracted.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void ToggleFold(int line)
		{
			 SPerform(2231, (uint)line, 0);
		}	
						

		/// <summary>
		/// Ensure a particular line is visible by expanding any header line hiding it.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void EnsureVisible(int line)
		{
			 SPerform(2232, (uint)line, 0);
		}	
						

		/// <summary>
		/// Set some style options for folding.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void SetFoldFlags(int flags)
		{
			 SPerform(2233, (uint)flags, 0);
		}	
						

		/// <summary>
		/// Ensure a particular line is visible by expanding any header line hiding it.
		/// Use the currently set visibility policy to determine which range to display.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void EnsureVisibleEnforcePolicy(int line)
		{
			 SPerform(2234, (uint)line, 0);
		}	
						

		/// <summary>
		/// Get position of start of word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN23</remarks>
		public int WordStartPosition(int pos, bool onlyWordCharacters )
		{
			return (int) SPerform(2266,(uint)pos, (uint)(onlyWordCharacters?1:0) );
		}	
						

		/// <summary>
		/// Get position of end of word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN23</remarks>
		public int WordEndPosition(int pos, bool onlyWordCharacters )
		{
			return (int) SPerform(2267,(uint)pos, (uint)(onlyWordCharacters?1:0) );
		}	
						

		/// <summary>
		/// Measure the pixel width of some text in a particular style.
		/// NUL terminated text argument.
		/// Does not handle tab or control characters.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int TextWidth(int style, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2276,(uint)style, (uint)b );
		}	
						

		/// <summary>
		/// Retrieve the height of a particular line of text in pixels.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int TextHeight(int line)
		{
			return (int) SPerform(2279, (uint)line, 0);
		}	
						

		/// <summary>
		/// Append a string to the end of the document without changing the selection.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void AppendText(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2282,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Make the target range start and end be the same as the selection range start and end.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void TargetFromSelection()
		{
			SPerform(2287, 0, 0);
		}	
						

		/// <summary>
		/// Join the lines in the target.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LinesJoin()
		{
			SPerform(2288, 0, 0);
		}	
						

		/// <summary>
		/// Split the lines in the target into lines that are less wide than pixelWidth
		/// where possible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void LinesSplit(int pixelWidth)
		{
			 SPerform(2289, (uint)pixelWidth, 0);
		}	
						

		/// <summary>
		/// Set the colours used as a chequerboard pattern in the fold margin
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetFoldMarginColour(bool useSetting, int back )
		{
			 SPerform(2290,(uint)(useSetting?1:0), (uint)back );
		}	
						

		/// <summary>
		/// Set the colours used as a chequerboard pattern in the fold margin
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN21</remarks>
		public void SetFoldMarginHiColour(bool useSetting, int fore )
		{
			 SPerform(2291,(uint)(useSetting?1:0), (uint)fore );
		}	
						

		/// <summary>
		/// Move caret down one line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineDown()
		{
			SPerform(2300, 0, 0);
		}	
						

		/// <summary>
		/// Move caret down one line extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineDownExtend()
		{
			SPerform(2301, 0, 0);
		}	
						

		/// <summary>
		/// Move caret up one line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineUp()
		{
			SPerform(2302, 0, 0);
		}	
						

		/// <summary>
		/// Move caret up one line extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineUpExtend()
		{
			SPerform(2303, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharLeft()
		{
			SPerform(2304, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one character extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharLeftExtend()
		{
			SPerform(2305, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharRight()
		{
			SPerform(2306, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one character extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharRightExtend()
		{
			SPerform(2307, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordLeft()
		{
			SPerform(2308, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one word extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordLeftExtend()
		{
			SPerform(2309, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordRight()
		{
			SPerform(2310, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one word extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordRightExtend()
		{
			SPerform(2311, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position on line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Home()
		{
			SPerform(2312, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position on line extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeExtend()
		{
			SPerform(2313, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position on line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEnd()
		{
			SPerform(2314, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position on line extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndExtend()
		{
			SPerform(2315, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position in document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DocumentStart()
		{
			SPerform(2316, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position in document extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DocumentStartExtend()
		{
			SPerform(2317, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position in document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DocumentEnd()
		{
			SPerform(2318, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position in document extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DocumentEndExtend()
		{
			SPerform(2319, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page up.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageUp()
		{
			SPerform(2320, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page up extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageUpExtend()
		{
			SPerform(2321, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page down.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageDown()
		{
			SPerform(2322, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page down extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageDownExtend()
		{
			SPerform(2323, 0, 0);
		}	
						

		/// <summary>
		/// Switch from insert to overtype mode or the reverse.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void EditToggleOvertype()
		{
			SPerform(2324, 0, 0);
		}	
						

		/// <summary>
		/// Cancel any modes such as call tip or auto-completion list display.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Cancel()
		{
			SPerform(2325, 0, 0);
		}	
						

		/// <summary>
		/// Delete the selection or if no selection, the character before the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DeleteBack()
		{
			SPerform(2326, 0, 0);
		}	
						

		/// <summary>
		/// If selection is empty or all on one line replace the selection with a tab character.
		/// If more than one line selected, indent the lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void Tab()
		{
			SPerform(2327, 0, 0);
		}	
						

		/// <summary>
		/// Dedent the selected lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void BackTab()
		{
			SPerform(2328, 0, 0);
		}	
						

		/// <summary>
		/// Insert a new line, may use a CRLF, CR or LF depending on EOL mode.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void NewLine()
		{
			SPerform(2329, 0, 0);
		}	
						

		/// <summary>
		/// Insert a Form Feed character.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void FormFeed()
		{
			SPerform(2330, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to before first visible character on line.
		/// If already there move to first character on line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void VCHome()
		{
			SPerform(2331, 0, 0);
		}	
						

		/// <summary>
		/// Like VCHome but extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void VCHomeExtend()
		{
			SPerform(2332, 0, 0);
		}	
						

		/// <summary>
		/// Magnify the displayed text by increasing the sizes by 1 point.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ZoomIn()
		{
			SPerform(2333, 0, 0);
		}	
						

		/// <summary>
		/// Make the displayed text smaller by decreasing the sizes by 1 point.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ZoomOut()
		{
			SPerform(2334, 0, 0);
		}	
						

		/// <summary>
		/// Delete the word to the left of the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DelWordLeft()
		{
			SPerform(2335, 0, 0);
		}	
						

		/// <summary>
		/// Delete the word to the right of the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DelWordRight()
		{
			SPerform(2336, 0, 0);
		}	
						

		/// <summary>
		/// Cut the line containing the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineCut()
		{
			SPerform(2337, 0, 0);
		}	
						

		/// <summary>
		/// Delete the line containing the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineDelete()
		{
			SPerform(2338, 0, 0);
		}	
						

		/// <summary>
		/// Switch the current line with the previous.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineTranspose()
		{
			SPerform(2339, 0, 0);
		}	
						

		/// <summary>
		/// Duplicate the current line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineDuplicate()
		{
			SPerform(2404, 0, 0);
		}	
						

		/// <summary>
		/// Transform the selection to lower case.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LowerCase()
		{
			SPerform(2340, 0, 0);
		}	
						

		/// <summary>
		/// Transform the selection to upper case.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void UpperCase()
		{
			SPerform(2341, 0, 0);
		}	
						

		/// <summary>
		/// Scroll the document down, keeping the caret visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineScrollDown()
		{
			SPerform(2342, 0, 0);
		}	
						

		/// <summary>
		/// Scroll the document up, keeping the caret visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineScrollUp()
		{
			SPerform(2343, 0, 0);
		}	
						

		/// <summary>
		/// Delete the selection or if no selection, the character before the caret.
		/// Will not delete the character before at the start of a line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DeleteBackNotLine()
		{
			SPerform(2344, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position on display line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeDisplay()
		{
			SPerform(2345, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position on display line extending selection to
		/// new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeDisplayExtend()
		{
			SPerform(2346, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position on display line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndDisplay()
		{
			SPerform(2347, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position on display line extending selection to new
		/// caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndDisplayExtend()
		{
			SPerform(2348, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeWrap()
		{
			SPerform(2349, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeWrapExtend()
		{
			SPerform(2450, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndWrap()
		{
			SPerform(2451, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndWrapExtend()
		{
			SPerform(2452, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void VCHomeWrap()
		{
			SPerform(2453, 0, 0);
		}	
						

		/// <summary>
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void VCHomeWrapExtend()
		{
			SPerform(2454, 0, 0);
		}	
						

		/// <summary>
		/// Copy the line containing the caret.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineCopy()
		{
			SPerform(2455, 0, 0);
		}	
						

		/// <summary>
		/// Move the caret inside current view if it's not there already.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void MoveCaretInsideView()
		{
			SPerform(2401, 0, 0);
		}	
						

		/// <summary>
		/// How many characters are on a line, not including end of line characters?
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int LineLength(int line)
		{
			return (int) SPerform(2350, (uint)line, 0);
		}	
						

		/// <summary>
		/// Highlight the characters at two positions.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void BraceHighlight(int pos1, int pos2 )
		{
			 SPerform(2351, (uint)pos1, (uint)pos2 );
		}	
						

		/// <summary>
		/// Highlight the character at a position indicating there is no matching brace.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void BraceBadLight(int pos)
		{
			 SPerform(2352, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Find the position of a matching brace or INVALID_POSITION if no match.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int BraceMatch(int pos)
		{
			return (int) SPerform(2353, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Sets the current caret position to be the search anchor.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void SearchAnchor()
		{
			SPerform(2366, 0, 0);
		}	
						

		/// <summary>
		/// Find some text starting at the search anchor.
		/// Does not ensure the selection is visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int SearchNext(int flags, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2367,(uint)flags, (uint)b );
		}	
						

		/// <summary>
		/// Find some text starting at the search anchor and moving backwards.
		/// Does not ensure the selection is visible.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public int SearchPrev(int flags, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				return (int) SPerform(2368,(uint)flags, (uint)b );
		}	
						

		/// <summary>
		/// Set whether a pop up menu is displayed automatically when the user presses
		/// the wrong mouse button.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN02</remarks>
		public void UsePopUp(bool allowPopUp)
		{
			 SPerform(2371, (uint)(allowPopUp?1:0), 0);
		}	
						

		/// <summary>
		/// Create a new document object.
		/// Starts with reference count of 1 and not selected into editor.
		/// Extend life of document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN11</remarks>
		public void AddRefDocument(int doc)
		{
			 SPerform(2376, 0, (uint)doc );
		}	
						

		/// <summary>
		/// Create a new document object.
		/// Starts with reference count of 1 and not selected into editor.
		/// Extend life of document.
		/// Release a reference to the document, deleting document if it fades to black.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN11</remarks>
		public void ReleaseDocument(int doc)
		{
			 SPerform(2377, 0, (uint)doc );
		}	
						

		/// <summary>
		/// Move to the previous change in capitalisation.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordPartLeft()
		{
			SPerform(2390, 0, 0);
		}	
						

		/// <summary>
		/// Move to the previous change in capitalisation.
		/// Move to the previous change in capitalisation extending selection
		/// to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordPartLeftExtend()
		{
			SPerform(2391, 0, 0);
		}	
						

		/// <summary>
		/// Move to the previous change in capitalisation.
		/// Move to the previous change in capitalisation extending selection
		/// to new caret position.
		/// Move to the change next in capitalisation.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordPartRight()
		{
			SPerform(2392, 0, 0);
		}	
						

		/// <summary>
		/// Move to the previous change in capitalisation.
		/// Move to the previous change in capitalisation extending selection
		/// to new caret position.
		/// Move to the change next in capitalisation.
		/// Move to the next change in capitalisation extending selection
		/// to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordPartRightExtend()
		{
			SPerform(2393, 0, 0);
		}	
						

		/// <summary>
		/// Constants for use with SetVisiblePolicy, similar to SetCaretPolicy.
		/// Set the way the display area is determined when a particular line
		/// is to be moved to by Find, FindNext, GotoLine, etc.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void SetVisiblePolicy(int visiblePolicy, int visibleSlop )
		{
			 SPerform(2394, (uint)visiblePolicy, (uint)visibleSlop );
		}	
						

		/// <summary>
		/// Delete back from the current position to the start of the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DelLineLeft()
		{
			SPerform(2395, 0, 0);
		}	
						

		/// <summary>
		/// Delete forwards from the current position to the end of the line.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void DelLineRight()
		{
			SPerform(2396, 0, 0);
		}	
						

		/// <summary>
		/// Set the last x chosen value to be the caret x position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ChooseCaretX()
		{
			SPerform(2399, 0, 0);
		}	
						

		/// <summary>
		/// Set the focus to this Scintilla widget.
		/// GTK+ Specific.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void GrabFocus()
		{
			SPerform(2400, 0, 0);
		}	
						

		/// <summary>
		/// Set the way the caret is kept visible when going sideway.
		/// The exclusion zone is given in pixels.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void SetXCaretPolicy(int caretPolicy, int caretSlop )
		{
			 SPerform(2402, (uint)caretPolicy, (uint)caretSlop );
		}	
						

		/// <summary>
		/// Set the way the line the caret is on is kept visible.
		/// The exclusion zone is given in lines.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void SetYCaretPolicy(int caretPolicy, int caretSlop )
		{
			 SPerform(2403, (uint)caretPolicy, (uint)caretSlop );
		}	
						

		/// <summary>
		/// Move caret between paragraphs (delimited by empty lines).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ParaDown()
		{
			SPerform(2413, 0, 0);
		}	
						

		/// <summary>
		/// Move caret between paragraphs (delimited by empty lines).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ParaDownExtend()
		{
			SPerform(2414, 0, 0);
		}	
						

		/// <summary>
		/// Move caret between paragraphs (delimited by empty lines).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ParaUp()
		{
			SPerform(2415, 0, 0);
		}	
						

		/// <summary>
		/// Move caret between paragraphs (delimited by empty lines).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void ParaUpExtend()
		{
			SPerform(2416, 0, 0);
		}	
						

		/// <summary>
		/// Given a valid document position, return the previous position taking code
		/// page into account. Returns 0 if passed 0.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int PositionBefore(int pos)
		{
			return (int) SPerform(2417, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Given a valid document position, return the next position taking code
		/// page into account. Maximum value returned is the last position in the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int PositionAfter(int pos)
		{
			return (int) SPerform(2418, (uint)pos, 0);
		}	
						

		/// <summary>
		/// Copy a range of text to the clipboard. Positions are clipped into the document.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void CopyRange(int start, int end )
		{
			 SPerform(2419, (uint)start, (uint)end );
		}	
						

		/// <summary>
		/// Copy argument text to the clipboard.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN22</remarks>
		unsafe public void CopyText(int length, string text )
		{
			if(text == null ||  text.Equals("")  )
				text = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( text ))
				 SPerform(2420,(uint)length, (uint)b );
		}	
						

		/// <summary>
		/// Retrieve the position of the start of the selection at the given line (INVALID_POSITION if no selection on this line).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int GetLineSelStartPosition(int line)
		{
			return (int) SPerform(2424, (uint)line, 0);
		}	
						

		/// <summary>
		/// Retrieve the position of the end of the selection at the given line (INVALID_POSITION if no selection on this line).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public int GetLineSelEndPosition(int line)
		{
			return (int) SPerform(2425, (uint)line, 0);
		}	
						

		/// <summary>
		/// Move caret down one line, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineDownRectExtend()
		{
			SPerform(2426, 0, 0);
		}	
						

		/// <summary>
		/// Move caret up one line, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineUpRectExtend()
		{
			SPerform(2427, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one character, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharLeftRectExtend()
		{
			SPerform(2428, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one character, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void CharRightRectExtend()
		{
			SPerform(2429, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to first position on line, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void HomeRectExtend()
		{
			SPerform(2430, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to before first visible character on line.
		/// If already there move to first character on line.
		/// In either case, extend rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void VCHomeRectExtend()
		{
			SPerform(2431, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to last position on line, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void LineEndRectExtend()
		{
			SPerform(2432, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page up, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageUpRectExtend()
		{
			SPerform(2433, 0, 0);
		}	
						

		/// <summary>
		/// Move caret one page down, extending rectangular selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void PageDownRectExtend()
		{
			SPerform(2434, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to top of page, or one page up if already at top of page.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StutteredPageUp()
		{
			SPerform(2435, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to top of page, or one page up if already at top of page, extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StutteredPageUpExtend()
		{
			SPerform(2436, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to bottom of page, or one page down if already at bottom of page.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StutteredPageDown()
		{
			SPerform(2437, 0, 0);
		}	
						

		/// <summary>
		/// Move caret to bottom of page, or one page down if already at bottom of page, extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StutteredPageDownExtend()
		{
			SPerform(2438, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one word, position cursor at end of word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordLeftEnd()
		{
			SPerform(2439, 0, 0);
		}	
						

		/// <summary>
		/// Move caret left one word, position cursor at end of word, extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordLeftEndExtend()
		{
			SPerform(2440, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one word, position cursor at end of word.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordRightEnd()
		{
			SPerform(2441, 0, 0);
		}	
						

		/// <summary>
		/// Move caret right one word, position cursor at end of word, extending selection to new caret position.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void WordRightEndExtend()
		{
			SPerform(2442, 0, 0);
		}	
						

		/// <summary>
		/// Reset the set of characters for whitespace and word characters to the defaults.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void SetCharsDefault()
		{
			SPerform(2444, 0, 0);
		}	
						

		/// <summary>
		/// Enlarge the document to a particular size of text bytes.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN03</remarks>
		public void Allocate(int bytes)
		{
			 SPerform(2446, (uint)bytes, 0);
		}	
						

		/// <summary>
		/// Start notifying the container of all key presses and commands.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StartRecord()
		{
			SPerform(3001, 0, 0);
		}	
						

		/// <summary>
		/// Stop notifying the container of all key presses and commands.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN01</remarks>
		public void StopRecord()
		{
			SPerform(3002, 0, 0);
		}	
						

		/// <summary>
		/// Colourise a segment of the document using the current lexing language.
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN16</remarks>
		public void Colourise(int start, int end )
		{
			 SPerform(4003, (uint)start, (uint)end );
		}	
						

		/// <summary>
		/// Load a lexer library (dll / so).
		/// 
		/// </summary>
		/// <remarks>Autogenerated: IGEN04</remarks>
		unsafe public void LoadLexerLibrary(string path)
		{
			if(path == null ||  path.Equals("")  )
				path = "\0\0";

			fixed (byte* b = System.Text.UTF8Encoding.UTF8.GetBytes( path ))
				 SPerform(4007,0 ,  (uint)b);
		}	
						
		#endregion

		#region "scintilla-generated-status"
/*
   Not Emitted:
 Function : AddStyledText
    // Function with cells parameter skipped [AddStyledText]
    // There is no clear way to provide this functionaliy to a .NET app.
 Function : GetStyledText
    // Function with parameter 2 TEXTRANGE skipped [GetStyledText]
    // Not yet coded this :p.
 Function : FindText
    // Function with parameter 2 find text skipped [FindText]
    // Not yet coded this :p.
 Function : FormatRange
    // Function with parameter 2 formatrange skipped [FormatRange]
    // Not yet coded this :p.
 Function : GetTextRange
    // Function with parameter 2 TEXTRANGE skipped [GetTextRange]
    // Not yet coded this :p.
 Set Accessor: CallTipSetBack
    // Set Accessor with parameter, but still void return [CallTipSetBack]
    // Not yet coded this :p.
 Set Accessor: CallTipSetFore
    // Set Accessor with parameter, but still void return [CallTipSetFore]
    // Not yet coded this :p.
 Set Accessor: CallTipSetForeHlt
    // Set Accessor with parameter, but still void return [CallTipSetForeHlt]
    // Not yet coded this :p.
 Set Accessor: HotspotActiveUnderline
    // Set Accessor with parameter, but still void return [HotspotActiveUnderline]
    // Not yet coded this :p.
 Set Accessor: HotspotSingleLine
    // Set Accessor with parameter, but still void return [HotspotSingleLine]
    // Not yet coded this :p.
 Value : INVALID_POSITION
 Value : SCI_START
 Value : SCI_OPTIONAL_START
 Value : SCI_LEXER_START
 Value : SC_CP_UTF8
 Value : SC_CP_DBCS
 Value : MARKER_MAX
 Value : SC_MASK_FOLDERS
 Value : INDIC0_MASK
 Value : INDIC1_MASK
 Value : INDIC2_MASK
 Value : INDICS_MASK
 Value : SC_TIME_FOREVER
 Value : VISIBLE_SLOP
 Value : VISIBLE_STRICT
 Value : KEYWORDSET_MAX
 Value : SC_MODEVENTMASKALL
 Value : SCEN_CHANGE
 Value : SCEN_SETFOCUS
 Value : SCEN_KILLFOCUS
 Value : SCE_GC_DEFAULT
 Value : SCE_GC_COMMENTLINE
 Value : SCE_GC_COMMENTBLOCK
 Value : SCE_GC_GLOBAL
 Value : SCE_GC_EVENT
 Value : SCE_GC_ATTRIBUTE
 Value : SCE_GC_CONTROL
 Value : SCE_GC_COMMAND
 Value : SCE_GC_STRING
 Value : SCE_GC_OPERATOR
*/
		#endregion

	}
}

