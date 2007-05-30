using System;
using System.Collections.Generic;
using System.Text;

namespace CrypTool.CMD
{
    class CMD
    {
        static void Main(string[] args)
        {
            Arguments cmdLine = new Arguments(args);

            if (cmdLine["get"] != null)
            {
                if (cmdLine["alphabet"] != null)
                {
                    Console.WriteLine(CrypTool.AppLogic.TextOptions.getAlphabet());
                }
            }

        }
    }
}
