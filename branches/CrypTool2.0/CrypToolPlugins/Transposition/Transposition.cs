using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.Transposition
{
    public class Transposition
    {
        public int[] Encrypt(int[] inputData, int[] key, char[] inputNoNonAlphChar, int[] key2)
        {
            char[] outputData1 = new char[inputNoNonAlphChar.Length];
            char[] outputData2 = new char[inputNoNonAlphChar.Length];
            int[] order = getOrder(key);
            int count = 0;
            for (int i = 0; i < order.Length; i++)
            {
                int ord = order[i];
                for (int j = ord; j < inputNoNonAlphChar.Length; j=j + order.Length)
                {
                    outputData1[count] = inputNoNonAlphChar[j];
                    count++;
                }
            }
            order = getOrder(key2);
            count = 0;
            for (int i = 0; i < order.Length; i++)
            {
                int ord = order[i];
                for (int j = ord; j < outputData1.Length; j=j + order.Length)
                {
                    outputData2[count] = outputData1[j];
                    count++;
                }
            }

            int[] dummy = null;
            return dummy; //return outputData2 to int array
        }

        public int[] Decrypt(int[] inputData, int[] key, char[] inputNoNonAlphChar, int[] key2)
        {
            char[] outputData1 = new char[inputNoNonAlphChar.Length];
            char[] outputData2 = new char[inputNoNonAlphChar.Length];
            int[] order = getOrder(key2);
            int count = 0;
            for (int i = 0; i < order.Length; i++)
            {
                int ord = order[i];
                for (int j = ord; j < inputNoNonAlphChar.Length; j=j + order.Length)
                {
                    outputData1[j] = inputNoNonAlphChar[count];
                    count++;
                }
            }
            order = getOrder(key);
            count = 0;
            for (int i = 0; i < order.Length; i++)
            {
                int ord = order[i];
                for (int j = ord; j < outputData1.Length; j=j + order.Length)
                {
                    outputData2[j] = outputData1[count];
                    count++;
                }
            }

            int[] dummy = null;
            return dummy;//return outputData2
        }

        private int[] getOrder(int[] key2)
        {
            int[] mP = new int[key2.Length];
            int[] mIP = new int[key2.Length];

            for (int i = 0; i < key2.Length; i++)
            {
                mP[i] = 0;
                for (int j = 0; j < key2.Length; j++)
                {
                    if (i != j)
                    {
                        if (key2[i] > key2[j])
                        {
                            mP[i]++;
                        }
                        else if ((key2[i] == key2[j]) && (j < i))
                        {
                            mP[i]++;
                        }
                    }
                }
            }
            for (int i = 0; i < key2.Length; i++)
            {
                mIP[mP[i]] = i;
            }
            return mIP;
        }
    }
}
