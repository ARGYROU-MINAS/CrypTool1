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
        public static byte[] CrypSymModernEncrypt(int AlgID,int KeySize,int BlockSize,byte[] PlainText)
        {
            switch (AlgID)
            { 
                case 9:
                    RijndaelEncrypt(KeySize,BlockSize,PlainText);
                    break;
            }
            return globalCipherText;
        }
        public static byte[] CrypSymModernDecrypt(int AlgID, int KeySize,int BlockSize,byte[] CipherText)
        {
            switch (AlgID)
            { 
                case 9:
                    RijndaelDecrypt(KeySize, BlockSize, CipherText);
                    break;
            }
            return globalPlainText;
        }
        private static void RijndaelEncrypt(int KeySize,int BlockSize, byte[] PlainText)
        {
            RijndaelManaged cipher = new RijndaelManaged();
            ICryptoTransform encryptor = cipher.CreateEncryptor();
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void RijndaelDecrypt(int KeySize, int BlockSize, byte[] CipherText)
        {
            //byte[] iv = Encoding.ASCII.GetBytes("@1B2c3D4e5F6g7H8");
            //byte[] saltvalue = Encoding.ASCII.GetBytes("s@1tValue");
            //string passphrase = "Pas5pr@se";
            //PasswordDeriveBytes pass = new PasswordDeriveBytes(passphrase,saltvalue);
            //byte[] keybytes = pass.GetBytes(256 / 8);
            //RijndaelManaged cipher = new RijndaelManaged();
            //ICryptoTransform decryptor = cipher.CreateDecryptor(keybytes,iv);
            //MemoryStream memoryStream = new MemoryStream(CipherText);
            //CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);

            //byte[] fromEncrypt = new byte[CipherText.Length];

            //int len = cryptoStream.Read(fromEncrypt, 0, 3);

            //globalPlainText = new byte[len];
            //Array.Copy(fromEncrypt, globalPlainText, len);            

            RijndaelManaged cipher = new RijndaelManaged();
            ICryptoTransform decryptor = cipher.CreateDecryptor();
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Write);
            cryptoStream.Write(CipherText, 0, CipherText.Length);
            cryptoStream.Close();

            globalPlainText = memoryStream.ToArray();

            memoryStream.Close();
            cipher.Clear();
        }

    }
}
