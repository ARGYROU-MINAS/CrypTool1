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
        private int AlgID;

        public DlgKeySymModern(ArrayList arKeyLen,int AlgID)
        {
            InitializeComponent();
            setKeyLen(arKeyLen);

            this.AlgID = AlgID;
        }
        private void setKeyLen(ArrayList arKeyLen)
        {
            for (int i = 0; i < arKeyLen.Count; i++)
                comboBoxKeyLen.Items.Add(arKeyLen[i].ToString());
        }
        private void Encrypt(object sender, RoutedEventArgs arg)
        { 
            
        }
        private void Decrypt(object sender, RoutedEventArgs arg)
        { 
        
        }
        private void Cancel(object sender, RoutedEventArgs arg)
        { 
            
        }

    }
}