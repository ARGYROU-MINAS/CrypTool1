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
         System.Windows.Controls.MenuItem[] itemLang;

        public DlgMain()
        {
            InitializeComponent();
            getLangItems();
            MarkSelectedLang();
            System.Windows.Forms.Application.EnableVisualStyles();
        }
        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);
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
                                    + "Bin�re Datei (*.hex)|*.hex|"
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
        private void getLangItems()
        {
            String langName;
            String[] langFiles = CrypTool.AppLogic.LanguageOptions.getLangFiles();

            itemLang = new System.Windows.Controls.MenuItem[langFiles.Length];

            for(int i=0;i<langFiles.Length;i++)
            {
                langName = langFiles[i];
                itemLang[i] = new System.Windows.Controls.MenuItem();
                itemLang[i].Header = langName;
                itemLang[i].Click += SelLang_OnClick;
                MenuItemLanguage.Items.Add(itemLang[i]);
            }
        }
        void SelLang_OnClick(object sender, RoutedEventArgs args)
        {
            //first uncheck all MenuItems
            for (int i = 0; i < itemLang.Length; i++)
                itemLang[i].IsChecked = false;

            //check now the selected MenuItem            
            System.Windows.Controls.MenuItem item = args.Source as System.Windows.Controls.MenuItem;
            item.IsChecked = true;
            CrypTool.AppLogic.LanguageOptions.setLang(item.Header.ToString());
            updateLang();
        }
        void MarkSelectedLang()
        {
            //Only on Load
            String strLang = CrypTool.AppLogic.LanguageOptions.getSelLang();
            for (int i = 0; i < itemLang.Length; i++)
                if (itemLang[i].Header.ToString() == strLang)
                    itemLang[i].IsChecked = true;

        }
    }
}