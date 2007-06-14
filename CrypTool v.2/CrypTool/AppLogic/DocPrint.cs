using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class DocPrint
    {
        private string sText;
        private System.Drawing.Printing.PrintDocument printDoc;

        public DocPrint(String sText)
        {
            this.sText = sText;
        }
        public void printDoc()
        { 
        
        }
        public void prinSetup()
        {
            System.Windows.Forms.PageSetupDialog pageSetup = new System.Windows.Forms.PageSetupDialog();
            pageSetup.ShowDialog();
        }
        public void printPreview()
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
