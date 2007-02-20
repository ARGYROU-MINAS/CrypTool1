using System.Runtime.InteropServices;
using System;

namespace Scintilla
{
	public class WinAPI 
	{

		[DllImport("kernel32")]
		public extern static IntPtr LoadLibrary(string lpLibFileName);

		[DllImport ("user32")]
		public static extern IntPtr CreateWindowEx(
			uint dwExStyle, string lpClassName, string lpWindowName,
			uint dwStyle, int x, int y, int width, int height, IntPtr hWndParent,
			int hMenu, IntPtr hInstance, string lpParam);

		[DllImport("kernel32",EntryPoint="SendMessage")]
		public static extern int SendMessageStr(
			IntPtr hWnd,
			int message,
			int data,
			string s);

	}
}

