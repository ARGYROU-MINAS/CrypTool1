using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CrypTool.AppLogic;
using System.Security.Cryptography;

namespace WindowsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            Rot13Caesar rot = new Rot13Caesar();

            System.IO.MemoryStream ms = new System.IO.MemoryStream();

            //create Rot13 Encryptor from this instance
            ICryptoTransform encrypt = rot.CreateEncryptor();



            CryptoStream cryptostream = new CryptoStream(ms, encrypt, CryptoStreamMode.Write);


            cryptostream.Write(Encoding.Unicode.GetBytes(textBox1.Text), 0, Encoding.Unicode.GetBytes(textBox1.Text).Length);


            cryptostream.Close();

   
            textBox1.Text = Encoding.Unicode.GetString(ms.ToArray());
        }
    }
}