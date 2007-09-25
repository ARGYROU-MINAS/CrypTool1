using System;

namespace CrypTool.PluginBase
{
    [AttributeUsage(AttributeTargets.Class)]
    public class PluginIDAttribute : Attribute
    {
        public readonly Guid ID;

        public PluginIDAttribute(string id)
        {
            this.ID = new Guid(id);
        }
    }
}
