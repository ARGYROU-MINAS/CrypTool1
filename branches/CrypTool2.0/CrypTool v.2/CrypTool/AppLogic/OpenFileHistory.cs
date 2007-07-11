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
            readOpenFileHistoryItems();
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

            for (int i = 0; i < nodeItems; i++)
            {
                nodeList = doc.GetElementsByTagName("OpenFileHistory" + i.ToString());
                
            }
        }
        public void delFileItem(String sFilePath)
        {
            this.openFileList.Remove(sFilePath);
        }
        public void inserNewFileItem(String sFilePath)
        {
            this.openFileList.Insert(0, sFilePath);
        }
    }
}


