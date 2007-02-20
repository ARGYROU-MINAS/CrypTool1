using System;

namespace Scintilla
{
	public struct NotifyHeader 
	{
		// hwndFrom is really an environment specifc window handle or pointer
		// but most clients of Scintilla.h do not have this type visible.
		//WindowID hwndFrom;
		public IntPtr hwndFrom;
		public uint idFrom;
		public uint code;
	};

	public struct SCNotification 
	{
		public NotifyHeader nmhdr;
		public int position;	// SCN_STYLENEEDED, SCN_MODIFIED, SCN_DWELLSTART, SCN_DWELLEND
		public int ch;		// SCN_CHARADDED, SCN_KEY
		public int modifiers;	// SCN_KEY
		public int modificationType;	// SCN_MODIFIED
		public IntPtr text;	// SCN_MODIFIED
		public int length;		// SCN_MODIFIED
		public int linesAdded;	// SCN_MODIFIED
		public int message;	// SCN_MACRORECORD
		public IntPtr wParam;	// SCN_MACRORECORD
		public IntPtr lParam;	// SCN_MACRORECORD
		public int line;		// SCN_MODIFIED
		public int foldLevelNow;	// SCN_MODIFIED
		public int foldLevelPrev;	// SCN_MODIFIED
		public int margin;		// SCN_MARGINCLICK
		public int listType;	// SCN_USERLISTSELECTION
		public int x;			// SCN_DWELLSTART, SCN_DWELLEND
		public int y;		// SCN_DWELLSTART, SCN_DWELLEND
	};

	public struct CharacterRange 
	{
		public long cpMin;
		public long cpMax;
	};

	public struct TextRange 
	{
		public CharacterRange chrg;
		public IntPtr lpstrText;
	};

	public struct TextToFind 
	{
		public CharacterRange chrg;
		public IntPtr lpstrText;
		public CharacterRange chrgText;
	};

}
