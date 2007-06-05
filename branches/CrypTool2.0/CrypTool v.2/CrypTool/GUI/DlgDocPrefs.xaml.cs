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
    /// Interaction logic for DlgDocPrefs.xaml
    /// </summary>

    public partial class DlgDocPrefs : System.Windows.Window
    {
        private DlgEditor _lastNotifiedForm = null;


        public DlgDocPrefs(DlgEditor _EditForm)
        {
            this._lastNotifiedForm = _EditForm;
            InitializeComponent();
            getDocInfo();
        }
        private void ButtonClose_OnClick(object sender, RoutedEventArgs arg)
        {
            this.Close();
        }
        private void getDocInfo()
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            CrypTool.AppLogic.DocProperties docProp = new CrypTool.AppLogic.DocProperties(dlgEditor.getPlainTextPath());

            this.labelWindowTitle.Content = dlgEditor.getPlainTextTabTitle();
            this.labelFileName.Content = docProp.getShortFileName();

        }

    }
}