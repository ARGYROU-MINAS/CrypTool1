using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace CrypTool.AppLogic
{
    public class CrypSymModern
    {
        private int AlgID;
        private string strDefaultIV;
        private string strIntRandIV;
        private int[] KeySize;

        public CrypSymModern()
        { 
        
        }
        public CrypSymModern(int AlgID)
        {
            this.AlgID = AlgID;
            getAlgoPrefs();
        }

        private PaddingMode[] padMode = {PaddingMode.None,PaddingMode.Zeros,
                                         PaddingMode.PKCS7,PaddingMode.ANSIX923,
                                         PaddingMode.ISO10126};

        private CipherMode[] ciphMode = {CipherMode.ECB,CipherMode.CBC,CipherMode.OFB,
                                         CipherMode.CFB,CipherMode.CTS};

        private string[] AlgTitle = {   "IDEA","RC2","RC4","DES",
                                        "TripleDES","Mars","RC6",
                                        "Rijndael(AES)","Serpent",
                                        "Twofish"};
        
        private string[] strPadMode = { "No Padding", "Zeros Padding", "PKCS7 Padding", "ANSIX923 Padding", "ISO10126 Padding" };

        private void getAlgoPrefs()
        {
            switch (this.AlgID)
            {
                case 0:
                    CrypTool.AppLogic.IDEA idea = new CrypTool.AppLogic.IDEA();
                    this.KeySize = idea.getKeySize();
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    CrypTool.AppLogic.DES des = new CrypTool.AppLogic.DES();
                    this.strDefaultIV = des.getDefaultIV();
                    this.strIntRandIV = des.getInternalRandomIV();
                    this.KeySize = des.getKeySize();
                    break;
                case 4:
                    CrypTool.AppLogic.TripleDES tripleDES = new CrypTool.AppLogic.TripleDES();
                    this.strDefaultIV = tripleDES.getDefaultIV();
                    this.strIntRandIV = tripleDES.getInternalRandomIV();
                    this.KeySize = tripleDES.getKeySize();
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    CrypTool.AppLogic.Rijndael rijndael = new CrypTool.AppLogic.Rijndael();
                    this.strDefaultIV = rijndael.getDefaultIV();
                    this.strIntRandIV = rijndael.getInternalRandomIV();
                    this.KeySize = rijndael.getKeySize();
                    break;
                case 8:
                    break;
                case 9:
                    break;
            }
        }

        /// <summary>
        /// AlgID
        /// 0 = IDEA
        /// 1 = RC2
        /// 2 = RC4
        /// 3 = DES
        /// 4 = TripleDES
        /// 5 = Mars
        /// 6 = RC6
        /// 7 = Rijndael(AES)
        /// 8 = Serpent
        /// 9 = Twofish
        /// CipherModeID
        /// 0 = ECB
        /// 1 = CTS
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
        public byte[] CrypSymModernEncrypt(string passPhrase, int KeySize, byte[] PlainText,int ciphMode, int padMode, string IV)
        {
            byte[] CipherText = null;
            switch (this.AlgID)
            { 
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    CrypTool.AppLogic.DES des = new CrypTool.AppLogic.DES();
                    CipherText = des.Encrypt(passPhrase, PlainText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 4:
                    CrypTool.AppLogic.TripleDES tripleDES = new CrypTool.AppLogic.TripleDES();
                    CipherText = tripleDES.Encrypt(passPhrase, PlainText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    CrypTool.AppLogic.Rijndael rijndael = new CrypTool.AppLogic.Rijndael();
                    CipherText = rijndael.Encrypt(passPhrase, PlainText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 8:
                    break;
                case 9:
                    break;
            }
            return CipherText;
        }
        public byte[] CrypSymModernDecrypt(string passPhrase, int KeySize, byte[] CipherText, int ciphMode, int padMode, string IV)
        {
            byte[] PlainText = null;
            switch (this.AlgID)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    CrypTool.AppLogic.DES des = new CrypTool.AppLogic.DES();
                    CipherText = des.Decrypt(passPhrase, CipherText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 4:
                    CrypTool.AppLogic.TripleDES tripleDES = new CrypTool.AppLogic.TripleDES();
                    CipherText = tripleDES.Decrypt(passPhrase, CipherText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    CrypTool.AppLogic.Rijndael rijndael = new CrypTool.AppLogic.Rijndael();
                    CipherText = rijndael.Decrypt(passPhrase, CipherText, KeySize, this.ciphMode[ciphMode], this.padMode[padMode], IV);
                    break;
                case 8:
                    break;
                case 9:
                    break;
            }
            return PlainText;
        }
        
        public string[] getAlgTitle()
        {
            return this.AlgTitle;
        }
        public string[] getPaddingMode()
        {
            return this.strPadMode;
        }
        public string getDefaultIV()
        {
            return this.strDefaultIV;
        }
        public string getIntRandIV()
        {
            return this.strIntRandIV;
        }
        public int[] getKeySize()
        {
            return this.KeySize;
        }

    }
}
