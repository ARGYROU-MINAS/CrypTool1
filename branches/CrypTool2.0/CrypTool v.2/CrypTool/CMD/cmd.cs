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

            #region GETTER
            if (cmdLine["get"] != null)
            {
                if (cmdLine["alphabet"] != null)
                {
                    Console.WriteLine(CrypTool.AppLogic.TextOptions.getAlphabet());
                }
            }
            #endregion

            #region SETTER
            if (cmdLine["set"] != null)
            {
                if (cmdLine["alphabet"] != null)
                {
                    CrypTool.AppLogic.TextOptions.setAlphabet(cmdLine["alphabet"]);
                    CrypTool.AppLogic.TextOptions.writeTextOptions();
                }
            }
            #endregion
        }
    }
}
