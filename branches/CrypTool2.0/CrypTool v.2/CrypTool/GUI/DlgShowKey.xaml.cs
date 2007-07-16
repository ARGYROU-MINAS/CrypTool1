using System;
using System.IO;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;

namespace CrypTool
{
	public partial class DlgShowKey
	{
		public DlgShowKey()
		{
			this.InitializeComponent();
			
			// Insert code required on object creation below this point.
		}
        private void ButtonClose_OnClick(object sender, RoutedEventArgs arg)
        {
            Close();
        }
        private void ButtonCopyKey_OnClick(object sender, RoutedEventArgs arg)
        {
            
        }
	}
}