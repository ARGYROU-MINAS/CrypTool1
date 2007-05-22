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
        private int iFirstPos;

        public Rot13Caesar()
        {
            setAlphArray();
        }
        public Rot13Caesar(char cKey,int iFirstPos)
        {
            this.cKey = cKey;
            this.iFirstPos = iFirstPos;
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
                int c = (this.cAlphArray[i] + this.cKey + this.iFirstPos) % this.cAlphArray.Length;
                this.cCipherAlphArray[i] = this.cAlphArray[c];
            }
        }
        private bool checkRot13Status()
        {
            int a = CrypTool.AppLogic.TextOptions.getAlphabet().Length % 2;
            if ((CrypTool.AppLogic.TextOptions.getAlphabet().Length % 2) == 0)
                return true;
            else
                return false;
        }
        public int getKeyCif()
        {
            return (cKey % this.cAlphArray.Length);
        }
        public void setKey(char cKey)
        {
            this.cKey = cKey;
        }
        public char[] getCipherAlph()
        {
           return this.cCipherAlphArray;
        }
        public bool getRot13Status()
        {
            return checkRot13Status();
        }
        public char getRot13Char()
        {
            return this.cAlphArray[this.cAlphArray.Length / 2];
        }
        public byte[] Encrypt(byte[] PlainText)
        {
            char[] cPlainText = System.Text.Encoding.Unicode.GetString(PlainText).ToUpper().ToCharArray();
            char[] cCipherText = new char[cPlainText.Length];

            int iPos;
            for (int i = 0; i < cPlainText.Length; i++)
            {
                iPos = (cPlainText[i] + this.cKey + this.iFirstPos) % this.cAlphArray.Length;
                cCipherText[i] = cAlphArray[iPos];
            }

            byte[] bCipherText = System.Text.Encoding.Unicode.GetBytes(cCipherText);
            return bCipherText;
        }
        public byte[] Decrypt(byte[] CipherText)
        {
            char[] cCipherText = System.Text.Encoding.Unicode.GetString(CipherText).ToUpper().ToCharArray();
            char[] cPlainText = new char[cCipherText.Length];
            int iPos;
            for (int i = 0; i < cCipherText.Length; i++)
            {
                iPos = (cCipherText[i] - this.cKey - this.iFirstPos) % this.cAlphArray.Length;
                cPlainText[i] = cAlphArray[iPos];
            }
            byte[] bPlainText = System.Text.Encoding.Unicode.GetBytes(cPlainText);
            return bPlainText;
        }
    }
}
