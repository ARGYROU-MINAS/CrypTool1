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
using System.IO;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgKeySymModern.xaml
    /// </summary>

    public partial class DlgKeySymModern : System.Windows.Window
    {        /// 0 = IDEA
        /// 1 = RC2
        /// 2 = RC4
        /// 3 = DES (ECB)
        /// 4 = DES (CBC)
        /// 5 = Triple DES (ECB)
        /// 6 = Triple DES (CBC)
        /// 7 = Mars
        /// 8 = RC6
        /// 9 = Rijndael (AES)
        /// 10 = Serpent
        /// 11 = Twofish
        private string[] AlgTitle = {   "IDEA","RC2","RC4","DES (ECB)","DES (CBC)","Trple DES (ECB)","Triple DES (CBC)",
                                        "Mars","RC6","Rijndael (AES)","Serpent","Twofish"};
        private int AlgID;
        private DlgEditor _lastNotifiedForm = null;

        public DlgKeySymModern(DlgEditor _EditForm, ArrayList arKeyLen, int AlgID)
        {
            _lastNotifiedForm = _EditForm;
            InitializeComponent();
            setKeyLen(arKeyLen);
            this.AlgID = AlgID;
        }
        private void setKeyLen(ArrayList arKeyLen)
        {
            for (int i = 0; i < arKeyLen.Count; i++)
                comboBoxKeyLen.Items.Add(arKeyLen[i].ToString());
        }
        private void Encrypt(object sender, RoutedEventArgs arg)
        {
            int KeySize = int.Parse(comboBoxKeyLen.Text);
            string passPhrase = textBox1.Text;
            int ciphMode = 0;
            int padMode = 0;
            string IV = "0123456789ABCDEF";

            byte[] plainText = System.Text.Encoding.Unicode.GetBytes(_lastNotifiedForm.getPlainText());

            CrypTool.AppLogic.CrypSymModern crypModern = new CrypTool.AppLogic.CrypSymModern();
            byte[] cipherText = crypModern.CrypSymModernEncrypt(this.AlgID, passPhrase, KeySize, plainText,ciphMode,padMode,IV);
            _lastNotifiedForm.setCipherText(Convert.ToBase64String(cipherText),this.AlgTitle[this.AlgID]);
        }
        private void Decrypt(object sender, RoutedEventArgs arg)
        {
            int KeySize = int.Parse(comboBoxKeyLen.Text);
            string passPhrase = textBox1.Text;
            int ciphMode = 0;
            int padMode = 0;
            string IV = "0123456789ABCDEF";

            byte[] cipherText = Convert.FromBase64String(_lastNotifiedForm.getPlainText());

            CrypTool.AppLogic.CrypSymModern crypModern = new CrypTool.AppLogic.CrypSymModern();
            //byte[] plainText = AppLogic.CrypSymModern.CrypSymModernDecrypt(this.AlgID, passPhrase, KeySize, cipherText);
            //_lastNotifiedForm.setCipherText(Encoding.Unicode.GetString(plainText,0,plainText.Length),this.AlgTitle[this.AlgID]);
        }
        private void Cancel(object sender, RoutedEventArgs arg)
        {
            Close();
        }

    }
}