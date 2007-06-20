using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Collections;

namespace CrypTool.AppLogic
{
    public class OpenFileHistory
    {
        private ArrayList openFileList = new ArrayList();

        private void readOpenFileHistoryItems()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("CrypTool.xml");

            XmlElement root = doc.DocumentElement;

            //for (int i = 0; i < openFileList.Count; i++)
            //    this.openFileList.Add(root.SelectSingleNode("./OpenFileHistory" + i.ToString()).InnerText);

            this.openFileList.Add(root.SelectSingleNode("./OpenFileHistory1").InnerText);
            //this.openFileList[0] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[1] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[2] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[3] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[4] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[5] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[6] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[7] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[8] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
            //this.openFileList[9] = root.SelectSingleNode("./OpenFileHistory0").InnerText;
        }
        public string[] getOpenFileList()
        {
            readOpenFileHistoryItems();
            string[] strOpenFiles = new string[this.openFileList.Count];
            return strOpenFiles;
        }
    }
}


