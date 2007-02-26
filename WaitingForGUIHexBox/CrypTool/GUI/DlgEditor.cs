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
        System.Windows.Window FormMain;

        public DlgEditor(System.Windows.Window FormMain)
        {
            InitializeComponent();
            this.FormMain = FormMain;
        }
        public DlgEditor(System.Windows.Window FormMain, Stream stream)
        {
            InitializeComponent();
            this.FormMain = FormMain;
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

        private void DlgEditor_Activated(object sender, EventArgs e)
        {
            
        }
        public void setText(String sText)
        {
            this.Text = sText;
        }
    }
}