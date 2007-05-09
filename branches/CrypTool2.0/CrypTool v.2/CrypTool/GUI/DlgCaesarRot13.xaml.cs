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

        public DlgCaesarRot13()
        {
            InitializeComponent();
            getSettings();
        }
        private void Encode(object sender, RoutedEventArgs e)
        {
            //CrypTool.AppLogic.Rot13Caesar rot = new CrypTool.AppLogic.Rot13Caesar();
            //byte[] Key = { "A" };
            //byte[] IV = { "Hallo" };
            //ICryptoTransform trans = rot.CreateEncryptor(Key, IV);
        
        }
        private void Decode(object sender, RoutedEventArgs e)
        { 
        
        }
        private void CloseDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void getSettings()
        {
            this.textBoxAlph.Text = AppLogic.TextOptions.getAlphabet();
            this.label3.Content = "Das Alphabet (" + AppLogic.TextOptions.getAlphabet().Length.ToString() +
                " Zeichen) wir abgebildet";
        }
        private void getCipherAlph(object sender, RoutedEventArgs a)
        {
            String strKey = this.textBoxKey.Text;

            if (CrypTool.AppLogic.TextOptions.getAlphabet().IndexOf(strKey) > -1)
            {
                CrypTool.AppLogic.Rot13Caesar rot13 = new CrypTool.AppLogic.Rot13Caesar(this.textBoxKey.Text.ToCharArray());
                this.textBoxCipherAlph.Text = new String(rot13.getCipherAlph());
            }
        }

    }
}