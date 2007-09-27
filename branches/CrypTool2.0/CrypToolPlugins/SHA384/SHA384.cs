using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.SHA384
{
    public class SHA384 : IHashAlgorithm, IHashAlgorithmSettings
    {
        public string getSha384Hash(Stream inputData)
        {
            SHA384Cng sha384Hash = new SHA384Cng();
            byte[] data = sha384Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();
        }

        public bool verifySha384Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getSha384Hash(inputData);

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
