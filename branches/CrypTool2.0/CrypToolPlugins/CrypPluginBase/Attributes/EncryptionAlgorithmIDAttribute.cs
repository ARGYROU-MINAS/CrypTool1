using System;

namespace CrypTool.PluginBase
{
    [AttributeUsage(AttributeTargets.Class)]
    public class EncryptionAlgorithmIDAttribute : Attribute
    {
        public readonly Guid ID;

        public EncryptionAlgorithmIDAttribute(Guid id)
        {
            this.ID = id;
        }
    }
}
