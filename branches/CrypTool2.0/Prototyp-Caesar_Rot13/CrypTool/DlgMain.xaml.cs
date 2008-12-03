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
    /// Interaction logic for DlgMain.xaml
    /// </summary>

    public partial class DlgMain : Window
    {
        Window DlgEdit;


        public DlgMain()
        {
            InitializeComponent();

        }
        private void CloseDlgMain(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void OpenDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            DlgCaesarRot13 dlgCaesarRot13 = new DlgCaesarRot13();
            dlgCaesarRot13.ShowDialog();
        }
        private void CreateDlgEdit()
        {
            DlgEdit = new Window();
            DlgEdit.Width = 350;
            DlgEdit.Height = 200;
            DlgEdit.Show();
        }

        private void OpenDlgTextOptions(object sender, RoutedEventArgs e)
        {
            DlgTextOptions dlgTextOption = new DlgTextOptions();
            dlgTextOption.ShowDialog();
        }
        private void OpenDlgAbout(object sender, RoutedEventArgs e)
        {
            AboutBox1 ab = new AboutBox1();
            ab.ShowDialog();
        }

    }
}