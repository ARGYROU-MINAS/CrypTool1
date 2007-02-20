using System;

namespace Scintilla.Indexed
{
	public class MarginType
	{
		private Scintilla.ScintillaControl instance;
		public MarginType(Scintilla.ScintillaControl i)
		{
			instance = i;
		}
		public Scintilla.Enums.MarginType this[int index]
		{
			get
			{
				return (Scintilla.Enums.MarginType)instance.GetMarginTypeN( index );
			}
			set
			{
				instance.SetMarginTypeN(index, (int)value);
			}
		}
	}
}
