using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.SHA256
{
    public class SHA256
    {
        public string getSha256Hash(Stream inputData)
        {
            SHA256Cng sha256Hash = new SHA256Cng();
            byte[] data = sha256Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();
        }

        public bool verifySha256Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getSha256Hash(inputData);

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
    }
}
