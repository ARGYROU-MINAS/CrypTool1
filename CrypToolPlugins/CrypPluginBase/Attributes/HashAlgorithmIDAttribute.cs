using System;

namespace CrypTool.PluginBase
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HashAlgorithmIDAttribute : Attribute
    {
        public readonly Guid ID;

        public HashAlgorithmIDAttribute(Guid id)
        {
            this.ID = id;
        }
    }
}
