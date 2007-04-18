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

        public DlgEditor(DlgMain _MainForm)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
        }
        public DlgEditor(DlgMain _MainForm, Stream stream)
        {
            _FormMainReference = _MainForm;
            InitializeComponent();
            richTextBoxPlaintext.LoadFile(stream,RichTextBoxStreamType.PlainText);
        }
        public void savePlainText(Stream stream)
        {
            richTextBoxPlaintext.SaveFile(stream, RichTextBoxStreamType.PlainText);
        }
        public void setCipherText(string cipherText)
        {
            RichTextBox rtCipherText = new RichTextBox();
            rtCipherText.Name = "rtCipherText";
            rtCipherText.Dock = DockStyle.Fill;
            rtCipherText.Text = cipherText;

            TabPage tpCipherText = new TabPage("Ciphertext");
            tpCipherText.Name = "tpCipherText";
            tpCipherText.Controls.Add(rtCipherText);
            tabControl1.TabPages.Add(tpCipherText);
        }
        public void setPlainText(string plainText)
        {
            RichTextBox rtPlainText = new RichTextBox();
            rtPlainText.Name = "rtPlaintext";
            rtPlainText.Dock = DockStyle.Fill;
            rtPlainText.Text = plainText;

            TabPage tpPlainText = new TabPage("PlainText");
            tpPlainText.Name = "tpPlainText";
            tpPlainText.Controls.Add(rtPlainText);
            tabControl1.TabPages.Add(tpPlainText);
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
        }
        public void setTitle(String sText)
        {
            this.Text = sText;
        }
    }
}