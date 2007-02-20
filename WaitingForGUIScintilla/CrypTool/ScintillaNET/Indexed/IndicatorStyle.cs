using System;

namespace Scintilla.Indexed
{
	public class IndicatorStyle
	{
		private Scintilla.ScintillaControl instance;
		public IndicatorStyle(Scintilla.ScintillaControl i)
		{
			instance = i;
		}
		public Scintilla.Enums.IndicatorStyle this[int index]
		{
			get
			{
				return (Scintilla.Enums.IndicatorStyle)instance.GetIndicStyle( index );
			}
			set
			{
				instance.SetIndicStyle(index, (int)value);
			}
		}
	}
}
