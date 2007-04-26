using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace CrypTool.AppLogic
{
    public class TripleDES
    {
        public byte[] Encrypt(string passPhrase, byte[] PlainText, int KeySize, CipherMode ciphMode, PaddingMode padMode, string IV)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(IV);
            cipher.Padding = padMode;
            cipher.Mode = ciphMode;

            ICryptoTransform encryptor = cipher.CreateEncryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream();
            CryptoStream cryptoStream = new CryptoStream(memoryStream, encryptor, CryptoStreamMode.Write);
            cryptoStream.Write(PlainText, 0, PlainText.Length);
            cryptoStream.FlushFinalBlock();
            byte[] CipherText = memoryStream.ToArray();
            memoryStream.Close();
            cryptoStream.Close();
            return CipherText;
        }
        public byte[] Decrypt(string passPhrase, byte[] CipherText, int KeySize, CipherMode ciphMode, PaddingMode padMode, string IV)
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.Key = getpassPhraseByte(passPhrase, KeySize);
            cipher.IV = System.Text.Encoding.ASCII.GetBytes(IV);
            cipher.Padding = padMode;
            cipher.Mode = ciphMode;

            ICryptoTransform decryptor = cipher.CreateDecryptor(cipher.Key, cipher.IV);
            MemoryStream memoryStream = new MemoryStream(CipherText);
            CryptoStream cryptoStream = new CryptoStream(memoryStream, decryptor, CryptoStreamMode.Read);
            byte[] PlainText = new byte[CipherText.Length];
            cryptoStream.Read(PlainText, 0, PlainText.Length);
            memoryStream.Close();
            cryptoStream.Close();
            return PlainText;
        }
        public string getDefaultIV()
        {
            return "00000000";
        }
        public string getInternalRandomIV()
        {
            TripleDESCryptoServiceProvider cipher = new TripleDESCryptoServiceProvider();
            cipher.GenerateIV();
            return System.Text.Encoding.Default.GetString(cipher.Key);
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
