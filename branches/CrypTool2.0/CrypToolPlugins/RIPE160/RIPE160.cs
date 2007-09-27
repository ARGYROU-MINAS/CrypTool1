using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.RIPE160
{
    public class RIPE160 : IHashAlgorithm, IHashAlgorithmSettings
    {
        public string getRipe160Hash(Stream inputData)
        {
            RIPEMD160Managed ripe160Hash = new RIPEMD160Managed();
            byte[] data = ripe160Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();
        }

        public bool verifyRipe160Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getRipe160Hash(inputData);

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
