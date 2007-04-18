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

        public DlgHash(DlgEditor _EditForm)
        {
            _lastNotifiedForm = _EditForm;
            InitializeComponent();
            getHashValues();
        }
        private void OnButtonClose(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void getHashValues()
        {
            string strPlainText = _lastNotifiedForm.getPlainText();

            CrypTool.AppLogic.MD5 md5 = new CrypTool.AppLogic.MD5(strPlainText);
            textBoxMD5.Text = md5.getHashValue();

            CrypTool.AppLogic.SHA1 sha1 = new CrypTool.AppLogic.SHA1(strPlainText);
            textBoxSHA1.Text = sha1.getHashValue();

            CrypTool.AppLogic.SHA256 sha256 = new CrypTool.AppLogic.SHA256(strPlainText);
            textBoxSHA256.Text = sha256.getHashValue();

            CrypTool.AppLogic.SHA384 sha384 = new CrypTool.AppLogic.SHA384(strPlainText);
            textBoxSHA384.Text = sha384.getHashValue();

            CrypTool.AppLogic.SHA512 sha512 = new CrypTool.AppLogic.SHA512(strPlainText);
            textBox1SHA512.Text = sha512.getHashValue();
        }
        private void ButtonShowFileMD5_OnClick(object sender, RoutedEventArgs e)
        {
            showHashFile(textBoxMD5.Text);
        }
        private void showHashFile(string HashString)
        {
            _lastNotifiedForm.setCipherTextHEX(HashString);
        }
    }
}