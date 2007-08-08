using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace CrypTool
{
    public partial class DlgEditor : Form
    {
        private DlgMain _FormMainReference = null;
        private Be.Windows.Forms.HexBox hexText;
        private string DlgText;
        private bool hasSavePath; //true: file hast save path
        
        private string sPlainTextPath;
        private string strLastFind;
      
        private bool Wildcards;
        private bool WholeWords;
        private bool Reverse;
        private bool MatchCase;
        private bool RegularExpression;
        private bool isFirstFind = true;
        
        private Regex regex;
        private Match match;

        private CrypTool.AppLogic.AlphabetHighlighter alphKeywordHighlighter;

        private string[] keywords;



        public DlgEditor(DlgMain _MainForm, string Title)
        {
            getKeyWords();
            _FormMainReference = _MainForm;
            InitializeComponent();
            setTitle();
            tabPagePlainText.Text = Title;
            checkSaveStatus(false);
            this.hasSavePath = false;
            
        }
        public DlgEditor(DlgMain _MainForm, Stream stream,string Title)
        {
            getKeyWords();
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
        public void setPlainTextHEX(string plainText, string Title)
        {
            hexText = new Be.Windows.Forms.HexBox();
            hexText.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            hexText.HexCasing = Be.Windows.Forms.HexCasing.Lower;
            hexText.LineInfoVisible = true;
            hexText.SelectionLength = ((long)(0));
            hexText.SelectionStart = ((long)(-1));
            hexText.ShadowSelectionColor = System.Drawing.Color.FromArgb(((System.Byte)(100)), ((System.Byte)(60)), ((System.Byte)(188)), ((System.Byte)(255)));
            hexText.StringViewVisible = true;
            hexText.UseFixedBytesPerLine = true;
            hexText.VScrollBarVisible = true;
            hexText.Name = "hexBoxPlainText";
            hexText.Dock = DockStyle.Fill;


            Be.Windows.Forms.FileByteProvider fileByteProvider = new Be.Windows.Forms.FileByteProvider(plainText);
            hexText.ByteProvider = fileByteProvider;

            TabPage tpCipherText = new TabPage(Title);
            tpCipherText.Name = "tpPlainText";
            tpCipherText.Controls.Add(hexText);
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
        public string getPlainTextHex()
        {
            return hexText.Text;
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
            doHighlightText();
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
            if (strLastFind != strFindText)
            {
                strLastFind = strFindText;
                isFirstFind = true;
            }

            if (isFirstFind)
            {
                regex = getRegExpression(strFindText);
                match = regex.Match(richTextBoxPlaintext.Text);
                isFirstFind = false;
            }
            else
            {
                if (!Reverse)
                    match = regex.Match(richTextBoxPlaintext.Text, match.Index + 1);
                else
                    match = regex.Match(richTextBoxPlaintext.Text, match.Index - 1);
            }

            if (match.Success)
            {
                richTextBoxPlaintext.SelectionStart = match.Index;
                richTextBoxPlaintext.SelectionLength = match.Length;
                richTextBoxPlaintext.Focus();
            }
            else
            {
                MessageBox.Show(String.Format("No more occurences found for '{0}'.   ", strFindText));
                isFirstFind = true;
            }
        }
        public void setFindOptions(bool MatchCase, bool Reverse, bool RegularExpression,bool Wildcards,bool WholeWords)
        {
            this.Wildcards = Wildcards;
            this.MatchCase = MatchCase;
            this.WholeWords = WholeWords;
            this.Reverse = Reverse;
            this.RegularExpression = RegularExpression;
        }
        public void setFirstFind()
        {
            isFirstFind = true;
        }
        public void replaceText(String strFindText, String strReplaceText)
        {
            Regex regexText = getRegExpression(strFindText);
            Match matchText = regexText.Match(richTextBoxPlaintext.SelectedText);

            if (matchText.Success)
            {
                if (matchText.Value == richTextBoxPlaintext.SelectedText)
                    richTextBoxPlaintext.SelectedText = strReplaceText;
            }
            findText(strFindText);
        }
        public void replaceAllText(String strReplaceText, String strFindText)
        {
            Regex regExReplace = getRegExpression(strFindText);
            String strReplacedText;

            int iSelPos = richTextBoxPlaintext.SelectionStart;
            strReplacedText = regExReplace.Replace(richTextBoxPlaintext.Text, strReplaceText);

            if (richTextBoxPlaintext.Text != strReplacedText)
            {
                richTextBoxPlaintext.Text = strReplacedText;
                MessageBox.Show("All occurences replaced.");
                richTextBoxPlaintext.SelectionStart = iSelPos;
            }
            else
            {
                MessageBox.Show(String.Format("No more occurences found for '{0}'.", strFindText));
            }

            this.richTextBoxPlaintext.Focus();
        }
        private Regex getRegExpression(String strFindText)
        {
            Regex result;
            String regExString;

            regExString = strFindText;
            if(this.RegularExpression)
            {
            }
            else if(this.Wildcards)
            {
                regExString = regExString.Replace("*",@"\w*");  //multiple characters wildcard (*)
                regExString = regExString.Replace("?",@"\w");  //single character wildcard (?)

                regExString = String.Format("{0}{1}{0}",@"\b",regExString);
            }
            else
            {
                regExString = Regex.Escape(regExString);
            }

            if(this.WholeWords)
            {
                regExString = String.Format("{0}{1}{0}",@"\b",regExString);
            }
            if(this.MatchCase)
            {
                result = new Regex(regExString);
            }
            else
            {
                result = new Regex(regExString,RegexOptions.IgnoreCase);
            }
            if (Reverse)
            {
                result = new Regex(regExString, RegexOptions.RightToLeft);
            }
            return result;
        }
        public void doSelectAll()
        {
            richTextBoxPlaintext.SelectAll();
        }
        #endregion

        #region View
        private void getKeyWords()
        {
            keywords = new string[CrypTool.AppLogic.TextOptions.getAlphabet().Length];
            for (int i = 0; i < keywords.Length; i++)
                keywords[i] = CrypTool.AppLogic.TextOptions.getAlphabet().Substring(i, 1);
        }
        public CrypTool.AppLogic.AlphabetHighlighter KeywordHilighter
        {
            get
            {
                if (alphKeywordHighlighter == null)
                {
                    alphKeywordHighlighter = new CrypTool.AppLogic.AlphabetHighlighter();
                    alphKeywordHighlighter.RichTextBox = this.richTextBoxPlaintext;
                    alphKeywordHighlighter.AlphKeywords = this.keywords;
                }
                return alphKeywordHighlighter;
            }
        }
        public void doHighlightText()
        {
            if (CrypTool.AppLogic.GlobalValues.getHighLightText())
            {
                int index = richTextBoxPlaintext.SelectionStart;
                KeywordHilighter.HilightAt(index);
            }
        }
        public void showEndOfLine()
        {
            richTextBoxPlaintext.Text = richTextBoxPlaintext.Text.Replace("\b\n", ((char)Convert.ToInt32("#CL/CR#")).ToString());
        }
        public void setWordWrap()
        {
            if (richTextBoxPlaintext.WordWrap)
                richTextBoxPlaintext.WordWrap = false;
            else
                richTextBoxPlaintext.WordWrap = true;
        }
        public void setWhiteSpaces()
        {
            if (!CrypTool.AppLogic.GlobalValues.getWhiteSpaces())
            {
                richTextBoxPlaintext.Text = richTextBoxPlaintext.Text.Replace(" ", Char.ToString((char)129));
            }
            else
            {
                richTextBoxPlaintext.Text = richTextBoxPlaintext.Text.Replace(((char)Convert.ToInt32(149)).ToString(), " ");
            }
        }
        #endregion
    }
}