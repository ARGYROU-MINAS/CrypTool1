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
        
        public DlgKeySymModern(DlgMain _DlgMain, DlgEditor _EditForm)
        {
            this.Owner = _DlgMain;
            _lastNotifiedForm = _EditForm;
            InitializeComponent();
            updateLang();
            getAlgItems();
            getPadModes();
            getCipherModes();
            setKeyInputMethod();
        }
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);

            Title = String.Format("{0}", CrypTool.AppLogic.XmlLangReader.getXMLItem("Title/SymmetricCryptographie", "Header"));
        }
        private void getAlgItems()
        {
            CrypTool.AppLogic.CrypSymModern crpMdrn = new CrypTool.AppLogic.CrypSymModern();
            for (int i = 0; i < crpMdrn.getAlgTitle().Length; i++)
                comboBoxAlgTitle.Items.Add(crpMdrn.getAlgTitle()[i]);
            comboBoxAlgTitle.SelectedIndex = 0;
        }
        private void getCipherModes()
        {
            CrypTool.AppLogic.CrypSymModern crpMdrn = new CrypTool.AppLogic.CrypSymModern();
            for (int i = 0; i < crpMdrn.getCipherModes().Length; i++)
                comboBoxCipherMode.Items.Add(crpMdrn.getCipherModes()[i]);
            comboBoxCipherMode.SelectedIndex = 0;
                
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
            int KeySize = int.Parse(this.comboBoxKeyLen.Text);
            int AlgID = this.comboBoxAlgTitle.SelectedIndex;
            string passPhrase = this.textBoxKey.Text;
            int ciphMode = this.comboBoxCipherMode.SelectedIndex;
            int padMode = this.comboBoxPadding.SelectedIndex;
            string IV = this.textBoxIV.Text;

            byte[] plainText = System.Text.Encoding.Unicode.GetBytes(_lastNotifiedForm.getPlainText());

            byte[] cipherText = this.crypModern.CrypSymModernEncrypt(passPhrase, KeySize, plainText,ciphMode,padMode,IV);
            _lastNotifiedForm.setCipherText(Convert.ToBase64String(cipherText),this.crypModern.getAlgTitle()[AlgID]);
        }
        private void Decrypt(object sender, RoutedEventArgs arg)
        {
            int KeySize = int.Parse(this.comboBoxKeyLen.Text);
            int AlgID = this.comboBoxAlgTitle.SelectedIndex;
            string passPhrase = this.textBoxKey.Text;
            int ciphMode = this.comboBoxCipherMode.SelectedIndex;
            int padMode = this.comboBoxPadding.SelectedIndex;
            string IV = this.textBoxIV.Text;

            byte[] cipherText = Convert.FromBase64String(_lastNotifiedForm.getPlainText());

            byte[] plainText = this.crypModern.CrypSymModernDecrypt(passPhrase, KeySize, cipherText,ciphMode,padMode,IV);
            _lastNotifiedForm.setCipherText(Encoding.Unicode.GetString(plainText,0,plainText.Length),this.crypModern.getAlgTitle()[AlgID]);
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
        private void setAlgInfo()
        {
            this.textBoxInfo.Text = this.crypModern.getAlgInfo();
        }
        private void setKeyInputMethod()
        {
            this.comboBoxKeyInputMethod.Items.Add("String");
            this.comboBoxKeyInputMethod.Items.Add("HEX");
            this.comboBoxKeyInputMethod.SelectedIndex = 0;
        }
        private void setAlgID(object sender, RoutedEventArgs arg)
        {
            this.AlgID = comboBoxAlgTitle.SelectedIndex;
            this.crypModern = new CrypTool.AppLogic.CrypSymModern(this.AlgID);
            getKeySize();
            setAlgInfo();
        }
    }
}