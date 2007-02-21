using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Forms;
using System.Text;
using System.Runtime.InteropServices;


namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgMain.xaml
    /// </summary>

    public partial class DlgMain : Window
    {
        [DllImport("user32.dll")]
        private static extern int GetActiveWindow();


        DlgEditor dlgEditor;

        public DlgMain()
        {
            InitializeComponent();
        }
        private void CloseDlgMain(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void ShowDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            DlgCaesarRot13 dlgCaesarRot13 = new DlgCaesarRot13();
            dlgCaesarRot13.Show();
        }
        private void ShowDlgTextOptions(object sender, RoutedEventArgs e)
        {
            DlgTextOptions dlgTextOptions = new DlgTextOptions();
            dlgTextOptions.Show();
        }
        private void MenuItemNew_OnClick(object sender, RoutedEventArgs e)
        {
            dlgEditor = new DlgEditor();
            dlgEditor.Show();
        }
        private void MenuItemOpen_OnClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            //openFileDialog.InitialDirectory =  System.Windows.Application.StartupPath;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Stream myStream = openFileDialog.OpenFile();
                if (null != myStream)
                {
                    //StreamReader reader = new StreamReader(openFileDialog.FileName, Encoding.UTF8);

                    dlgEditor = new DlgEditor(myStream);
                    dlgEditor.Show();
                }
            }

        }
        private void MenuItemSave_OnClick(object sender, RoutedEventArgs e)
        {
            int handle = GetActiveWindow();

            System.Windows.Forms.MessageBox.Show(handle.ToString());
            
            //SaveFileDialog saveFileDialog = new SaveFileDialog();

            //saveFileDialog.RestoreDirectory = true;

            //if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            //{
            //    StreamWriter writer = new StreamWriter(saveFileDialog.FileName, Encoding.UTF8);

            //    writer.Write = dlgEditor.getText();
            //    writer.
            //}
            //StreamReader reader = dlgEditor.getPlainText();
            //dlgEditor.setCipherText(reader);
            
        }
    }
}