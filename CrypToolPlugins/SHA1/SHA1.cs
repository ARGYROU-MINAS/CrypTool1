using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Cryptography;
using CrypTool.PluginBase;
using System.IO;

namespace CrypTool.SHA1
{
    public class SHA1 : IHashAlgorithm, IHashAlgorithmSettings
    {
        public string getSha1Hash(Stream inputData)
        {
            SHA1Cng sha1Hash = new SHA1Cng();
            byte[] data = sha1Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();
        }
        public bool verifySha1Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getSha1Hash(inputData);

            StringComparer comparer = StringComparer.OrdinalIgnoreCase;

            if (0 == comparer.Compare(hashOfInputData, hash))
            {
                return true;
            }
            else
            {
                return false;
            }
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
