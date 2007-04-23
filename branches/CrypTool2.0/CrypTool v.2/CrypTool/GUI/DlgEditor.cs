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

        public DlgEditor(DlgMain _MainForm,string Title)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
            setTitle();
            tabPagePlainText.Text = Title;
        }
        public DlgEditor(DlgMain _MainForm, Stream stream,string Title)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
            setTitle();
            richTextBoxPlaintext.LoadFile(stream,RichTextBoxStreamType.PlainText);
            tabPagePlainText.Text = Title;
        }
        public void savePlainText(Stream stream)
        {
            richTextBoxPlaintext.SaveFile(stream, RichTextBoxStreamType.PlainText);
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
        private void setActiveText()
        {
            this.Text = this.DlgText + " - [Active]";
        }
        public void setNonActiveText()
        {
            this.Text = this.DlgText;
        }
        public void setOtherFormNonActive()
        {
            _FormMainReference.setOtherChildFormNonActive();
        }
    }
}