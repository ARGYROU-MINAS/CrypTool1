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
using System.Xml;


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
        System.Drawing.Printing.PrintDocument printDoc;

        public DlgMain()
        {
            InitializeComponent();
            _unnamedForm = 1;
            updateLang();
            getLangItems();
            MarkSelectedLang();
            System.Windows.Forms.Application.EnableVisualStyles();
            printDoc = new System.Drawing.Printing.PrintDocument();
            getOpenFileHistoryItems();
            this.Loaded += new RoutedEventHandler(DlgMain_Loaded);
            this.Closing += new System.ComponentModel.CancelEventHandler(DlgMain_Closing);
        }

        void DlgMain_Loaded(object sender, RoutedEventArgs e)
        {
            ShowExampleFile();
            ShowHowToDialog();
        }

        void DlgMain_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            foreach (DlgEditor dlgEditor in _childFormList)
            {
                dlgEditor.Close();
            }
        }

        public void updateLang()
        {
            String selLangFullPath = CrypTool.AppLogic.LanguageOptions.getSelLangFullPath();
            XmlDataProvider xmlData = (XmlDataProvider)(this.FindResource("Lang"));
            xmlData.Source = new Uri(selLangFullPath, UriKind.Relative);
        }
        public double getLocationTop()
        {
            return this.Top;
        }
        public double getLoactionLeft()
        {
            return this.Left;
        }
        private void CloseDlgMain(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void ShowDlgCaesarRot13(object sender, RoutedEventArgs e)
        {
            DlgCaesarRot13 dlgCaesarRot13 = new DlgCaesarRot13(this,_lastNotifiedForm);
            dlgCaesarRot13.ShowDialog();
        }
        private void ShowDlgTextOptions(object sender, RoutedEventArgs e)
        {
            DlgOptions dlgTextOptions = new DlgOptions(this);
            dlgTextOptions.ShowDialog();
        }
        private void MenuItemNew_OnClick(object sender, RoutedEventArgs e)
        {
            string Title = "Unnamed[" + this._unnamedForm.ToString() + "]";
            DlgEditor dlgEditor = new DlgEditor(this,Title);
            _unnamedForm++;
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
                        CrypTool.AppLogic.OpenFileHistory openFile = new CrypTool.AppLogic.OpenFileHistory();
                        openFile.inserNewFileItem(fileInfo.FullName);
                        getOpenFileHistoryItems();
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
                _unnamedForm--;
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
            DlgHash dlgHash = new DlgHash(this,_lastNotifiedForm);
            dlgHash.ShowDialog();
        }
        private void ShowDlgDocPrefs(object sender, RoutedEventArgs e)
        {
            DlgDocPrefs dlgDocPrefs = new DlgDocPrefs(this,_lastNotifiedForm);
            dlgDocPrefs.ShowDialog();
        }
        private void ShowDlgKeySymModern(object sender, RoutedEventArgs e)
        {
            DlgKeySymModern dlgKeySymModern = new DlgKeySymModern(this,_lastNotifiedForm);
            dlgKeySymModern.ShowDialog();
        }
        private void PrintDialog(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.PrintDialog pDialog = new System.Windows.Forms.PrintDialog();
            pDialog.Document = printDoc;
            if (pDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                DlgEditor dlgEditor = _lastNotifiedForm;
                CrypTool.AppLogic.DocPrint docPrint = new CrypTool.AppLogic.DocPrint(dlgEditor.getPlainText(), printDoc);
                docPrint.PrintDoc();
            }            
        }
        private void PrintDialogPreview(object sender, RoutedEventArgs e)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            CrypTool.AppLogic.DocPrint docPrint = new CrypTool.AppLogic.DocPrint(dlgEditor.getPlainText(), printDoc);
            
            System.Windows.Forms.PrintPreviewDialog pPreview = new System.Windows.Forms.PrintPreviewDialog();
            pPreview.Document = docPrint.getPrintDoc();
            pPreview.ShowDialog();
        }
        private void DocSetup(object sender, RoutedEventArgs e)
        {
            PageSetupDialog pSetup = new PageSetupDialog();
            pSetup.PageSettings = printDoc.DefaultPageSettings;
            pSetup.ShowDialog();
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
        private void getOpenFileHistoryItems()
        {
            MenuItemOpenFileHistory.Items.Clear();
            CrypTool.AppLogic.OpenFileHistory openFile = new CrypTool.AppLogic.OpenFileHistory();
            string[] openFiles = openFile.getOpenFileList();
            System.Windows.Controls.MenuItem[] menuItemOpenFile = new System.Windows.Controls.MenuItem[openFiles.Length];
            for (int i = 0; i < openFiles.Length; i++)
            {
                menuItemOpenFile[i] = new System.Windows.Controls.MenuItem();
                menuItemOpenFile[i].Name = "menItemOpenFile" + i.ToString();
                menuItemOpenFile[i].Header = openFiles[i];
                menuItemOpenFile[i].Click += new RoutedEventHandler(this.openFileHistoryItem);
                MenuItemOpenFileHistory.Items.Add(menuItemOpenFile[i]);
            }
        }
        private void openFileHistoryItem(object sender, RoutedEventArgs e)
        {
            /// Will nicht laufen, ich kann einfach nicht das selektierte Item auslesen !!!!
            /// 
            //System.Windows.Controls.TreeViewItem tvi = (System.Windows.Controls.TreeViewItem)(this.Menu.ItemContainerGenerator.ContainerFromItem(this.Menu.SelectedItem));
            //System.Windows.MessageBox.Show(tvi.Header.ToString());
            //String file = (String)tvi.Header;

            String sFile = "";

            //try to open file from file history
            try
            {
                System.IO.FileInfo fileInfo = new System.IO.FileInfo(sFile);
                System.IO.FileStream fileStream = fileInfo.OpenRead();
                Stream myStream = fileStream;
                if (myStream != null)
                {
                    DlgEditor dlgEditor = new DlgEditor(this, myStream, fileInfo.FullName);
                    _childFormList.Add(dlgEditor);
                    dlgEditor.setPlainTextTabTitle(fileInfo.FullName);
                    dlgEditor.Show();
                }
                fileStream.Close();
            }
            catch //if path not exit, dele from file history
            {
                CrypTool.AppLogic.OpenFileHistory openFile = new CrypTool.AppLogic.OpenFileHistory();
                openFile.delFileItem(sFile);
            }
        }
        private void ShowHowToDialog()
        {
            CrypTool.AppLogic.StartOptions startOptions = new CrypTool.AppLogic.StartOptions();
            if (startOptions.getShowHowToStartDialog())
            {
                DlgHowTo dlgHowTo = new DlgHowTo();
                dlgHowTo.ShowDialog();
            }
            
        }
        private void ShowExampleFile()
        {
            CrypTool.AppLogic.StartOptions startOptions = new CrypTool.AppLogic.StartOptions();
            if (startOptions.getShowExampleFile())
            {
                XmlDocument doc = new XmlDocument();
                doc.Load("."+CrypTool.AppLogic.LanguageOptions.getSelLangFullPath());

                XmlNodeList nodeList;

                nodeList = doc.GetElementsByTagName("ExampleFileOnStartUp");

                String sFileName = nodeList[0].InnerText;

                try
                {
                    System.IO.FileInfo fileInfo = new System.IO.FileInfo(sFileName);
                    System.IO.FileStream fileStream = fileInfo.OpenRead();
                    Stream myStream = fileStream;
                    if (myStream != null)
                    {
                        DlgEditor dlgEditor = new DlgEditor(this, myStream, fileInfo.FullName);
                        _childFormList.Add(dlgEditor);
                        dlgEditor.setPlainTextTabTitle(fileInfo.FullName);
                        dlgEditor.Show();
                    }
                }
                catch
                {
                    CrypTool.AppLogic.OpenFileHistory openFile = new CrypTool.AppLogic.OpenFileHistory();
                    openFile.delFileItem(sFileName);
                }
            }
        }
        #region Edit-Menu
        private void updateEditMenu()
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            MenuItemUndo.IsEnabled = dlgEditor.getUndo();
            MenuItemRedo.IsEnabled = dlgEditor.getRedo();
            MenuItemCut.IsEnabled = dlgEditor.getCut();
            MenuItemCopy.IsEnabled = dlgEditor.getCopy();
            MenuItemPaste.IsEnabled = dlgEditor.getPaste();
        }
        private void doUndo(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doUndo();
        }
        private void doRedo(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doRedo();
        }
        private void doCut(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doCut();
        }
        private void doCopy(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doCopy();
        }
        private void doPaste(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doPaste();
        }
        private void doDelete(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doDelete();
        }
        private void doSelectAll(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.doSelectAll();
            dlgEditor.Focus();
        }
        private void showKeyDialog(object sender, RoutedEventArgs arg)
        {
            DlgShowKey dlgShowKey = new DlgShowKey(this);
            dlgShowKey.Show();
        }
        private void showDialogFindReplace(object sender, RoutedEventArgs arg)
        {
            DlgFindReplace dlgFindReplace = new DlgFindReplace(this, _lastNotifiedForm);
            dlgFindReplace.Show();
        }
        private void findNext(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.findText(CrypTool.AppLogic.GlobalValues.getCurrentSearchValue());
            dlgEditor.Focus();
        }
        #endregion

        #region MenuItem-View
        private void showAsText(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setPlainText(dlgEditor.getPlainTextHex(),dlgEditor.getPlainTextTabTitle());            
        }
        private void showAsHex(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setPlainTextHEX(dlgEditor.getPlainText(), dlgEditor.getPlainTextTabTitle());
        }
        private void setAlphabetHighLight(object sender, RoutedEventArgs arg)
        {
            if (CrypTool.AppLogic.GlobalValues.getHighLightText())
            {
                CrypTool.AppLogic.GlobalValues.setHighLightText(false);
            }
            else
            {
                CrypTool.AppLogic.GlobalValues.setHighLightText(true);
            }

        }
        private void showEndOfLine(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.showEndOfLine();
        }
        private void setWordWrap(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setWordWrap();
        }
        private void setWhiteSpaces(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setWhiteSpaces();
        }
        private void setFontArial8(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontArial(8);
        }
        private void setFontArial10(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontArial(10);
        }
        private void setFontArial12(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontArial(12);
        }
        private void setFontCourier8(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontCourier(8);
        }
        private void setFontCourier10(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontCourier(10);
        }
        private void setFontCourier12(object sender, RoutedEventArgs arg)
        {
            DlgEditor dlgEditor = _lastNotifiedForm;
            dlgEditor.setFontCourier(12);
        }
        #endregion
    }
}