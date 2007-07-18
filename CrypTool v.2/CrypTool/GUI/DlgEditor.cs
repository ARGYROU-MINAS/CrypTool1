using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace CrypTool
{
    public partial class DlgEditor : Form
    {
        private DlgMain _FormMainReference = null;
        private string DlgText;
        private bool hasSavePath; //true: file hast save path
        private string sPlainTextPath;
        private RichTextBoxFinds FindOptions = RichTextBoxFinds.None;

        public DlgEditor(DlgMain _MainForm,string Title)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
            setTitle();
            tabPagePlainText.Text = Title;
            checkSaveStatus(false);
            this.hasSavePath = false;
        }
        public DlgEditor(DlgMain _MainForm, Stream stream,string Title)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
            setTitle();
            richTextBoxPlaintext.LoadFile(stream,RichTextBoxStreamType.PlainText);
            tabPagePlainText.Text = Title;
            checkSaveStatus(true);
            this.hasSavePath = true;
        }
        public void savePlainText(Stream stream)
        {
            richTextBoxPlaintext.SaveFile(stream, RichTextBoxStreamType.PlainText);
            checkSaveStatus(false);
            this.hasSavePath = true;
        }
        public void setCipherText(string cipherText,string Title)
        {
            RichTextBox rtCipherText = new RichTextBox();
            rtCipherText.Name = "rtCipherText";
            rtCipherText.Dock = DockStyle.Fill;
            rtCipherText.Text = cipherText;

            TabPage tpCipherText = new TabPage(Title);
            tpCipherText.Name = "tpCipherText";
            tpCipherText.Controls.Add(rtCipherText);
            tabControl1.TabPages.Add(tpCipherText);

            tabControl1.SelectedIndex = tabControl1.TabPages.Count - 1;
        }
        public void setCipherTextHEX(string cipherText,string Title)
        {
            Be.Windows.Forms.HexBox hexBoxCipherText = new Be.Windows.Forms.HexBox();
            hexBoxCipherText.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            hexBoxCipherText.HexCasing = Be.Windows.Forms.HexCasing.Lower;
            hexBoxCipherText.LineInfoVisible = true;
            hexBoxCipherText.SelectionLength = ((long)(0));
            hexBoxCipherText.SelectionStart = ((long)(-1));
            hexBoxCipherText.ShadowSelectionColor = System.Drawing.Color.FromArgb(((System.Byte)(100)), ((System.Byte)(60)), ((System.Byte)(188)), ((System.Byte)(255)));
            hexBoxCipherText.StringViewVisible = true;
            hexBoxCipherText.UseFixedBytesPerLine = true;
            hexBoxCipherText.VScrollBarVisible = true;
            hexBoxCipherText.Name = "hexBoxCipherText";
            hexBoxCipherText.Dock = DockStyle.Fill;
            

            Be.Windows.Forms.FileByteProvider fileByteProvider = new Be.Windows.Forms.FileByteProvider(cipherText);
            hexBoxCipherText.ByteProvider = fileByteProvider;
            
            TabPage tpCipherText = new TabPage(Title);
            tpCipherText.Name = "tpCipherText";
            tpCipherText.Controls.Add(hexBoxCipherText);
            tabControl1.TabPages.Add(tpCipherText);

            tabControl1.SelectedIndex = tabControl1.TabPages.Count - 1;
        }

        public void setPlainText(string plainText, string Title)
        {
            RichTextBox rtPlainText = new RichTextBox();
            rtPlainText.Name = "rtPlaintext";
            rtPlainText.Dock = DockStyle.Fill;
            rtPlainText.Text = plainText;

            TabPage tpPlainText = new TabPage(Title);
            tpPlainText.Name = "tpPlainText";
            tpPlainText.Controls.Add(rtPlainText);
            tabControl1.TabPages.Add(tpPlainText);

            tabControl1.SelectedIndex = tabControl1.TabPages.Count - 1;
        }
        public string getPlainText()
        {
            return richTextBoxPlaintext.Text;
        }
        public string getCipherText()
        {
            return richTextBoxPlaintext.Text;
        }
        private void DlgEditor_Activated(object sender, EventArgs e)
        {
            _FormMainReference.mainFormNotify(this);
            setActiveText();
            setOtherFormNonActive();
        }
        public void setTitle()
        {
            this.DlgText = "CrypTool-Editor";
            setActiveText();
        }
        public void setPlainTextTabTitle(string sTitle)
        {
            this.sPlainTextPath = sTitle;
            this.tabPagePlainText.Text = this.sPlainTextPath;
        }
        public string getPlainTextTabTitle()
        {
            return this.tabPagePlainText.Text;
        }
        public string getPlainTextPath()
        {
            return this.sPlainTextPath;
        }
        private void setActiveText()
        {
            this.Text = this.DlgText + " - [Active]";
        }
        private void checkSaveStatus(bool saveStatus)
        {
            if (saveStatus)
                if(!(this.Text.IndexOf("*") > -1))
                    this.Text = this.Text + "*";
            else if (this.Text.IndexOf("*") > -1)
                this.Text.Remove(this.Text.IndexOf("*"), 1);
        }
        public void setNonActiveText()
        {
            this.Text = this.DlgText;
        }
        public void setOtherFormNonActive()
        {
            _FormMainReference.setOtherChildFormNonActive();
        }
        public bool getHasSavePath()
        {
            return this.hasSavePath;
        }
        private void richTextBoxPlaintext_TextChanged(object sender, EventArgs e)
        {
            checkSaveStatus(true);
        }

        #region Edit Menu
        private void menuItemUndo_Click(object sender, EventArgs e)
        {
            doUndo();
        }
        public void doUndo()
        {
            this.richTextBoxPlaintext.Undo();
        }
        public bool getUndo()
        {
            return this.richTextBoxPlaintext.CanUndo;
        }
        private void redoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doRedo();
        }
        public void doRedo()
        {
            this.richTextBoxPlaintext.Redo();
        }
        public bool getRedo()
        {
            return this.richTextBoxPlaintext.CanRedo;
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doCut();
        }
        public void doCut()
        {
            this.richTextBoxPlaintext.Cut();
        }
        public bool getCut()
        {
            if (this.richTextBoxPlaintext.SelectedText.Length > 0)
                return true;
            else
                return false;
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doCopy();
        }
        public void doCopy()
        {
            this.richTextBoxPlaintext.Copy();
        }
        public bool getCopy()
        {
            if (this.richTextBoxPlaintext.SelectedText.Length > 0)
                return true;
            else
                return false;
        }
        private void pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doPaste();
        }
        public void doPaste()
        {
            this.richTextBoxPlaintext.Paste();
        }
        public bool getPaste()
        {
            DataFormats.Format pasteFormat = DataFormats.GetFormat(DataFormats.UnicodeText);
            return this.richTextBoxPlaintext.CanPaste(pasteFormat);
        }
        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doDelete();
        }
        public void doDelete()
        {
            this.richTextBoxPlaintext.Text = "";
        }

        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            doSelectAll();
        }
        public void doSelectAll()
        {
            this.richTextBoxPlaintext.SelectAll();
        }
        private void contextMenuRichTextBoxPlain_Opening(object sender, CancelEventArgs e)
        {
            this.redoToolStripMenuItem.Enabled = getRedo();
            this.pasteToolStripMenuItem.Enabled = getPaste();
            this.menuItemUndo.Enabled = getUndo();
            this.copyToolStripMenuItem.Enabled = getCopy();
            this.cutToolStripMenuItem.Enabled = getCut();
        }
        #endregion

        #region Find/Replace
        public void findText(String strFindText)
        {
            CrypTool.AppLogic.GlobalValues.addSearchValue(strFindText);

            int startIndex;
            int endIndex;

            if ((this.FindOptions & RichTextBoxFinds.Reverse) == RichTextBoxFinds.Reverse)
            {
                startIndex = 0;
                endIndex = this.richTextBoxPlaintext.SelectionStart;
            }
            else
            {
                startIndex = this.richTextBoxPlaintext.SelectionStart + this.richTextBoxPlaintext.SelectionLength;
                endIndex = this.richTextBoxPlaintext.Text.Length;
            }
            int findIndex = this.richTextBoxPlaintext.Find(strFindText, startIndex, endIndex, this.FindOptions);

            if (findIndex >= 0)
            {
                this.richTextBoxPlaintext.Select(findIndex, strFindText.Length);
                this.richTextBoxPlaintext.Focus();
            }
            else
            {
                MessageBox.Show("No more occurences found", "Find complete", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        public void setFindOptions(bool MatchCase, bool WholeWords, bool Reverse)
        {
            this.FindOptions = RichTextBoxFinds.None;
            if (MatchCase)
                this.FindOptions |= RichTextBoxFinds.MatchCase;
            if (WholeWords)
                this.FindOptions |= RichTextBoxFinds.WholeWord;
            if (Reverse)
                this.FindOptions |= RichTextBoxFinds.Reverse;
        }
        public void replaceText(String strReplaceText)
        {
            this.richTextBoxPlaintext.SelectedText = strReplaceText;
            this.richTextBoxPlaintext.Focus();
        }
        public void replaceAllText(String strReplaceText, String strFindText)
        {
            this.richTextBoxPlaintext.Text.Replace(strFindText, strReplaceText);
            this.richTextBoxPlaintext.Focus();
        }
        #endregion
    }
}