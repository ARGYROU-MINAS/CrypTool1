﻿using System;
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
        /// <summary>
        /// Encrypt a stream
        /// </summary>
        /// <param name="inputData">The original stream</param>
        /// <param name="desKey">The des key to encrypt</param>
        /// <param name="desIV">The des initial vector</param>
        /// <returns>The encrypted stream</returns>
        public Stream Encrypt(Stream inputData, byte[] desKey, byte[] desIV)
        {
            //ToDo - Exception handling

            DESCryptoServiceProvider desCipher = new DESCryptoServiceProvider();
            desCipher.Key = desKey;
            desCipher.IV = desIV;
            //desCipher.Padding = 
            //desCipher.Mode = 

            ICryptoTransform encryptor = desCipher.CreateEncryptor(desCipher.Key, desCipher.IV);
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
        /// <param name="desKey">The des key to decrypt</param>
        /// <param name="desIV">The des initial vector</param>
        /// <returns>The decrypted stream</returns>
        public Stream Decrypt(Stream inputData, byte[] desKey, byte[] desIV)
        {
            DESCryptoServiceProvider desCipher = new DESCryptoServiceProvider();
            desCipher.Key = desKey;
            desCipher.IV = desIV;

            ICryptoTransform decryptor = desCipher.CreateDecryptor(desCipher.Key, desCipher.IV);
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