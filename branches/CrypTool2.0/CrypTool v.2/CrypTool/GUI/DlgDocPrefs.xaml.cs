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
    /// Interaction logic for DlgDocPrefs.xaml
    /// </summary>

    public partial class DlgDocPrefs : System.Windows.Window
    {
        private DlgEditor _lastNotifiedForm = null;


        public DlgDocPrefs(DlgMain _DlgMain,DlgEditor _EditForm)
        {
            this.Owner = _DlgMain;
            this._lastNotifiedForm = _EditForm;
            InitializeComponent();
            getDocInfo();
        }
        private void ButtonClose_OnClick(object sender, RoutedEventArgs arg)
        {
            this.Close();
        }
        private void getDocInfo()
        {
            DlgEditor dlgEditor = this._lastNotifiedForm;
            CrypTool.AppLogic.DocProperties docProp = new CrypTool.AppLogic.DocProperties(dlgEditor.getPlainTextPath());

            this.labelWindowTitle.Content = dlgEditor.getPlainTextTabTitle();
            this.labelFileName.Content = docProp.getShortFileName();
            this.labelDocumentType.Content = docProp.getFileExtension();
            this.labelDocumentSize.Content = docProp.getFileSize() + " bytes";
            this.labelDocumentAttributes.Content = docProp.getFileAttributes().ToString();
            this.labelDocumentCreationTime.Content = docProp.getFileCreationTime().ToLongDateString() + ", "
                + docProp.getFileCreationTime().ToLongTimeString();
            this.labelDocumentLastAccessTime.Content = docProp.getFileLastAccessTime().ToLongDateString() + ", "
                + docProp.getFileLastAccessTime().ToLongTimeString();
            this.labelDocumentLastWriteTime.Content = docProp.getFileLasWriteTime().ToLongDateString() + ", "
                + docProp.getFileLasWriteTime().ToLongTimeString();
            this.labelFilePath.Content = docProp.getFilePath();
            this.labelDocumentPath.Content = docProp.getPathForDocuments();
            this.labelTempFilePath.Content = docProp.getPathForTempFiles();

        }

    }
}