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
using System.Collections;

namespace CrypTool
{
    /// <summary>
    /// Interaction logic for DlgKeySymModern.xaml
    /// </summary>

    public partial class DlgKeySymModern : System.Windows.Window
    {
        private ArrayList arKeyLen;

        public DlgKeySymModern(ArrayList arKeyLen)
        {
            this.arKeyLen = arKeyLen;
            InitializeComponent();
            setKeyLen();

            String test = "
        }
        private void setKeyLen()
        {
            for (int i = 0; i < this.arKeyLen.Count; i++)
                comboBoxKeyLen.Items.Add(this.arKeyLen[i].ToString());
        }

    }
}