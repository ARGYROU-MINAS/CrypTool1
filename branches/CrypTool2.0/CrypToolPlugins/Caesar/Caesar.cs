using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.Caesar
{
    public class Caesar
    {
        /// <summary>
        /// Caesar encryption
        /// </summary>
        /// <param name="inputData">Input data to be encrypted</param>
        /// <param name="key">Key which the encryption uses</param>
        /// <param name="alphLength">The length of the alphabet</param>
        /// <returns>The encrypted data as an int array</returns>
        public int[] Encrypt(int[] inputData, int[] key, int alphLength)
        {
            int[] outputData = new int[inputData.Length];

            for (int i = 0; i < inputData.Length; i++)
            {
                outputData[i] = (inputData[i] + key[0]) % alphLength;
            }

            return outputData;
        }

        /// <summary>
        /// Caesar decryption
        /// </summary>
        /// <param name="inputData">Input data to be decrypted</param>
        /// <param name="key">Key which the decryption uses</param>
        /// <param name="alphLength">The length of the alphabet</param>
        /// <returns>The decrypted data as an int array</returns>
        public int[] Decrypt(int[] inputData, int[] key, int alphLength)
        {
            int[] outputData = new int[inputData.Length];
            int newCharValue;

            for (int i = 0; i < inputData.Length; i++)
            {
                newCharValue = inputData[i] - key[0];

                if (newCharValue < 0)
                    newCharValue += alphLength;

                outputData[i] = newCharValue;
            }

            return outputData;
        }
    }
}
