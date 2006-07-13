using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using Interfaces;

namespace AppLogic
{
    public sealed class Rot13Caesar:SymmetricAlgorithm, IEncryptionClassic
    {
        public override ICryptoTransform CreateDecryptor(byte[] rgbKey, byte[] rgbIV)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public override ICryptoTransform CreateEncryptor(byte[] rgbKey, byte[] rgbIV)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public override void GenerateIV()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public override void GenerateKey()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        #region IEncryptionClassic Members

        void IEncryptionClassic.sampleMethodEspeciallyForClassicAlgorithms()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        #endregion

        #region IEncryptionAlgorithm Members

        byte[] IEncryptionAlgorithm.encrypt(byte[] data)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        byte[] IEncryptionAlgorithm.decrypt(byte[] data)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        #endregion
    }
}
