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
        private char cKey;
        private int iKey;

        public Rot13Caesar()
        {
            setAlphArray();
        }
        public Rot13Caesar(char cKey)
        {
            this.cKey = cKey;
            setAlphArray();
            setCipherAlphArray();
            setKeyPos(cKey);
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
                int c = (this.cAlphArray[i] + this.cKey) % this.cAlphArray.Length;
                this.cCipherAlphArray[i] = this.cAlphArray[c];
            }
        }
        private bool checkRot13Status()
        {
            if ((CrypTool.AppLogic.TextOptions.getAlphabet().Length % 2) == 1)
                return true;
            else
                return false;
        }
        private int getCipherChar(char cChar)
        {
            for (int i = 0; i < this.cAlphArray.Length; i++)
                if (this.cAlphArray[i] == cChar)
                    return i;
            return 0;
        }
        private void setKeyPos(char cKey)
        {
            for (int i = 0; i < this.cAlphArray.Length; i++)
                if (this.cAlphArray[i] == cKey)
                {
                    this.iKey = i;
                    return;
                }
        }
        public void setKey(char cKey)
        {
            this.cKey = cKey;
            setKeyPos(cKey);
        }
        public char[] getCipherAlph()
        {
           return this.cCipherAlphArray;
        }
        public bool getRot13Status()
        {
            return checkRot13Status();
        }
        public byte[] Encrypt(byte[] PlainText)
        {
            int iPos;
            byte[] CipherText = new byte[PlainText.Length];
            for (int i = 0; i < PlainText.Length; i++)
            {
                //iPos = ((char)PlainText[i] + this.cKey) % this.cAlphArray.Length;
                CipherText[i] = (byte)this.cAlphArray[i];
            }
            
            return CipherText;
        }
        public byte[] Decrypt(byte[] CipherText)
        {
            return CipherText;
        }
    }
}
