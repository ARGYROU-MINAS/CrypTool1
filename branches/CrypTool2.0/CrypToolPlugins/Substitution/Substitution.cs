using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;
using System.Collections;

namespace CrypTool.Substitution
{
    public class Substitution
    {

        /// <summary>
        /// Substitution encryption
        /// </summary>
        /// <param name="inputData">The input data to encrypt</param>
        /// <param name="key">Key which the encryption uses</param>
        /// <param name="alphabet">Alphabet which the encryption uses</param>
        /// <returns>The encrypted data as an int array</returns>
        public int[] Encrypt(int[] inputData, int[] key, int[] alphabet)
        {
            int[] outputData = new int[inputData.Length];
            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);

            for (int i = 0; i < inputData.Length; i++)
            {
                for (int j = 0; j < alphabet.Length; j++)
                {
                    if (alphabet[j] == inputData[i])
                    {
                        outputData[i] = alphCipher[j];
                        break;
                    }
                }
            }
            return outputData;
        }

        /// <summary>
        /// Substitution decryption
        /// </summary>
        /// <param name="inputData">The input data to decrypt</param>
        /// <param name="key">Key which the encryption uses</param>
        /// <param name="alphabet">Alphabet which the encryption uses</param>
        /// <returns>The decrypted data as an int array</returns>
        public int[] Decrypt(int[] inputData, int[] key, int[] alphabet)
        {
            int[] outputData = new int[inputData.Length];
            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);

            for (int i = 0; i < inputData.Length; i++)
            {
                for (int j = 0; j < alphabet.Length; j++)
                {
                    if (alphCipher[j] == inputData[i])
                    {
                        outputData[i] = alphabet[j];
                        break;
                    }
                }
            }
            return outputData;
        }

        /// <summary>
        /// Build alphabet cipher
        /// </summary>
        /// <param name="key">used key</param>
        /// <param name="alphabet">The plain alphabet</param>
        /// <returns>Alphabet for en-/decryption as an int array</returns>
        private int[] getAlphCipher(int[] key, int[] alphabet)
        {
            int count = 0;
            bool found;
            int[] alphCipher = new int[alphabet.Length];

            for (int i = 0; i < key.Length; i++)
            {
                alphCipher[i] = key[i];
            }

            for (int i = 0; i < alphabet.Length; i++)
            {
                found = false;
                for (int j = 0; j < key.Length && !found; j++)
                {
                    if (alphabet[i] == key[j])
                    {
                        found = true;
                        count++;
                    }
                }
                if (!found)
                {
                    alphCipher[i + key.Length - count] = alphabet[i];
                }
            }

            return alphCipher;
        }

        /// <summary>
        /// Remove duplicate characters from the key array
        /// </summary>
        /// <param name="key">The key array</param>
        /// <returns>The key array without duplicate characters</returns>
        private int[] removeDuplicateChars(int[] key)
        {
            bool found;
            int[] newKey;
            ArrayList alKey = new ArrayList();
            
            for (int i = 0; i < key.Length; i++)
            {
                found = false;
                for (int j = 0; j < alKey.Count; j++)
                {
                    if (key[i] == (int)alKey[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    alKey.Add(key[i]);
                }
            }

            newKey = new int[alKey.Count];
            for (int i = 0; i < alKey.Count; i++)
            {
                newKey[i] = (int)alKey[i];
            }

            return newKey;
        }
    }
}
