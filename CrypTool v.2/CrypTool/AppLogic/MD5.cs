using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;

namespace CrypTool.AppLogic
{
    public class MD5
    {
        private string strHashValue;

        public MD5(string Data)
        {
            System.Security.Cryptography.MD5 md5 = System.Security.Cryptography.MD5.Create();
            byte[] DataByte = md5.ComputeHash(Encoding.Default.GetBytes(Data));

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
