using System;
using System.Collections.Generic;
using System.Text;


namespace CrypTool
{
    class GUIInterface
    {
        Interface.Interface intfce;

        public GUIInterface()
        {
            intfce = new Interface.Interface();
        }

        public String getAlphabet()
        {
            return intfce.getAlphabet();
        }
    }
}
