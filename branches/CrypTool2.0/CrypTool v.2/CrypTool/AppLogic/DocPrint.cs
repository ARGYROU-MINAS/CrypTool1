using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class DocPrint
    {
        private string sText;
        private System.Drawing.Printing.PrintDocument printDoc;
        private string[] lines;

        public DocPrint(String sText,System.Drawing.Printing.PrintDocument printDoc)
        {
            this.sText = sText;
            this.printDoc = printDoc;
            this.printDoc.PrintPage += new System.Drawing.Printing.PrintPageEventHandler(OnPrintPage);
        }
        public void PrintDoc()
        {
            this.printDoc.Print();
        }
        public System.Drawing.Printing.PrintDocument getPrintDoc()
        {
            return this.printDoc;
        }

        private void OnPrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            char[] param = { '\n' };
            this.lines = this.sText.Split(param);
            int i = 0;
            char[] trimParam = { '\r' };
            foreach (string s in this.lines)
                lines[i++] = s.TrimEnd(trimParam);

            System.Drawing.Font printFont = new System.Drawing.Font("Courier New",12);
            //int x = e.MarginBounds.Left;
            //int y = e.MarginBounds.Right;
            foreach (string s in this.lines)
                e.Graphics.DrawString(s, printFont, System.Drawing.Brushes.Black, 0,0);
        }
    }
}
