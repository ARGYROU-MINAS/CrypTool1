using System;
using System.Collections.Generic;
using System.Text;

namespace Interfaces
{
    public interface IEncryptionAlgorithm
    {
        byte[] encrypt(byte[] data);

        byte[] decrypt(byte[] data);
        
    }
}
