using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.RC2
{
    public class RC2 : IEncryptionAlgorithm, IEncryptionAlgorithmSettings
    {

        /// <summary>
        /// Encrypt a stream
        /// </summary>
        /// <param name="inputData">The original stream</param>
        /// <param name="rc2Key">The RC2 key to encrypt</param>
        /// <param name="rc2IV">The RC2 initial vector</param>
        /// <returns>The encrypted stream</returns>
        public Stream Encrypt(Stream inputData, byte[] rc2Key, byte[] rc2IV)
        {
            RC2CryptoServiceProvider rc2Cipher = new RC2CryptoServiceProvider();
            rc2Cipher.Key = rc2Key;
            rc2Cipher.IV = rc2IV;

            ICryptoTransform encryptor = rc2Cipher.CreateEncryptor(rc2Cipher.Key, rc2Cipher.IV);
            MemoryStream outputData = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(outputData, encryptor, CryptoStreamMode.Write);

            StreamWriter streamWriter = new StreamWriter(cryptoStream);
            streamWriter.Write(inputData);
            streamWriter.Flush();
            cryptoStream.FlushFinalBlock();
            streamWriter.Flush();

            return outputData;
        }

        /// <summary>
        /// Decrypt a crypted stream
        /// </summary>
        /// <param name="inputData">The encrypted stream</param>
        /// <param name="rc2Key">The RC2 key to decrypt</param>
        /// <param name="rc2IV">The RC2 initial vector</param>
        /// <returns>The decrypted stream</returns>
        public Stream Decrypt(Stream inputData, byte[] rc2Key, byte[] rc2IV)
        {
            RC2CryptoServiceProvider rc2Cipher = new RC2CryptoServiceProvider();
            rc2Cipher.Key = rc2Key;
            rc2Cipher.IV = rc2IV;

            ICryptoTransform decryptor = rc2Cipher.CreateDecryptor(rc2Cipher.Key, rc2Cipher.IV);
            MemoryStream outputData = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(outputData, decryptor, CryptoStreamMode.Read);

            StreamReader streamReader = new StreamReader(cryptoStream);

            return streamReader.BaseStream;
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
