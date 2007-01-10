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
using CrypTool.AppLogic;
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
            showDlgData();
        }
        private void CloseDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void showDlgData()
        {
            String strAlphabetLen;

            strAlphabetLen = "Das Alphabet (";
            strAlphabetLen += AppLogic.TextOptions.getAlphabet().Length.ToString();
            strAlphabetLen += " Zeichen) wir abgebildet";

            label3.Content = strAlphabetLen;
            textBox2.Text = AppLogic.TextOptions.getAlphabet();

        }
        private void onEncode(object sender, RoutedEventArgs e)
        {
            Rot13Caesar rot = new Rot13Caesar();

            System.IO.MemoryStream ms = new System.IO.MemoryStream();

            //create Rot13 Encryptor from this instance
            ICryptoTransform encrypt = rot.CreateEncryptor();

            CryptoStream cryptostream = new CryptoStream(ms, encrypt, CryptoStreamMode.Write);

            cryptostream.Write(Encoding.Unicode.GetBytes(textBox1.Text), 0, Encoding.Unicode.GetBytes(textBox1.Text).Length);

            cryptostream.Close();

            textBox1.Text = Encoding.Unicode.GetString(ms.ToArray());
        }
        private void onDecode(object sender, RoutedEventArgs e)
        {
            Rot13Caesar rot = new Rot13Caesar();

            System.IO.MemoryStream ms = new System.IO.MemoryStream();

            ICryptoTransform decrypt = rot.CreateDecryptor();

            CryptoStream cryptostream = new CryptoStream(ms, decrypt, CryptoStreamMode.Write);

            cryptostream.Write(Encoding.Unicode.GetBytes(textBox1.Text), 0, Encoding.Unicode.GetBytes(textBox1.Text).Length);
            cryptostream.Close();
            textBox1.Text = Encoding.Unicode.GetString(ms.ToArray());
        }
    }
}