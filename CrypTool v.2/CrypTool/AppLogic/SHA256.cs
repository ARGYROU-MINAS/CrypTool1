using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class SHA256
    {
        private string strHashValue;

        public SHA256(string Data)
        {
            System.Security.Cryptography.SHA256 sha256 = System.Security.Cryptography.SHA256.Create();
            byte[] DataBytes = sha256.ComputeHash(Encoding.Default.GetBytes(Data));

            StringBuilder strHash = new StringBuilder();
            for (int i = 0; i < DataBytes.Length; i++)
                strHash.Append(DataBytes[i].ToString("x2"));

            this.strHashValue = strHash.ToString();
        }
        public string getHashValue()
        {
            return strHashValue;
        }
    }
}
