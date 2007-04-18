using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class SHA512
    {
        private string strHashValue;

        public SHA512(string Data)
        {
            System.Security.Cryptography.SHA512 sha512 = System.Security.Cryptography.SHA512.Create();
            byte[] DataBytes = sha512.ComputeHash(Encoding.Default.GetBytes(Data));

            StringBuilder strHash = new StringBuilder();
            for (int i = 0; i < DataBytes.Length; i++)
                strHash.Append(DataBytes[i].ToString("x2"));

            this.strHashValue = strHash.ToString();
        }
        public string getHashValue()
        {
            return this.strHashValue;
        }
    }
}
