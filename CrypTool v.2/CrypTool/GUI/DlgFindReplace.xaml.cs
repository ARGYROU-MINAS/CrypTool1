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
    /// Interaction logic for DlgFindReplace.xaml
    /// </summary>

    public partial class DlgFindReplace : System.Windows.Window
    {
        private DlgEditor _lastNotifiedForm = null;

        public DlgFindReplace(DlgEditor _EditForm)
        {
            this._lastNotifiedForm = _EditForm;
            InitializeComponent();
        }
        private void ButtonFind_OnClick(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            dlgEditor.finText(this.ComboBoxFind.Text);
        }
        private void ButtonReplace_OnClick(object sender, RoutedEventArgs arg)
        {

        }
        private void ButtonReplaceAll_OnClick(object sender, RoutedEventArgs arg)
        {

        }
        private void ButtonCancel_OnClick(object sender, RoutedEventArgs arg)
        {
            Close();
        }
    }
}