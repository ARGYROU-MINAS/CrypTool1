using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Collections;

namespace CrypTool.AppLogic
{
    public class OpenFileHistory
    {
        const int nodeItems = 10;

        private ArrayList openFileList = new ArrayList();

        public OpenFileHistory()
        {
            readOpenFileHistoryItems();
        }

        private void readOpenFileHistoryItems()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("CrypTool.xml");

            XmlNodeList nodeList;

            for (int i = 0; i < nodeItems; i++)
            {
                nodeList = doc.GetElementsByTagName("OpenFileHistory" + i.ToString());
                if (nodeList[0].InnerText.Length > 0)
                    this.openFileList.Add(nodeList[0].InnerText);
            }
        }
        public string[] getOpenFileList()
        {
            string[] strOpenFiles = new string[this.openFileList.Count];
            for (int i = 0; i < this.openFileList.Count; i++)
                strOpenFiles[i] = this.openFileList[i].ToString();
            return strOpenFiles;
        }
        public void saveFileList()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("CrypTool.xml");

            XmlNodeList nodeList;

            for (int i = 0; i < this.openFileList.Count; i++)
            {
                nodeList = doc.GetElementsByTagName("OpenFileHistory" + i.ToString());
                nodeList[0].InnerText = this.openFileList[i].ToString();
            }
            doc.Save("CrypTool.xml");
        }
        public void delFileItem(String sFilePath)
        {
            this.openFileList.Remove(sFilePath);
            saveFileList();
        }
        public void inserNewFileItem(String sFilePath)
        {
            delFileItem(sFilePath);
            this.openFileList.Insert(0, sFilePath);
            if (this.openFileList.Count > 10)
                this.openFileList.RemoveAt(10);
            saveFileList();
        }
    }
}


