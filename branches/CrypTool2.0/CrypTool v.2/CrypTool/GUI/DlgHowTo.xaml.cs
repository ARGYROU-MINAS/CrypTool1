using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgHowTo.xaml
    /// </summary>

    public partial class DlgHowTo : System.Windows.Window
    {

        public DlgHowTo()
        {
            InitializeComponent();
            updateLang();
        }
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);

            Title = String.Format("{0}", CrypTool.AppLogic.XmlLangReader.getXMLItem("Labels/HowToStart", "Header"));
        }
        private void ButtonClose_OnClick(object sender, RoutedEventArgs arg)
        {
            checkShowAgain();
            Close();
        }
        private void checkShowAgain()
        {
            if ((bool)this.checkBoxShowAgain.IsChecked)
            {
                CrypTool.AppLogic.StartOptions startOptions = new CrypTool.AppLogic.StartOptions();
                startOptions.setShowHowToStartDialog(false);
                startOptions.saveOptions();
            }
        }
    }
}