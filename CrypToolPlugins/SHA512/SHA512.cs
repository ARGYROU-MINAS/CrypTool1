using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.SHA512
{
    public class SHA512 : IHashAlgorithm, IHashAlgorithmSettings
    {
        public string getSha512Hash(Stream inputData)
        {
            SHA512Cng sha512Hash = new SHA512Cng();
            byte[] data = sha512Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();
        }

        public bool verifySha512Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getSha512Hash(inputData);

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
