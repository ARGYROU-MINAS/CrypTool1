using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;
using System.Collections;

namespace CrypTool.ADFGVX
{
    public class ADFGVX
    {
        /// <summary>
        /// ADFGVX encryptor
        /// </summary>
        /// <param name="inputData">The input data to be encrypted</param>
        /// <param name="key">Key used for encryption</param>
        /// <param name="alphabet">alphabet used for encryption</param>
        /// <param name="inputNoNonAlphaChar">char array containing no nonalphabetical characters</param>
        /// <param name="key2"></param>
        /// <returns>The encrypted data as an int array</returns>
        public int[] Encrypt(int[] inputData, int[] key, int[] alphabet, int[] key2)
        {
            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);
            char[] outputData = new char[inputData.Length * 2];

            int y = 0;
            for (int i = 0; i < inputData.Length && y < outputData.Length + 1; i++)
            {
                for (int j = 0; j < alphCipher.Length; j++)
                {
                    if (alphCipher[j] == inputData[i])
                    {
                        int line = j / 6;
                        int column = j % 6;
                        String pair = "";
                        switch (line)
                        {
                            case 0:
                                pair = "A";
                                break;
                            case 1:
                                pair = "D";
                                break;
                            case 2:
                                pair = "F";
                                break;
                            case 3:
                                pair = "G";
                                break;
                            case 4:
                                pair = "V";
                                break;
                            case 5:
                                pair = "X";
                                break;
                        }
                        switch (column)
                        {
                            case 0:
                                pair += "A";
                                break;
                            case 1:
                                pair += "D";
                                break;
                            case 2:
                                pair += "F";
                                break;
                            case 3:
                                pair += "G";
                                break;
                            case 4:
                                pair += "V";
                                break;
                            case 5:
                                pair += "X";
                                break;
                        }
                        char[] tempPair = pair.ToCharArray();
                        outputData[y] = tempPair[0];
                        y++;
                        outputData[y] = tempPair[1];
                        y++;
                    }
                }
            }
            int[] order = getOrder(key2);
            int count = 0;
            char[] charOutputData = new char[outputData.Length];
            for (int i = 0; i < order.Length; i++)
            {
                int tempOrder = order[i];
                for (int j = tempOrder; j < outputData.Length; j=j + order.Length)
                {
                    charOutputData[count] = outputData[j];
                    count++;
                }
            }

            int[] dummy = null;
            return dummy; // charOutputData, missing Alphabet
        }

        /// <summary>
        /// ADFGVX decryptor
        /// </summary>
        /// <param name="inputData">The input data to be decryted</param>
        /// <param name="key">Key used for decryption</param>
        /// <param name="alphabet">alphabet used for decryption</param>
        /// <param name="inputNoNonAlphaChar">char array containing no nonalphabetical characters</param>
        /// <param name="key2"></param>
        /// <returns>The decrypted data as an int array</returns>
        public int[] Decrypt(int[] inputData, int[] key, int[] alphabet, char[] inputNoNonAlphaChar, int[] key2)
        {
            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);
            int[] ouputData = new int[inputNoNonAlphaChar.Length / 2];
            int[] order = getOrder(key2);
            int count = 0;
            char[] charOutputData = new char[inputNoNonAlphaChar.Length];

            for (int i = 0; i < order.Length; i++)
            {
                int ord = order[i];
                for (int j = ord; j < inputNoNonAlphaChar.Length; j=j + order.Length)
                {
                    charOutputData[j] = inputNoNonAlphaChar[count];
                    count++;
                }
            }

            int y = 0;
            for (int i = 0; i < charOutputData.Length; i++)
            {
                char[] pair = new char[2];
                int line = 0;
                int column = 0;
                pair[0] = charOutputData[i];
                i++;
                pair[1] = charOutputData[i];

                switch (pair[0])
                {
                    case 'A':
                        line = 0;
                        break;
                    case 'D':
                        line = 1;
                        break;
                    case 'F':
                        line = 2;
                        break;
                    case 'G':
                        line = 3;
                        break;
                    case 'V':
                        line = 4;
                        break;
                    case 'X':
                        line = 5;
                        break;
                }
                switch (pair[1])
                {
                    case 'A':
                        column = 0;
                        break;
                    case 'D':
                        column = 1;
                        break;
                    case 'F':
                        column = 2;
                        break;
                    case 'G':
                        column = 3;
                        break;
                    case 'V':
                        column = 4;
                        break;
                    case 'X':
                        column = 5;
                        break;
                }
                int ch = line * 6 + column;
                ouputData[y] = alphCipher[ch];
                y++;
            }
            return ouputData;
        }

        /// <summary>
        /// Generate and initialize the private data
        /// </summary>
        /// <param name="key2">The key to be used for the permutation</param>
        /// <returns>an int array which contains the read-order of the columns</returns>
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
                        else if ((key2[i] == key2[j]) && (i < j))
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
