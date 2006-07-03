using System;
using System.Collections.Generic;
using System.Text;


namespace Interface
{
    public class Interface
    {
        AppLogic.ManTextOptions manTextOptions;

        public Interface()
        {
            manTextOptions = new AppLogic.ManTextOptions();
        }

        public String getAlphabet()
        {
            return manTextOptions.getAlphabet();
        }
    }
}
