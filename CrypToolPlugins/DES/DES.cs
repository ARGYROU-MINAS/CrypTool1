using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.DES
{
    public class DES : IEncryptionAlgorithm, IEncryptionAlgorithmSettings
    {
        public Stream Encrypt(Stream inputData, string passPhrase, byte[] desKey, byte[] desIV)
        {
            DESCryptoServiceProvider desCipher = new DESCryptoServiceProvider();
            desCipher.Key = desKey;
            desCipher.IV = desIV;
            //desCipher.Padding = 
            //desCipher.Mode = 

            ICryptoTransform encryptor = desCipher.CreateEncryptor(desCipher.Key, desCipher.IV);
            MemoryStream outputData = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(outputData, encryptor, CryptoStreamMode.Write);

            StreamWriter streamWriter = new StreamWriter(outputData);


            
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
