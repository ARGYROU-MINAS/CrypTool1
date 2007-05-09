using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.AppLogic
{
    public class IDEA
    {
        public int[] getKeySize()
        {
            int[] KeySize = { 128 };
            return KeySize;
        }
        public string getAlgInfo()
        {
            return "Fixed Key Length: 16 - Block Size: 8";
        }
    }
}
