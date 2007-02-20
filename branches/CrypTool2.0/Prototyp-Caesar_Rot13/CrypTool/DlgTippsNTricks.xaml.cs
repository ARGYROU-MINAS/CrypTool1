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
    /// Interaction logic for DlgTippsNTricks.xaml
    /// </summary>

    public partial class DlgTippsNTricks : Window
    {

        public DlgTippsNTricks()
        {
            InitializeComponent();
        }
        public void OnBtnClose(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

    }
}