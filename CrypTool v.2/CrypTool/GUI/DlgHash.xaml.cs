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
            getMD5();
        }
        private void OnButtonClose(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void getMD5()
        {
            MD5 md5 = MD5.Create();

            byte[] data = md5.ComputeHash(Encoding.Default.GetBytes(_lastNotifiedForm.getPlainText()));

            StringBuilder str = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
                str.Append(data[i].ToString("x2"));

            textBox1.Text = str.ToString();
        }

    }
}