using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using CrypTool.PluginBase;

namespace CrypTool.MD5
{
    public class MD5 : IHashAlgorithmSettings
    {
        public MD5()
        {

        }
        public string getMd5Hash(Stream inputData)
        {
            MD5Cng md5Hash = new MD5Cng();
            byte[] data = md5Hash.ComputeHash(inputData);

            StringBuilder sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }

            return sBuilder.ToString();            
        }
        public bool verifyMd5Hash(Stream inputData, string hash)
        {
            string hashOfInputData = getMd5Hash(inputData);

            StringComparer comparer = StringComparer.OrdinalIgnoreCase;

            if(0 == comparer.Compare(hashOfInputData, hash))
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
