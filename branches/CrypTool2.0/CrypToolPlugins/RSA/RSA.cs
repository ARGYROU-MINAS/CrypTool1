using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Cryptography;
using System.IO;
using CrypTool.PluginBase;

namespace CrypTool.RSA
{
    public class RSA : IEncryptionAlgorithm, IEncryptionAlgorithmSettings
    {
        public byte[] Encrypt(byte[] inputData, RSAParameters RSAKeyInfo)
        {
            RSACryptoServiceProvider rsaCipher = new RSACryptoServiceProvider();

            rsaCipher.ImportParameters(RSAKeyInfo);

            return rsaCipher.Encrypt(inputData, false);
        }

        public byte[] Decrypt(byte[] inputData, RSAParameters RSAKeyInfo)
        {
            RSACryptoServiceProvider rsaCipher = new RSACryptoServiceProvider();

            rsaCipher.ImportParameters(RSAKeyInfo);

            return rsaCipher.Decrypt(inputData, false);
        }

        #region IPlugin Members

        public void Initialize()
        {
            throw new NotImplementedException();
        }

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
