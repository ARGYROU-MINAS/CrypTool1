using System;
using System.Collections.Generic;
using System.Text;

namespace AppLogic
{
    class CrypSymModern
    {
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
        public void CrypSymModernEncrypt(int AlgID,int KeySize,int BlockSize,byte[] PlainText)
        {
            switch (AlgID)
            { 
                case 0:
                    RijndaelEncrypt(KeySize,BlockSize,PlainText);
                    break;
            }
            
        }
        public void CrypSymModernDecrypt(int AlgID, int KeySize,int BlockSize,byte[] CipherText)
        { 
        
        }
        private void RijndaelEncrypt(int KeySize,int BlockSize, byte[] PlainText)
        { 
            
        }

    }
}
