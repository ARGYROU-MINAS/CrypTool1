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

        private PaddingMode[] padMode = {PaddingMode.None,PaddingMode.Zeros,
                                         PaddingMode.PKCS7,PaddingMode.ANSIX923,
                                         PaddingMode.ISO10126};

        private CipherMode[] ciphMode = {CipherMode.ECB,CipherMode.CBC,CipherMode.OFB,
                                         CipherMode.CFB,CipherMode.CTS};

        /// <summary>
        /// AlgID
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
        /// CipherModeID
        /// 0 = ECB
        /// 1 = CBC-CTS
        /// 2 = OFB
        /// 3 = CBC
        /// 4 = CFB
        /// 5 = CTR
        /// Padding
        /// 0 = None
        /// 1 = Zeros
        /// 2 = PKCS7
        /// 3 = ANSIX923
        /// 4 = ISO 10126
        /// </summary>
        /// <param name="AlgID"></param>
        public static byte[] CrypSymModernEncrypt(int AlgID,string passPhrase, int KeySize, byte[] PlainText)
        {
            switch (AlgID)
            { 
                case 9:
                    RijndaelEncrypt(passPhrase, KeySize,PlainText);
                    break;
                case 5:
                    TripleDES_ECB_Encrypt(passPhrase, KeySize, PlainText);
                    break;
                case 6:
                    TripleDES_CBC_Encrypt(passPhrase, KeySize, PlainText);
                    break;
                case 3:
                    DES_ECB_Encrypt(passPhrase, KeySize, PlainText);
                    break;
                case 4:
                    DES_CBC_Encrypt(passPhrase, KeySize, PlainText);
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
                case 5:
                    TripleDES_ECB_Decrypt(passPhrase, KeySize, CipherText);
                    break;
                case 6:
                    TripleDES_CBC_Decrypt(passPhrase, KeySize, CipherText);
                    break;
                case 3:
                    DES_ECB_Decrypt(passPhrase, KeySize, CipherText);
                    break;
                case 4:
                    DES_CBC_Decrypt(passPhrase, KeySize, CipherText);
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
        private static void TripleDES_ECB_Encrypt(string passPhrase, int KeySize, byte[] PlainText)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.ECB;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void TripleDES_ECB_Decrypt(string passPhrase, int KeySize, byte[] CipherText)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.ECB;

            ICryptoTransform decryptor = cipher.CreateDecryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream(CipherText);
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);
            globalPlainText = new byte[CipherText.Length];
            cryptoStream.Read(globalPlainText, 0, globalPlainText.Length);

            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void TripleDES_CBC_Encrypt(string passPhrase, int KeySize, byte[] PlainText)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.CBC;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void TripleDES_CBC_Decrypt(string passPhrase, int KeySize, byte[] CipherText)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.CBC;

            ICryptoTransform decryptor = cipher.CreateDecryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream(CipherText);
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);
            globalPlainText = new byte[CipherText.Length];
            cryptoStream.Read(globalPlainText, 0, globalPlainText.Length);

            memoryStream.Close();
            cryptoStream.Close();
        }


        private static void DES_CBC_Encrypt(string passPhrase, int KeySize, byte[] PlainText)
        {
            DESCryptoServiceProvider cipher = new DESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.CBC;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void DES_CBC_Decrypt(string passPhrase, int KeySize, byte[] CipherText)
        {
            DESCryptoServiceProvider cipher = new DESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.CBC;

            ICryptoTransform decryptor = cipher.CreateDecryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream(CipherText);
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);
            globalPlainText = new byte[CipherText.Length];
            cryptoStream.Read(globalPlainText, 0, globalPlainText.Length);

            memoryStream.Close();
            cryptoStream.Close();
        }

        private static void DES_ECB_Encrypt(string passPhrase, int KeySize, byte[] PlainText)
        {
            DESCryptoServiceProvider cipher = new DESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.ECB;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            globalCipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
        }
        private static void DES_ECB_Decrypt(string passPhrase, int KeySize, byte[] CipherText)
        {
            DESCryptoServiceProvider cipher = new DESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            string t = "12345678";
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(t);
            cipher.Padding = PaddingMode.Zeros;
            cipher.Mode = CipherMode.ECB;

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
