using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class SHA384
    {
        private string strHashValue;

        public SHA384(string Data)
        {
            System.Security.Cryptography.SHA384 sha384 = System.Security.Cryptography.SHA384.Create();
            byte[] DataByte = sha384.ComputeHash(Encoding.Default.GetBytes(Data));

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
