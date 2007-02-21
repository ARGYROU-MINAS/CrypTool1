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
        public DlgEditor()
        {
            InitializeComponent();
        }
        public DlgEditor(Stream stream)
        {
            InitializeComponent();
            richTextBoxPlaintext.LoadFile(stream,RichTextBoxStreamType.PlainText);
        }
        public StreamReader getPlainText()
        {
            StreamReader reader = new StreamReader("");

            return reader;
        }
        public void setCipherText(StreamReader reader)
        {
            //scintillaControlCipherText.Text = reader.ReadToEnd();
        }
        private void scintillaControl1_Click(object sender, EventArgs e)
        {

        }
    }
}