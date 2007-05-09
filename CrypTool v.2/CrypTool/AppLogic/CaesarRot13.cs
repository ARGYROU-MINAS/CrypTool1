using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;


namespace CrypTool.AppLogic
{
    public class Rot13Caesar
    {
        private char[] cAlphArray = null;
        private char[] cCipherAlphArray = null;
        private char[] cKey = null;

        public Rot13Caesar()
        {
            setAlphArray();
        }
        public Rot13Caesar(char[] cKey)
        {
            this.cKey = cKey;
            setAlphArray();
            setCipherAlphArray();
        }

        private void setAlphArray()
        {
            this.cAlphArray = CrypTool.AppLogic.TextOptions.getAlphabet().ToCharArray();
        }
        private void setCipherAlphArray()
        {
            this.cCipherAlphArray = new char[this.cAlphArray.Length];

            for (int i = 0; i < this.cAlphArray.Length; i++)
            {
                int c = (this.cAlphArray[i] + this.cKey[0]) % this.cAlphArray.Length;
                this.cCipherAlphArray[i] = this.cAlphArray[c];
            }
        }

        public void setKey(char[] cKey)
        {
            this.cKey = cKey;
        }
        public char[] getCipherAlph()
        {
           return this.cCipherAlphArray;
        }
        //public byte[] Encrypt()
        //{ 
        
        //}
        //public byte[] Decrypt()
        //{ 
        
        //}
    }
}
