using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;



namespace CrypTool.AppLogic
{
    public sealed class Rot13Caesar : SymmetricAlgorithm, ICryptoTransform
    {
        public Rot13Caesar()
        {
            this.LegalKeySizesValue = new KeySizes[] { new KeySizes(16, 16, 0) };

            this.KeySize = 16; // in bits

            this.LegalBlockSizesValue = new KeySizes[] { new KeySizes(16, 16, 0) }; // this is in bits - typical of MS - always 16 bytes

            this.BlockSize = 16; // set this to 16 bytes we cannot have any other value
        }

        public override ICryptoTransform CreateDecryptor(byte[] rgbKey, byte[] rgbIV)
        {
            Key = rgbKey;
            IV = rgbIV;
            return this;
        }

        public override ICryptoTransform CreateEncryptor(byte[] rgbKey, byte[] rgbIV)
        {
            Key = rgbKey;
            IV = rgbIV;
            return this;
        }

        public override void GenerateIV()
        {
            //Isn't used in Rot13Caesar
            IVValue = new byte[BlockSize / 8];


        }

        public override void GenerateKey()
        {
            //Standard for Rot13Caesar is "M"
            KeyValue = new byte[KeySize / 8];
            Key = Encoding.Unicode.GetBytes("M");
        }


        #region ICryptoTransform Members

        private bool canReuseTransform = false;
        public bool CanReuseTransform
        {
            get { return canReuseTransform; }
        }

        private bool canTransformMultipleBlocks = false;
        public bool CanTransformMultipleBlocks
        {
            get { return canTransformMultipleBlocks; }
        }

        public int InputBlockSize
        {
            get { return BlockSize / 8; }
        }

        public int OutputBlockSize
        {
            get { return BlockSize / 8; }
        }

        public int TransformBlock(byte[] inputBuffer, int inputOffset, int inputCount, byte[] outputBuffer, int outputOffset)
        {
            int bytesWritten = 0;
            for (int i = inputOffset; i < inputOffset + inputCount; i = i + 2)
            {
                //just as an example
                outputBuffer[i + outputOffset - inputOffset] = (byte)(inputBuffer[i] + Key[0] - 65);
                if (outputBuffer[i + outputOffset - inputOffset] > 90)
                {
                    outputBuffer[i + outputOffset - inputOffset] = (byte)(outputBuffer[i + outputOffset - inputOffset] - 90 + 65);
                }
                bytesWritten++;
            }

            return bytesWritten * 2;

        }

        public byte[] TransformFinalBlock(byte[] inputBuffer, int inputOffset, int inputCount)
        {
            for (int i = inputOffset; i < inputOffset + inputCount; i = i + 2)
            {
                //just as an example
                inputBuffer[i] = (byte)(inputBuffer[i] + Key[0] - 65);
                if (inputBuffer[i] > 90)
                {
                    inputBuffer[i] = (byte)(inputBuffer[i] - 90 + 65);
                }
            }
            return inputBuffer;

        }

        #endregion
    }
}
