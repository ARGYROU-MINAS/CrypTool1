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

        public DocPrint(String sText)
        {
            this.sText = sText;
        }

        private void OnBeginPrint(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            char[] param = { '\n' };
            this.lines = this.sText.Split(param);
            int i = 0;
            char[] trimParam = { '\r' };
            foreach (string s in this.lines)
                lines[i++] = s.TrimEnd(trimParam);

        }
        private void OnPrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            System.Drawing.Font printFont = new System.Drawing.Font("Courier New",12);
            int x = e.MarginBounds.Left;
            int y = e.MarginBounds.Right;
            foreach (string s in this.lines)
                e.Graphics.DrawString(s, printFont, System.Drawing.Brushes.Black, x, y);
        }
    }
}
