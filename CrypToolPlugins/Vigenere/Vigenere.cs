using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.Vigenere
{
    public class Vigenere
    {
        /// <summary>
        /// Vigenere Encryption
        /// </summary>
        /// <param name="inputData">The input data to be encrypted</param>
        /// <param name="key">The key which the encryption uses</param>
        /// <param name="alphLength">The length of the alphabet</param>
        /// <returns>The encrpyted data as an int array</returns>
        public int[] Encrypt(int[] inputData, int[] key, int alphLength)
        {
            int[] outputData = new int[inputData.Length];

            for (int i = 0; i < inputData.Length; i++)
            {
                outputData[i] = (inputData[i] + key[i % key.Length]) & alphLength;
            }

            return outputData;
        }

        /// <summary>
        /// Vigenere Decryption
        /// </summary>
        /// <param name="inputData">The input data to be decrypted</param>
        /// <param name="key">The key which the encryption uses</param>
        /// <param name="alphLength">The lenght of the alphabet</param>
        /// <returns>The decrypted data as an int array</returns>
        public int[] Decrypt(int[] inputData, int[] key, int alphLength)
        {
            int[] outputData = new int[inputData.Length];
            int newCharValue;

            for (int i = 0; i < inputData.Length; i++)
            {
                newCharValue = inputData[i] - key[i % key.Length];

                if (newCharValue < 0)
                    newCharValue += alphLength;

                outputData[i] = newCharValue;
            }

            return outputData;
        }
    }
}
