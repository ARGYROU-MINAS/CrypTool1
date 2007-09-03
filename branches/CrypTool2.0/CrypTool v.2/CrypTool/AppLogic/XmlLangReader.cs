using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace CrypTool.AppLogic
{
    public static class XmlLangReader
    {
        /// <summary>
        /// Get Node inner text
        /// </summary>
        /// <param name="XmlNode"></param>
        /// <returns></returns>
        public static String getXMLItem(String XmlNode)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("." + CrypTool.AppLogic.LanguageOptions.getSelLangFullPath());

            XmlElement root = doc.DocumentElement;

            return root.SelectSingleNode(XmlNode).InnerText;
        }
        /// <summary>
        /// Get Node attribute inner text
        /// </summary>
        /// <param name="XmlNode"></param>
        /// <param name="Attribute"></param>
        /// <returns></returns>
        public static String getXMLItem(String XmlNode, String Attribute)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("." + CrypTool.AppLogic.LanguageOptions.getSelLangFullPath());

            XmlElement root = doc.DocumentElement;

            return root.SelectSingleNode(XmlNode).Attributes[Attribute].InnerText;
        }
    }
}
