using System;

namespace Scintilla
{
	#region "scintilla-events"
    public enum ScintillaEvents
    {    
        styleneeded = 2000,
        charadded = 2001,
        savepointreached = 2002,
        savepointleft = 2003,
        modifyattemptro = 2004,
        key = 2005,
        doubleclick = 2006,
        updateui = 2007,
        modified = 2008,
        macrorecord = 2009,
        marginclick = 2010,
        needshown = 2011,
        painted = 2013,
        userlistselection = 2014,
        uridropped = 2015,
        dwellstart = 2016,
        dwellend = 2017,
        zoom = 2018,
        hotspotclick = 2019,
        hotspotdoubleclick = 2020,
        calltipclick = 2021
    }
	#endregion

	#region "scintilla-delegates"

	public delegate void StyleNeededHandler(ScintillaControl pSender ,int position);

	public delegate void CharAddedHandler(ScintillaControl pSender ,int ch);

	public delegate void SavePointReachedHandler(ScintillaControl pSender );

	public delegate void SavePointLeftHandler(ScintillaControl pSender );

	public delegate void ModifyAttemptROHandler(ScintillaControl pSender );

	public delegate void KeyHandler(ScintillaControl pSender ,int ch,int modifiers);

	public delegate void DoubleClickHandler(ScintillaControl pSender );

	public delegate void UpdateUIHandler(ScintillaControl pSender );

	public delegate void ModifiedHandler(ScintillaControl pSender ,int position,int modificationType,string text,int length,int linesAdded,int line,int foldLevelNow,int foldLevelPrev);

	public delegate void MacroRecordHandler(ScintillaControl pSender ,int message,IntPtr wParam,IntPtr lParam);

	public delegate void MarginClickHandler(ScintillaControl pSender ,int modifiers,int position,int margin);

	public delegate void NeedShownHandler(ScintillaControl pSender ,int position,int length);

	public delegate void PaintedHandler(ScintillaControl pSender );

	public delegate void UserListSelectionHandler(ScintillaControl pSender ,int listType,string text);

	public delegate void URIDroppedHandler(ScintillaControl pSender ,string text);

	public delegate void DwellStartHandler(ScintillaControl pSender ,int position);

	public delegate void DwellEndHandler(ScintillaControl pSender ,int position);

	public delegate void ZoomHandler(ScintillaControl pSender );

	public delegate void HotSpotClickHandler(ScintillaControl pSender ,int modifiers,int position);

	public delegate void HotSpotDoubleClickHandler(ScintillaControl pSender ,int modifiers,int position);

	public delegate void CallTipClickHandler(ScintillaControl pSender ,int position);
	#endregion 
	
	#region "scintilla-modified-delegates"

	public delegate void TextInsertedHandler( ScintillaControl pSender ,int position ,int length , int linesAdded );
	public delegate void TextDeletedHandler( ScintillaControl pSender ,int position ,int length , int linesAdded  );
	public delegate void StyleChangedHandler( ScintillaControl pSender ,int position ,int length );
	public delegate void FoldChangedHandler( ScintillaControl pSender , int line , int foldLevelNow , int foldLevelPrev );
	public delegate void UserPerformedHandler( ScintillaControl pSender );
	public delegate void UndoPerformedHandler( ScintillaControl pSender );
	public delegate void RedoPerformedHandler( ScintillaControl pSender);
	public delegate void LastStepInUndoRedoHandler( ScintillaControl pSender );
	public delegate void MarkerChangedHandler( ScintillaControl pSender , int line );
	public delegate void BeforeInsertHandler( ScintillaControl pSender , int position , int length  );
	public delegate void BeforeDeleteHandler( ScintillaControl pSender , int position , int length );
	#endregion
}
