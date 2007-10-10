using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CrypTool.PluginBase;
using System.Collections;

namespace CrypTool.Playfair
{
    public class Playfair
    {
        /// <summary>
        /// Playfair encryption
        /// </summary>
        /// <param name="inputData">The input data to be encrypted</param>
        /// <param name="key">Key used for the encryption</param>
        /// <param name="inputNoNonAlphChar"></param>
        /// <param name="alphabet"></param>
        /// <param name="nullChar"></param>
        /// <param name="keyChars"></param>
        /// <returns></returns>
        public int[] Encrypt(int[] inputData, int[] key, char[] inputNoNonAlphChar,int[] alphabet, char nullChar, char[] keyChars)
        {
            int pairs = 0;
            for (int i = 0; i < inputData.Length; i++)
            {
                if (char.IsLetter(keyChars[i]))
                {
                    inputData[i] = char.ToUpper(keyChars[i]);
                }
                if (inputData[i] == 'J')
                {
                    inputData[i] = 'I';
                }
                if (inputData[i] == 'Ä')
                {
                    inputData[i] = 'A';
                }
                if (inputData[i] == 'Ö')
                {
                    inputData[i] = 'O';
                }
                if (inputData[i] == 'Ü')
                {
                    inputData[i] = 'U';
                }
            }
            for (int i = 0; i < inputNoNonAlphChar.Length; i++)
            {
                if (i < inputNoNonAlphChar.Length - 1)
                {
                    if (inputNoNonAlphChar[i] == inputNoNonAlphChar[i + 1])
                    {
                        pairs++;
                    }
                }
            }

            char[] inputEven;
            if ((inputNoNonAlphChar.Length + pairs) % 2 != 0)
            {
                inputEven = new char[inputNoNonAlphChar.Length + 1 + pairs];
                int counter = 0;
                for (int i = 0; i < inputNoNonAlphChar.Length; i++)
                {
                    if (i < inputNoNonAlphChar.Length - 1)
                    {
                        if (inputNoNonAlphChar[i] == inputNoNonAlphChar[i + 1])
                        {
                            inputEven[counter] = inputNoNonAlphChar[i];
                            counter++;
                            inputEven[counter] = nullChar;
                            counter++;
                        }
                        else
                        {
                            inputEven[counter] = inputNoNonAlphChar[i];
                            counter++;
                        }
                    }
                    else
                    {
                        inputEven[counter] = inputNoNonAlphChar[i];
                        counter++;
                    }
                }
                inputEven[inputEven.Length - 1] = nullChar;
            }
            else
            {
                inputEven = new char[inputNoNonAlphChar.Length + pairs];
                int counter = 0;
                for (int i = 0; i < inputNoNonAlphChar.Length; i++)
                {
                    if (i < inputNoNonAlphChar.Length - 1)
                    {
                        if (inputNoNonAlphChar[i] == inputNoNonAlphChar[i + 1])
                        {
                            inputEven[counter] = inputNoNonAlphChar[i];
                            counter++;
                            inputEven[counter] = nullChar;
                            counter++;
                        }
                        else
                        {
                            inputEven[counter] = inputNoNonAlphChar[i];
                            counter++;
                        }
                    }
                    else
                    {
                        inputEven[counter] = inputNoNonAlphChar[i];
                        counter++;
                    }
                }
            }

            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);
            int[] inputInt = null; //todo convert char array inputEven to int array
            int[] outputData = new int[inputInt.Length];
            for (int i = 0; i < inputInt.Length - 1; i++)
            {
                int ch1 = inputInt[i];
                i++;
                int ch2 = inputInt[i];
                int indexCh1 = getIndex(ch1, alphCipher);
                int indexCh2 = getIndex(ch2, alphCipher);
                int rowCh1 = -1;
                int rowCh2 = -2;
                int colCh1 = -3;
                int colCh2 = -4;
                int newCh1;
                int newCh2;

                for (int j = 0; j < alphCipher.Length; j++)
                {
                    if (alphCipher[j] == ch1)
                    {
                        rowCh1 = j / 5;
                        colCh1 = j % 5;
                    }
                    if (alphCipher[j] == ch2)
                    {
                        rowCh2 = j / 5;
                        colCh2 = j % 5;
                    }
                }
                if (rowCh1 == rowCh2)
                {
                    newCh1 = getRightNeighbour(indexCh1, alphCipher);
                    newCh2 = getRightNeighbour(indexCh2, alphCipher);
                }
                else if (colCh1 == colCh2)
                {
                    newCh1 = getLowerNeighbour(indexCh1, alphCipher);
                    newCh2 = getLowerNeighbour(indexCh2, alphCipher);
                }
                else
                {
                    newCh1 = getSubstitute(rowCh1, colCh2, alphCipher);
                    newCh2 = getSubstitute(rowCh2, colCh1, alphCipher);
                }
                outputData[i - 1] = newCh1;
                outputData[i] = newCh2;
            }
            return outputData;
        }

        public int[] Decrypt(int[] inputData, int[] key, char[] inputNoNonAlphChar, int[] alphabet, char nullChar, char[] keyChars)
        {
            int[] alphCipher = getAlphCipher(removeDuplicateChars(key), alphabet);
            int[] outputData = new int[inputData.Length];
            for (int i = 0; i < inputData.Length - 1; i++)
            {
                int ch1 = inputData[i];
                i++;
                int ch2 = inputData[i];
                int indexCh1 = getIndex(ch1, alphCipher);
                int indexCh2 = getIndex(ch2, alphCipher);
                int rowCh1 = -1;
                int rowCh2 = -2;
                int colCh1 = -3;
                int colCh2 = -4;
                int newCh1;
                int newCh2;

                for (int j = 0; j < alphCipher.Length; j++)
                {
                    if (alphCipher[j] == ch1)
                    {
                        rowCh1 = j / 5;
                        colCh1 = j % 5;
                    }
                    if (alphCipher[j] == ch2)
                    {
                        rowCh2 = j / 5;
                        colCh2 = j % 5;
                    }
                }
                if (rowCh1 == rowCh2)
                {
                    newCh1 = getLeftNeighbour(indexCh1, alphCipher);
                    newCh2 = getLeftNeighbour(indexCh2, alphCipher);
                }
                else if (colCh1 == colCh2)
                {
                    newCh1 = getUpperNeighbour(indexCh1, alphCipher);
                    newCh2 = getUpperNeighbour(indexCh2, alphCipher);
                }
                else
                {
                    newCh1 = getSubstitute(rowCh1, colCh2, alphCipher);
                    newCh2 = getSubstitute(rowCh2, colCh1, alphCipher);
                }
                outputData[i - 1] = newCh1;
                outputData[i] = newCh2;
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

        private int getIndex(int ch, int[] alphCipher)
        {
            for (int i = 0; i < alphCipher.Length; i++)
            {
                if (ch == alphCipher[i])
                {
                    return i;
                }
            }
            return -1;
        }

        private int getRightNeighbour(int index, int[] alphCipher)
        {
            if (index % 5 < 4)
            {
                return alphCipher[index + 1];
            }
            else
            {
                if (index % 5 == 4)
                {
                    return alphCipher[index - 4];
                }
            }
            return -1;
        }

        private int getLowerNeighbour(int index, int[] alphCipher)
        {
            if (index + 5 < alphCipher.Length)
            {
                return alphCipher[index + 5];
            }
            else
            {
                return alphCipher[(index + 5) % alphCipher.Length];
            }
        }

        private int getUpperNeighbour(int index, int[] alphCipher)
        {
            if (index < 5)
            {
                return alphCipher[alphCipher.Length - (5 - index)];
            }
            else
            {
                return alphCipher[index - 5];
            }
        }

        private int getLeftNeighbour(int index, int[] alphCipher)
        {
            if (index % 5 > 0)
            {
                return alphCipher[index - 1];
            }
            else
            {
                return alphCipher[index + 4];
            }
        }

        private int getSubstitute(int row, int col, int[] alphCipher)
        {
            return alphCipher[5 * (row) + col];
        }
    }
}
