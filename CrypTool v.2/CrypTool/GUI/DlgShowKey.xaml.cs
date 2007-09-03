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
		public DlgShowKey(DlgMain _DlgMain)
		{
            this.Owner = _DlgMain;
			this.InitializeComponent();

            updateLang();
		}
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);

            Title = String.Format("{0}", CrypTool.AppLogic.XmlLangReader.getXMLItem("Labels/Key", "Header"));
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