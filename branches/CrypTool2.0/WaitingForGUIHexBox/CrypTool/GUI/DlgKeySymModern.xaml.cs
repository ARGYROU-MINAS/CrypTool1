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
            int BlockSize = KeySize / 8;
            Stream stream = _lastNotifiedForm.getPlainText();
            //_lastNotifiedForm.setCipherText(stream);
            byte[] PlainText = new byte[1024];
            _lastNotifiedForm.getPlainText().Read(PlainText, 0, PlainText.Length);

            byte[] CipherText = AppLogic.CrypSymModern.CrypSymModernEncrypt(this.AlgID, KeySize, BlockSize, 0);
        }
        private void Decrypt(object sender, RoutedEventArgs arg)
        {

        }
        private void Cancel(object sender, RoutedEventArgs arg)
        {
            Close();
        }

    }
}