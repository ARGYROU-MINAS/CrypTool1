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

            //XmlElement root = doc.DocumentElement;

            XmlNodeList nodeList;

            for (int i = 0; i < nodeItems; i++)
            {
                nodeList = doc.GetElementsByTagName("OpenFileHistory" + i.ToString());
                if (nodeList[0].InnerText.Length > 0)
                    this.openFileList.Add(nodeList[0].InnerText);
            }
            
            //nodeList = doc.GetElementsByTagName("OpenFileHistory0");
            //if(nodeList[0].InnerText.Length > 0)
            //    this.openFileList.Add(nodeList[0].InnerText);
            
            //nodeList = doc.GetElementsByTagName("OpenFileHistory1");
            //if(nodeList[0].in
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory2");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory3");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory4");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory5");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory6");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory7");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory8");
            //this.openFileList.Add(nodeList[0].InnerText);
            //nodeList = doc.GetElementsByTagName("OpenFileHistory9");
            //this.openFileList.Add(nodeList[0].InnerText);

        }
        public string[] getOpenFileList()
        {
            readOpenFileHistoryItems();
            string[] strOpenFiles = new string[this.openFileList.Count];
            for (int i = 0; i < this.openFileList.Count; i++)
                strOpenFiles[i] = this.openFileList[i].ToString();
            return strOpenFiles;
        }
    }
}


