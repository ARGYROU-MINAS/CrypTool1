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
        public String getLongFileName()
        {
            return this.fileInfo.FullName;
        }
        public String getFilePath()
        {
            return this.fileInfo.DirectoryName;
        }
        public long getFileSize()
        {
            return this.fileInfo.Length;
        }
        public FileAttributes getFileAttributes()
        {
            return this.fileInfo.Attributes;
        }
        public DateTime getFileCreationTime()
        {
            return this.fileInfo.CreationTime;
        }
        public String getFileExtension()
        {
            return this.fileInfo.Extension;
        }
        public DateTime getFileLastAccessTime()
        {
            return this.fileInfo.LastAccessTime;
        }
        public DateTime getFileLasWriteTime()
        {
            return this.fileInfo.LastWriteTime;
        }
        public String getPathForDocuments()
        {
            return System.Reflection.Assembly.GetCallingAssembly().Location;
        }
        public String getPathForTempFiles()
        {
            return Path.GetTempPath();
        }
    }
}
