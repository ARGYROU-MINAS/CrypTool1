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
    {
        private int AlgID;
        private DlgEditor _lastNotifiedForm = null;
        private CrypTool.AppLogic.CrypSymModern crypModern;
        
        public DlgKeySymModern(DlgEditor _EditForm)
        {
            _lastNotifiedForm = _EditForm;
            InitializeComponent();
            getAlgItems();
            getPadModes();
        }
        private void getAlgItems()
        {
            CrypTool.AppLogic.CrypSymModern crpMdrn = new CrypTool.AppLogic.CrypSymModern();
            for (int i = 0; i < crpMdrn.getAlgTitle().Length; i++)
                comboBoxAlgTitle.Items.Add(crpMdrn.getAlgTitle()[i]);
            comboBoxAlgTitle.SelectedIndex = 0;
        }
        private void getPadModes()
        {
            CrypTool.AppLogic.CrypSymModern crpMdrn = new CrypTool.AppLogic.CrypSymModern();
            for (int i = 0; i < crpMdrn.getPaddingMode().Length; i++)
                comboBoxPadding.Items.Add(crpMdrn.getPaddingMode()[i]);
            comboBoxPadding.SelectedIndex = 1; //Zeros Padding
        }
        private void Encrypt(object sender, RoutedEventArgs arg)
        {
            int KeySize = int.Parse(comboBoxKeyLen.Text);
            int AlgID = 0;
            string passPhrase = textBoxKey.Text;
            int ciphMode = 0;
            int padMode = 0;
            string IV = "0123456789ABCDEF";

            byte[] plainText = System.Text.Encoding.Unicode.GetBytes(_lastNotifiedForm.getPlainText());

            byte[] cipherText = this.crypModern.CrypSymModernEncrypt(passPhrase, KeySize, plainText,ciphMode,padMode,IV);
            _lastNotifiedForm.setCipherText(Convert.ToBase64String(cipherText),this.crypModern.getAlgTitle()[AlgID]);
        }
        private void Decrypt(object sender, RoutedEventArgs arg)
        {
            int KeySize = int.Parse(comboBoxKeyLen.Text);
            string passPhrase = textBoxKey.Text;
            int ciphMode = 0;
            int padMode = 0;
            string IV = "0123456789ABCDEF";

            byte[] cipherText = Convert.FromBase64String(_lastNotifiedForm.getPlainText());

            //byte[] plainText = AppLogic.CrypSymModern.CrypSymModernDecrypt(this.AlgID, passPhrase, KeySize, cipherText);
            //_lastNotifiedForm.setCipherText(Encoding.Unicode.GetString(plainText,0,plainText.Length),this.AlgTitle[this.AlgID]);
        }
        private void Cancel(object sender, RoutedEventArgs arg)
        {
            Close();
        }
        private void getDefaultIV(object sender, RoutedEventArgs arg)
        {
            this.textBoxIV.Text = this.crypModern.getDefaultIV();
            this.textBoxIV.IsReadOnly = true;
        }
        private void getManualIV(object sender, RoutedEventArgs arg)
        {
            this.textBoxIV.Text = this.crypModern.getDefaultIV();
            this.textBoxIV.IsReadOnly = false;
        }
        private void getInternalRandomIV(object sender, RoutedEventArgs arg)
        {
            this.textBoxIV.Text = this.crypModern.getIntRandIV();
            this.textBoxIV.IsReadOnly = true;
        }
        private void getKeySize()
        {
            int[] tmpKeySize = this.crypModern.getKeySize();
            this.comboBoxKeyLen.Items.Clear();
            for (int i = 0; i < tmpKeySize.Length ; i++)
                this.comboBoxKeyLen.Items.Add(tmpKeySize[i].ToString());
            this.comboBoxKeyLen.SelectedIndex = 0;
        }
        private void setAlgID(object sender, RoutedEventArgs arg)
        {
            this.AlgID = comboBoxAlgTitle.SelectedIndex;
            this.crypModern = new CrypTool.AppLogic.CrypSymModern(this.AlgID);
            getKeySize();
        }
    }
}