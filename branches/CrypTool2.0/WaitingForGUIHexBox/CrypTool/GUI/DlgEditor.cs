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
        public void setCipherText(Stream stream)
        {
            stream.Position = 0;

            RichTextBox rtCipherText = new RichTextBox();
            rtCipherText.Name = "rtCipherText";
            rtCipherText.Dock = DockStyle.Fill;
            rtCipherText.LoadFile(stream, RichTextBoxStreamType.PlainText);

            TabPage tpCipherText = new TabPage("Ciphertext");
            tpCipherText.Name = "tpCipherText";
            tpCipherText.Controls.Add(rtCipherText);
            tabControl1.TabPages.Add(tpCipherText);
        }
        public Stream getPlainText()
        {
            MemoryStream stream = new MemoryStream();
            richTextBoxPlaintext.SaveFile(stream, RichTextBoxStreamType.PlainText);

            return stream;
        }
        private void DlgEditor_Activated(object sender, EventArgs e)
        {
            _FormMainReference.mainFormNotify(this);
        }
        public void setText(String sText)
        {
            this.Text = sText;
        }
    }
}