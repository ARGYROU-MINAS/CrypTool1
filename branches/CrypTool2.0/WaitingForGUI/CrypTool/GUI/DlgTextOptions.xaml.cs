using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgTextOptions.xaml
    /// </summary>

    public partial class DlgTextOptions : Window
    {

        public DlgTextOptions()
        {
            InitializeComponent();
            LoadSettings();
        }
        private void LoadSettings()
        {
            textBoxSeparator.Text = CrypTool.AppLogic.TextOptions.getTrenn();
            checkBoxUpper.IsChecked = CrypTool.AppLogic.TextOptions.getGrossVal();
            checkBoxLower.IsChecked = CrypTool.AppLogic.TextOptions.getKleinVal();
            checkBoxSpace.IsChecked = CrypTool.AppLogic.TextOptions.getLeerVal();
            checkBoxCif.IsChecked = CrypTool.AppLogic.TextOptions.getZahlVal();
            checkBoxPunctuation.IsChecked = CrypTool.AppLogic.TextOptions.getSatzVal();

            labelUsedAlphabet.Content = "Zu verwendetes Alphabet (";
            labelUsedAlphabet.Content += CrypTool.AppLogic.TextOptions.getAlphabet().Length.ToString();
            labelUsedAlphabet.Content += " Zeichen):";

            textBoxRefFile.Text = CrypTool.AppLogic.TextOptions.getStrRefFile();
            textBoxAlph.Text = CrypTool.AppLogic.TextOptions.getAlphabet();
            checkBoxSeparatePairs.IsChecked = CrypTool.AppLogic.TextOptions.getAddx();
            checkBoxDistinguishUpperLower.IsChecked = CrypTool.AppLogic.TextOptions.getCase();
            checkBoxNotInAlph.IsChecked = CrypTool.AppLogic.TextOptions.getFormat();
            checkBoxKeepUpperLower.IsChecked = CrypTool.AppLogic.TextOptions.getConvertCase();
        }
        private void saveSettings()
        {
            CrypTool.AppLogic.TextOptions.setTrenn(textBoxSeparator.Text);
            CrypTool.AppLogic.TextOptions.setGrossVal((bool)checkBoxUpper.IsChecked);
            CrypTool.AppLogic.TextOptions.setKleinVal((bool)checkBoxLower.IsChecked);
            CrypTool.AppLogic.TextOptions.setLeerVal((bool)checkBoxSpace.IsChecked);
            CrypTool.AppLogic.TextOptions.setZahlVal((bool)checkBoxCif.IsChecked);
            CrypTool.AppLogic.TextOptions.setSatzVal((bool)checkBoxPunctuation.IsChecked);
            CrypTool.AppLogic.TextOptions.setStrRefFile(textBoxRefFile.Text);
            CrypTool.AppLogic.TextOptions.setAlphabet(textBoxAlph.Text);
            CrypTool.AppLogic.TextOptions.setAddx((bool)checkBoxSeparatePairs.IsChecked);
            CrypTool.AppLogic.TextOptions.setCase((bool)checkBoxDistinguishUpperLower.IsChecked);
            CrypTool.AppLogic.TextOptions.setFormat((bool)checkBoxNotInAlph.IsChecked);
            CrypTool.AppLogic.TextOptions.setConvertCase((bool)checkBoxKeepUpperLower.IsChecked);
        }
        private void ButtonCancel_OnClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void ButtonDefault_OnClick(object sender, RoutedEventArgs e)
        {
            CrypTool.AppLogic.TextOptions.setDefault();
            LoadSettings();
        }
        private void ButtonApply_OnClick(object sender, RoutedEventArgs e)
        {
            saveSettings();
            Close();
        }

    }
}