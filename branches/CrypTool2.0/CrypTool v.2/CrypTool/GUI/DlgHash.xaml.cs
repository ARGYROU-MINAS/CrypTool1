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

using System.Security.Cryptography;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgHash.xaml
    /// </summary>

    public partial class DlgHash : System.Windows.Window
    {
        private DlgEditor _lastNotifiedForm = null;

        CrypTool.AppLogic.MD5 md5;
        CrypTool.AppLogic.SHA1 sha1;
        CrypTool.AppLogic.SHA256 sha256;
        CrypTool.AppLogic.SHA384 sha384;
        CrypTool.AppLogic.SHA512 sha512;

        public DlgHash(DlgMain _DlgMain,DlgEditor _EditForm)
        {
            this.Owner = _DlgMain;
            _lastNotifiedForm = _EditForm;
            InitializeComponent();
            updateLang();
            getHashValues();
        }
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);
        }
        private void OnButtonClose(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void getHashValues()
        {
            string strPlainText = _lastNotifiedForm.getPlainText();

            this.md5 = new CrypTool.AppLogic.MD5(strPlainText);
            textBoxMD5.Text = showHashInBlock(this.md5.getHashValue());

            this.sha1 = new CrypTool.AppLogic.SHA1(strPlainText);
            textBoxSHA1.Text = showHashInBlock(this.sha1.getHashValue());

            this.sha256 = new CrypTool.AppLogic.SHA256(strPlainText);
            textBoxSHA256.Text = showHashInBlock(this.sha256.getHashValue());

            this.sha384 = new CrypTool.AppLogic.SHA384(strPlainText);
            textBoxSHA384.Text = showHashInBlock(this.sha384.getHashValue());

            this.sha512 = new CrypTool.AppLogic.SHA512(strPlainText);
            textBoxSHA512.Text = showHashInBlock(this.sha512.getHashValue());

            setTitle(_lastNotifiedForm.getPlainTextTabTitle());
        }
        private void ButtonShowFileMD5_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.md5.getHashValue(),"MD5");
        }
        private void ButtonShowFileSHA1_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.sha1.getHashValue(),"SHA1");
        }
        private void ButtonShowFileSHA256_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.sha256.getHashValue(),"SHA256");
        }
        private void ButtonShowFileSHA384_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.sha384.getHashValue(),"SHA384");
        }
        private void ButtonShowFileSHA512_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.sha512.getHashValue(),"SHA512");
        }
        private void ButtonShowAllInFiles_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(this.md5.getHashValue(),"MD5");
            showHashFile(this.sha1.getHashValue(),"SHA1");
            showHashFile(this.sha256.getHashValue(),"SHA256");
            showHashFile(this.sha384.getHashValue(),"SHA384");
            showHashFile(this.sha512.getHashValue(),"SHA512");
        }
        private string showHashInBlock(string strHash)
        {
            string strHashBlock = null;

            for (int i = 0; i < strHash.Length; i++)
            {
                strHashBlock += strHash[i];
                if (i % 2 == 1)
                    strHashBlock += " ";
            }
            return strHashBlock;
        }
        private void showHashFile(string HashString,string Title)
        {
            _lastNotifiedForm.setCipherTextHEX(HashString,Title);
        }
        private void setTitle(String strTitle)
        {
            Title = String.Format("{0} <{1}>", CrypTool.AppLogic.XmlLangReader.getXMLItem("./Labels/HashvalueOf","Header"),
                strTitle);
        }
    }
}