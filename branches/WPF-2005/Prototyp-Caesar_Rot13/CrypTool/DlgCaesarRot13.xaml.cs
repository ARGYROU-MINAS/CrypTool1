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

            strAlphabetLen  = "Das Alphabet (";
            strAlphabetLen += Interface.TextOptions.getAlphabet().Length.ToString();
            strAlphabetLen += " Zeichen) wir abgebildet";

            label3.Content = strAlphabetLen;
            textBox2.Text = Interface.TextOptions.getAlphabet();

        }
        private void onEncode(object sender, RoutedEventArgs e)
        {

        }
    }
}