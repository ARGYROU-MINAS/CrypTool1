using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;


namespace CrypTool.Rijndael
{
    public class Rijndael : IEncryptionAlgorithm, IEncryptionAlgorithmSettings
    {
        /// <summary>
        /// Encrypt a stream
        /// </summary>
        /// <param name="inputData">The original stream</param>
        /// <param name="rijndaelKey">The rijndael key to encrypt</param>
        /// <param name="rijndaelIV">The rijndael initial vector</param>
        /// <returns>The encrypted stream</returns>
        public Stream Encrypt(Stream inputData, byte[] rijndaelKey, byte[] rijndaelIV)
        {
            RijndaelManaged rijndaelCipher = new RijndaelManaged();
            rijndaelCipher.Key = rijndaelKey;
            rijndaelCipher.IV = rijndaelIV;

            ICryptoTransform encryptor = rijndaelCipher.CreateEncryptor(rijndaelCipher.Key, rijndaelCipher.IV);
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
        /// <param name="rijndaelKey">The rijndael key to decrypt</param>
        /// <param name="rijndaelIV">The rijndael initial vector</param>
        /// <returns>The decrypted stream</returns>
        public Stream Decrypt(Stream inputData, byte[] rijndaelKey, byte[] rijndaelIV)
        {
            RijndaelManaged rijndaelCipher = new RijndaelManaged();
            rijndaelCipher.Key = rijndaelKey;
            rijndaelCipher.IV = rijndaelIV;

            ICryptoTransform decryptor = rijndaelCipher.CreateDecryptor(rijndaelCipher.Key, rijndaelCipher.IV);
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
