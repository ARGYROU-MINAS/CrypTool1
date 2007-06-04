using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CrypToo.AppLogic
{
    public class DocProperties
    {
        private String sFilePath;

        public DocProperties(String sFilePath)
        {
            this.sFilePath = sFilePath;
        }

        public String getShortFileName()
        {
            FileInfo fileInfo = new FileInfo(this.sFilePath);
            
        }
    }
}
