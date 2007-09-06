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
using System.Collections;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgFindReplace.xaml
    /// </summary>

    public partial class DlgFindReplace : System.Windows.Window
    {
        private DlgEditor _lastNotifiedForm = null;

        public DlgFindReplace(DlgMain _DlgMain,DlgEditor _EditForm)
        {
            this.Owner = _DlgMain;
            this._lastNotifiedForm = _EditForm;
            InitializeComponent();
            updateLang();
            getSearchValues();
            getReplaceValues();
        }
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);

            Title = String.Format("{0}", CrypTool.AppLogic.XmlLangReader.getXMLItem("Titles/FindAndReplace", "Header"));
        }
        private void ButtonFind_OnClick(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            dlgEditor.setFindOptions((bool)CheckBoxMatchCase.IsChecked, (bool)CheckBoxFindReverse.IsChecked,
                (bool)CheckBoxRegularExpression.IsChecked, (bool)checkBoxUseWildcards.IsChecked, (bool)checkBoxWholeWords.IsChecked);
            dlgEditor.findText(this.ComboBoxFind.Text);
        }
        private void ButtonReplace_OnClick(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            dlgEditor.replaceText(this.ComboBoxFind.Text, this.ComboBoxReplace.Text);
        }
        private void ButtonReplaceAll_OnClick(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            dlgEditor.setFindOptions((bool)CheckBoxMatchCase.IsChecked, false /*other wise it doesn't work*/,
                (bool)CheckBoxRegularExpression.IsChecked, (bool)checkBoxUseWildcards.IsChecked, (bool)checkBoxWholeWords.IsChecked);
            dlgEditor.replaceAllText(this.ComboBoxReplace.Text, this.ComboBoxFind.Text);
        }
        private void ButtonCancel_OnClick(object sender, RoutedEventArgs arg)
        {
            Close();
        }
        private void getSearchValues()
        {
            for (int i = 0; i < CrypTool.AppLogic.GlobalValues.getSearchValues().Count; i++)
                this.ComboBoxFind.Items.Add(CrypTool.AppLogic.GlobalValues.getSearchValues()[i].ToString());
            this.ComboBoxFind.SelectedIndex = 0;
        }
        private void getReplaceValues()
        {
            for (int i = 0; i < CrypTool.AppLogic.GlobalValues.getReplaceValues().Count; i++)
                this.ComboBoxFind.Items.Add(CrypTool.AppLogic.GlobalValues.getReplaceValues()[i].ToString());
            this.ComboBoxReplace.SelectedIndex = 0;
        }
        private void setFirstFind(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFirstFind();
        }
    }
}