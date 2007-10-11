using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.Vernam
{
    public class Vernam
    {
        public int[] Encrypt(int[] inputData, int[] key)
        {
            int[] outputData = new int[inputData.Length];
            key = refillKey(key,inputData.Length);

            for (int i = 0; i < inputData.Length; i++)
			{
                outputData[i] = inputData[i] ^ key[i];
			}

            return outputData;
        }

        public int[] Decrypt(int[] inputData, int[]key)
        {
            int[] outputData = new int[inputData.Length];
            key = refillKey(key,inputData.Length);

            for (int i = 0; i < inputData.Length; i++)
			{
                outputData[i] = inputData[i] ^ key[i];
			}

            return outputData;
        }

        private int[] refillKey(int[] key, int inputDataLength)
        {
            int[] fullKey = new int[inputDataLength];

            for (int i = 0; i < key.Length; i++)
			{
                fullKey[i] = key[i];
			}

            int pos = 1;
            for (int i = key.Length; i < inputDataLength; i++)
			{
                fullKey[i] = key[pos];
                pos++;
			}
            return fullKey;
        }
    }
}