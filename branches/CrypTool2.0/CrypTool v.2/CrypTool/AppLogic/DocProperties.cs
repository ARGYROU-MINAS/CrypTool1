using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CrypTool.AppLogic
{
    public class DocProperties
    {
        FileInfo fileInfo;
        private String sFilePath;

        public DocProperties(String sFilePath)
        {
            this.sFilePath = sFilePath;
            this.fileInfo = new FileInfo(sFilePath);
        }

        public String getShortFileName()
        {
            return this.fileInfo.Name;            
        }
    }
}
