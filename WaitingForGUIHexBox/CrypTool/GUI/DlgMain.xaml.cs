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
        private DlgEditor _lastNotifiedForm = null;
        private String selectedLang;
        System.Windows.Controls.MenuItem[] itemLang;

        public DlgMain()
        {
            InitializeComponent();
            getLanguages();
            System.Windows.Forms.Application.EnableVisualStyles();
        }
        public void setLang(String selectedLang)
        {
            this.selectedLang = "/lng/";
            this.selectedLang += selectedLang;
            this.selectedLang += ".xml";
        }
        public String getLang()
        {
            return this.selectedLang;
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
            DlgEditor dlgEditor = new DlgEditor(this);
            dlgEditor.Show();
        }
        private void MenuItemOpen_OnClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.InitialDirectory = System.Windows.Forms.Application.StartupPath;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = true;
            openFileDialog.Filter = "Text Datei (*.txt)|*.txt|Plot Datei (*.plt)|*.plt|"
                                    + "Binäre Datei (*.hex)|*.hex|"
                                    + "OpenGL Datei (*.ogl)|*.ogl|Alle Dateien (*.*)|*.*";
            

            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                foreach(String file in openFileDialog.FileNames)
                {
                    System.IO.FileInfo fileInfo = new System.IO.FileInfo(file);
                    System.IO.FileStream fileStream = fileInfo.OpenRead();
                    Stream myStream = fileStream;
                    if (null != myStream)
                    {
                        DlgEditor dlgEditor = new DlgEditor(this, myStream);
                        dlgEditor.Show();
                    }
                    fileStream.Close();
                }
            }
        }
        internal void mainFormNotify(DlgEditor notifingForm)
        {
            _lastNotifiedForm = notifingForm;
        }
        private void MenuItemSave_OnClick(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text Datei (*.txt)|*.txt|Alle Dateien (*.*)|*.*";
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.InitialDirectory = System.Windows.Forms.Application.StartupPath;

            if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                DlgEditor dlg = _lastNotifiedForm;
                dlg.savePlainText(saveFileDialog.OpenFile());
            }           
        }
        private void MenuItemClose_OnClick(object sender, RoutedEventArgs e)
        {
            DlgEditor dlg = _lastNotifiedForm;
            dlg.Close();
        }
        private void ShowDlgRijndael(object sender, RoutedEventArgs e)
        { 
        
        }
        private void getLanguages()
        {
            String langName;
            DirectoryInfo di = new DirectoryInfo("lng");
            FileInfo[] files = di.GetFiles("*.xml");
            
            foreach (FileInfo fi in files)
            {
                langName = fi.Name;
                langName = langName.Substring(0, langName.IndexOf(".xml"));                
                itemLang[itemLang.Length] = new System.Windows.Controls.MenuItem();
                itemLang[itemLang.Length].Header = langName;
                //itemLang[itemLang.Length].Click += SelLang_OnClick;
                //MenuItemLanguage.Items.Add(itemLang[itemLang.Length]);
            }
        }
        void SelLang_OnClick(object sender, RoutedEventArgs args)
        {
            
            System.Windows.Controls.MenuItem item = args.Source as System.Windows.Controls.MenuItem;
            item.IsChecked = true;
        }
    }
}