using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace AES
{
    public class AES : IEncryptionAlgorithm, IEncryptionAlgorithmSettings
    {
        /// <summary>
        /// Encrypt a stream
        /// </summary>
        /// <param name="inputData">The original stream</param>
        /// <param name="aesKey">The aes key to encrypt</param>
        /// <param name="aesIV">The aes initial vector</param>
        /// <returns>The encrypted stream</returns>
        public Stream Encrypt(Stream inputData, byte[] aesKey, byte[] aesIV)
        {
            AesCryptoServiceProvider aesCipher = new AesCryptoServiceProvider();
            aesCipher.Key = aesKey;
            aesCipher.IV = aesIV;

            ICryptoTransform encryptor = aesCipher.CreateEncryptor(aesCipher.Key, aesCipher.IV);
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
        /// <param name="aesKey">The aes key to decrypt</param>
        /// <param name="aesIV">The aes initial vector</param>
        /// <returns>The decrypted stream</returns>
        public Stream Decrypt(Stream inputData, byte[] aesKey, byte[] aesIV)
        {
            AesCryptoServiceProvider aesCipher = new AesCryptoServiceProvider();
            aesCipher.Key = aesKey;
            aesCipher.IV = aesIV;

            ICryptoTransform decryptor = aesCipher.CreateDecryptor(aesCipher.Key, aesCipher.IV);
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
