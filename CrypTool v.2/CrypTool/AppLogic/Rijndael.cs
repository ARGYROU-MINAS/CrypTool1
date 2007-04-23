using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace CrypTool.AppLogic
{
    public class Rijndael
    {
        //provided by .NET Framework

        public byte[] Encrypt(string passPhrase,byte[] PlainText,int KeySize,CipherMode ciphMode, PaddingMode padMode,string IV)
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
    }
}
