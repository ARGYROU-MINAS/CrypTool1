using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;

namespace CrypTool.Hill
{
    public class Hill
    {
        public int[] Encrypt(int[] inputData, int dim, int modul)
        {
            int[] outputData = new int[inputData.Length];

            for (long i = 0; i < inputData.Length/dim; i++)
            {
                for (int j = 0; j < dim; j++)
                {
                    long hilf = 0;
                    for (int k = 0; k < dim; k++)
                    {
                        //hilf += (enc_mat)(k,j) * inputData[dim*i+k];
                        hilf %= modul;
                    }
                    outputData[dim * i + j] = (int)hilf;
                }
            }
            return outputData;
        }

        public int[] Decrypt(int[] inputData, int dim, int modul)
        {
            int[] outputData = new int[inputData.Length];

            for (long i = 0; i < inputData.Length/dim; i++)
            {
                for (int j = 0; j < dim; j++)
                {
                    long hilf = 0;
                    for (int k = 0; k < dim; k++)
                    {
                        //hilf += (dec_mat)(k,j) * inputData[dim*i+k];
                        hilf %= modul;
                    }
                    outputData[dim * i + j] = (int)hilf;
                }
            }
            return outputData;
        }
    }
}
