using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.XOR
{
    public class Xor
    {

        /// <summary>
        /// Xor Encryption
        /// </summary>
        /// <param name="inputData">The input data to be encrypted</param>
        /// <param name="key">Key which the encryption uses</param>
        /// <returns>The encrypted data as an int array</returns>
        public int[] Encrypt(int[] inputData, int[] key)
        {
            int[] outputData = new int[inputData.Length];

            for (int i = 0; i < inputData.Length; i++)
            {
                outputData[i] = inputData[i] ^ key[i % key.Length];
            }

            return outputData;
        }

        /// <summary>
        /// Xor Decryption
        /// </summary>
        /// <param name="inputData">The input data to be decrypted</param>
        /// <param name="key">Key which the decryption uses</param>
        /// <returns>The decrypted data as an int array</returns>
        public int[] Decrypt(int[] inputData, int[] key)
        {
            int[] outputData = new int[inputData.Length];

            for (int i = 0; i < inputData.Length; i++)
            {
                outputData[i] = inputData[i] ^ key[i % key.Length];
            }

            return outputData;
        }
    }
}
