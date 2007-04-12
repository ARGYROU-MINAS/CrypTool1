using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace CrypTool.AppLogic
{
    public static class CrypSymModern
    {
        static private byte[] globalCipherText;
        static private byte[] globalPlainText;
        static private string initVector = "0123456789ABCDEF";

        /// <summary>
        /// 0 = IDEA
        /// 1 = RC2
        /// 2 = RC4
        /// 3 = DES (ECB)
        /// 4 = DES (CBC)
        /// 5 = Triple DES (ECB)
        /// 6 = Triple DES (CBC)
        /// 7 = Mars
        /// 8 = RC6
        /// 9 = Rijndael (AES)
        /// 10 = Serpent
        /// 11 = Twofish
        /// </summary>
        /// <param name="AlgID"></param>
        public static byte[] CrypSymModernEncrypt(int AlgID,string passPhrase, int KeySize, byte[] PlainText)
        {
            switch (AlgID)
            { 
                case 9:
                    RijndaelEncrypt(passPhrase, KeySize,PlainText);
                    break;
            }
            return globalCipherText;
        }
        public static byte[] CrypSymModernDecrypt(int AlgID, string passPhrase, int KeySize, byte[] CipherText)
        {
            switch (AlgID)
            { 
                case 9:
                    RijndaelDecrypt(passPhrase, KeySize, CipherText);
                    break;
            }
            return globalPlainText;
        }
        private static void RijndaelEncrypt(string passPhrase, int KeySize, byte[] PlainText)
        {
            RijndaelManaged cipher = new RijndaelManaged();

            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(initVector);
            cipher.Padding = PaddingMode.Zeros;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key,cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void RijndaelDecrypt(string passPhrase, int KeySize, byte[] CipherText)
        {
            RijndaelManaged cipher = new RijndaelManaged();

            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(initVector);
            cipher.Padding = PaddingMode.Zeros;

            ICryptoTransform decryptor = cipher.CreateDecryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream(CipherText);
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);
            globalPlainText = new byte[CipherText.Length];
            cryptoStream.Read(globalPlainText, 0, globalPlainText.Length);

            memoryStream.Close();
            cryptoStream.Close();
        }
        private static byte[] getpassPhraseByte(string passPhrase, int keySize)
        { 
            //appand 0 when passPhrase too short
            int passPhraseLen = keySize / 8;
            for (int i = passPhrase.Length; i < passPhraseLen; i++)
            {
                passPhrase += "0";
            }
            byte[] passPhraseByte = System.Text.Encoding.ASCII.GetBytes(passPhrase);
            return passPhraseByte;
        }

    }
}
