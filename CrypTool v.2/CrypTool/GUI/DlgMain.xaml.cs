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
using System.Collections;
using System.Security.Cryptography;


namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgMain.xaml
    /// </summary>

    public partial class DlgMain : Window
    {
        private int _unnamedForm;
        private ArrayList _childFormList = new ArrayList();
        private DlgEditor _lastNotifiedForm = null;
        System.Windows.Controls.MenuItem[] itemLang;


        public DlgMain()
        {
            InitializeComponent();
            this._unnamedForm = 1;
            updateLang();
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
            DlgCaesarRot13 dlgCaesarRot13 = new DlgCaesarRot13(this._lastNotifiedForm);
            dlgCaesarRot13.Show();
        }
        private void ShowDlgTextOptions(object sender, RoutedEventArgs e)
        {
            DlgTextOptions dlgTextOptions = new DlgTextOptions();
            dlgTextOptions.Show();
        }
        private void MenuItemNew_OnClick(object sender, RoutedEventArgs e)
        {
            string Title = "Unnamed[" + this._unnamedForm.ToString() + "]";
            DlgEditor dlgEditor = new DlgEditor(this,Title);
            this._unnamedForm++;
            _childFormList.Add(dlgEditor);
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
                        DlgEditor dlgEditor = new DlgEditor(this, myStream,fileInfo.FullName);
                        _childFormList.Add(dlgEditor);
                        dlgEditor.setPlainTextTabTitle(fileInfo.FullName);
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
            DlgEditor dlg = _lastNotifiedForm;

            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text Datei (*.txt)|*.txt|Alle Dateien (*.*)|*.*";
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.InitialDirectory = System.Windows.Forms.Application.StartupPath;

            if (dlg.getHasSavePath())
            {
                saveFileDialog.FileName = dlg.getPlainTextPath();
                dlg.savePlainText(saveFileDialog.OpenFile());                
            }
            else
                if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    dlg.savePlainText(saveFileDialog.OpenFile());

            dlg.setPlainTextTabTitle(saveFileDialog.FileName);
        }
        private void MenuItemSaveAs_OnClick(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text Datei (*.txt)|*.txt|Alle Dateien (*.*)|*.*";
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.InitialDirectory = System.Windows.Forms.Application.StartupPath;
            if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                DlgEditor dlg = _lastNotifiedForm;
                dlg.savePlainText(saveFileDialog.OpenFile());
                dlg.setPlainTextTabTitle(saveFileDialog.FileName);
            }
        }
        private void MenuItemClose_OnClick(object sender, RoutedEventArgs e)
        {
            DlgEditor dlg = _lastNotifiedForm;
            if (_lastNotifiedForm.Text.IndexOf("[") > 0)
                this._unnamedForm--;
            dlg.Close();

        }
        private void MenuItemCloseAll_OnClick(object sender, RoutedEventArgs e)
        {
            foreach (DlgEditor dlgEditor in _childFormList)
            {
                dlgEditor.Close();
            }
        }
        private void ShowDlgHash(object sender, RoutedEventArgs e)
        {
            DlgHash dlgHash = new DlgHash(_lastNotifiedForm);
            dlgHash.Show();
        }
        private void ShowDlgDocPrefs(object sender, RoutedEventArgs e)
        {
            DlgDocPrefs dlgDocPrefs = new DlgDocPrefs(_lastNotifiedForm);
            dlgDocPrefs.Show();
        }
        private void ShowDlgKeySymModern(object sender, RoutedEventArgs e)
        {
            DlgKeySymModern dlgKeySymModern = new DlgKeySymModern(_lastNotifiedForm);
            dlgKeySymModern.Show();
        }
        private void PrintDialog(object sender, RoutedEventArgs e)
        { 
            
        }
        private void PrintDialogPreview(object sender, RoutedEventArgs e)
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            CrypTool.AppLogic.DocPrint dPrint = new CrypTool.AppLogic.DocPrint();
            dPrint.printPreview(dlgEditor.getPlainText());
        }
        private void PrintSetup(object sender, RoutedEventArgs e)
        {
            CrypTool.AppLogic.DocPrint dPrint = new CrypTool.AppLogic.DocPrint();
            dPrint.prinSetup();

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
        public void setOtherChildFormNonActive()
        {
            foreach (DlgEditor dlgEditor in _childFormList)
            {
                if (dlgEditor != _lastNotifiedForm)
                    dlgEditor.setNonActiveText();
            }
        }
    }
}