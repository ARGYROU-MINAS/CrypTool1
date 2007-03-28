using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;

namespace CrypTool.AppLogic
{
    public static class CrypSymModern
    {
        static private byte[] cipherText;

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
            return cipherText;
        }
        public static void CrypSymModernDecrypt(int AlgID, int KeySize,int BlockSize,byte[] CipherText)
        { 
        
        }
        private static void RijndaelEncrypt(int KeySize,int BlockSize, byte[] PlainText)
        {
            RijndaelManaged cipher = new RijndaelManaged();
            cipher.KeySize = KeySize;
            cipher.BlockSize = BlockSize;
            cipher.Mode = CipherMode.ECB;
            ICryptoTransform transform = cipher.CreateEncryptor();

            cipherText = transform.TransformFinalBlock(PlainText, 0, PlainText.Length);
        }

    }
}
