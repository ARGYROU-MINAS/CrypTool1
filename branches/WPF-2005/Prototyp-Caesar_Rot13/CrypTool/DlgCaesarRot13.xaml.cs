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
        }
        private void CloseDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void onEncode(object sender, RoutedEventArgs e)
        {
            AppLogic.ManTextOptions txtOpt = new AppLogic.ManTextOptions();
                textBox2.Text = txtOpt.getAlphabet();
        }
    }
}