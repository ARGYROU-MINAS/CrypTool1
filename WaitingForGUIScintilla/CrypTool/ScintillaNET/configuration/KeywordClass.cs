using System;
using System.Runtime;
using System.Xml.Serialization;

namespace Scintilla.Configuration
{
    [SerializableAttribute()]
    public class KeywordClass : ConfigItem
    {
        [XmlAttributeAttribute()]
        public string name;

        [XmlTextAttribute()]
        public string val;
    }
}
