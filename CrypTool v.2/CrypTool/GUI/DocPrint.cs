using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool
{
    public class DocPrint
    {
        public void printDoc(String sText)
        { 
        
        }
        public void printPreview(String sText)
        {
            System.Windows.Forms.PrintPreviewDialog pPreview = new System.Windows.Forms.PrintPreviewDialog();
            pPreview.ShowDialog();
        }
        private void OnBeginPrint(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            char[] param = { '\n' };

        }
        private void OnPrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        { 
            
        }
    }
}
