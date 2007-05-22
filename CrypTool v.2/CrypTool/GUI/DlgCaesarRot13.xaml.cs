using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Security.Cryptography;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgCaesarRot13.xaml
    /// </summary>

    public partial class DlgCaesarRot13 : Window
    {
        private bool AlphInput;
        private int FirstPos;

        private DlgEditor _lastNotifiedForm = null;
        CrypTool.AppLogic.Rot13Caesar rot13;

        public DlgCaesarRot13(DlgEditor _EditForm)
        {
            this._lastNotifiedForm = _EditForm;
            InitializeComponent();
            this.rot13 = new CrypTool.AppLogic.Rot13Caesar();
            this.AlphInput = true;
            this.FirstPos = 0;
            getSettings();
        }
        private void Encode(object sender, RoutedEventArgs e)
        {
            byte[] plainText = System.Text.Encoding.Unicode.GetBytes(_lastNotifiedForm.getPlainText());
            
            byte[] cipherText = this.rot13.Encrypt(plainText);
            _lastNotifiedForm.setCipherText(System.Text.Encoding.Unicode.GetString(cipherText),"CeasarRot13");
        }
        private void Decode(object sender, RoutedEventArgs e)
        {
            byte[] cipherText = System.Text.Encoding.Unicode.GetBytes(_lastNotifiedForm.getPlainText());
            byte[] plainText = this.rot13.Decrypt(cipherText);
            _lastNotifiedForm.setCipherText(System.Text.Encoding.Unicode.GetString(plainText), "CeasarRot13");
        }
        private void CloseDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void getRot13Char(object sender, RoutedEventArgs arg)
        {
            if (this.rot13.getRot13Status())
                this.textBoxKey.Text = this.rot13.getRot13Char().ToString();
        }
        private void getSettings()
        {
            this.textBoxAlph.Text = AppLogic.TextOptions.getAlphabet();
            this.label3.Content = "Das Alphabet (" + AppLogic.TextOptions.getAlphabet().Length.ToString() +
                " Zeichen) wird abgebildet";
            //Rot13 Status
            if (this.rot13.getRot13Status())
                this.textBoxRot13Status.Visibility = Visibility.Hidden;
            else
                this.textBoxRot13Status.Visibility = Visibility.Visible;
            this.radioButtonRot13.IsEnabled = this.rot13.getRot13Status();

            //Alphabet or value input
            this.textBoxKey.IsEnabled = this.AlphInput;
            this.textBoxKeyCif.IsEnabled = !this.AlphInput;
        }
        private void OnTextBoxKey_Changed(object sender, RoutedEventArgs arg)
        {
            getCipherAlph(this.textBoxKey.Text);
        }
        private void getCipherAlph(String strKey)
        {
            if (strKey.Length > 0 && CrypTool.AppLogic.TextOptions.getAlphabet().IndexOf(strKey) > -1)
            {
                this.rot13 = new CrypTool.AppLogic.Rot13Caesar(strKey.ToCharArray()[0],this.FirstPos);
                this.textBoxCipherAlph.Text = new String(rot13.getCipherAlph());
            }
            else
            {
                this.textBoxCipherAlph.Text = "";
                this.textBoxKey.Text = "";
            }

        }
        private void OnRadioButtonAlph_Click(object sender, RoutedEventArgs arg)
        {
            this.AlphInput = true;
            getSettings();
        }
        private void OnRadioButtonCif_Click(object sender, RoutedEventArgs arg)
        {
            this.AlphInput = false;
            getSettings();
        }
        private void OnRadioButtonFirstPosZero_Click(object sender, RoutedEventArgs arg)
        {
            this.FirstPos = 0;
        }
        private void OnRadioButtonFirstPosOne_Click(object sender, RoutedEventArgs arg)
        {
            this.FirstPos = 1;
        }

    }
}