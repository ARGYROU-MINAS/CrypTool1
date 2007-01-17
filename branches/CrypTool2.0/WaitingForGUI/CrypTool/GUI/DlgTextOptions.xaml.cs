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
            textBoxTrennzeichen.Text = CrypTool.AppLogic.TextOptions.getTrenn();
            checkBoxUpper.IsChecked = CrypTool.AppLogic.TextOptions.getGrossVal();
            checkBoxLower.IsChecked = CrypTool.AppLogic.TextOptions.getKleinVal();
            checkBoxSpace.IsChecked = CrypTool.AppLogic.TextOptions.getLeerVal();
            checkBoxCif.IsChecked = CrypTool.AppLogic.TextOptions.getZahlVal();
            checkBoxSentence.IsChecked = CrypTool.AppLogic.TextOptions.getSatzVal();

            labelUsedAlphabet.Content = "Zu verwendetes Alphabet (";
            labelUsedAlphabet.Content += CrypTool.AppLogic.TextOptions.getAlphabet().Length.ToString();
            labelUsedAlphabet.Content += " Zeichen):";

            textBoxRefFile.Text = CrypTool.AppLogic.TextOptions.getStrRefFile();
            textBoxAlph.Text = CrypTool.AppLogic.TextOptions.getAlphabet();
            //checkBoxDouble.Checked
            //checkBoxAttentUppLow.Checked
        }

    }
}