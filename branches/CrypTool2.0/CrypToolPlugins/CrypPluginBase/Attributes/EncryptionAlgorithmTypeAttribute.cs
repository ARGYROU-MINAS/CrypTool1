using System;

namespace CrypTool.PluginBase
{
    [AttributeUsage(AttributeTargets.Class)]
    public class EncryptionAlgorithmTypeAttribute : Attribute
    {
        public readonly EncryptionAlgorithmType EncryptionAlgorithmType;

        public EncryptionAlgorithmTypeAttribute(EncryptionAlgorithmType encryptionAlgorithmType)
        {
            this.EncryptionAlgorithmType = encryptionAlgorithmType;
        }
    }
}
