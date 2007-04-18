using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class SHA1
    {
        private string strHashValue;

        public SHA1(string Data)
        {
            System.Security.Cryptography.SHA1 sha1 = System.Security.Cryptography.SHA1.Create();
            byte[] DataByte = sha1.ComputeHash(Encoding.Default.GetBytes(Data));

            StringBuilder strHash = new StringBuilder();
            for (int i = 0; i < DataByte.Length; i++)
                strHash.Append(DataByte[i].ToString("x2"));

            this.strHashValue = strHash.ToString();
        }
        public string getHashValue()
        {
            return this.strHashValue;
        }
    }
}
