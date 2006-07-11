using System;
using System.Collections.Generic;
using System.Text;


namespace Interface
{
    public class TextOptions
    {
        AppLogic.TextOptions txtOpt;

        public TextOptions()
        {
        }


        //SetMethods
        public static void setStrRefFile(String strRefFile)
        {
            AppLogic.TextOptions.setStrRefFile(strRefFile);
        }
        public static void setAlphabet(String strAlph)
        {
            AppLogic.TextOptions.setAlphabet(strAlph);
        }
        public static void setTrenn(String strTrenn)
        {
            AppLogic.TextOptions.setTrenn(strTrenn);
        }
        public static void setFormat(bool bFormat)
        {
            AppLogic.TextOptions.setFormat(bFormat);
        }
        public static void setCase(bool bCase)
        {
            AppLogic.TextOptions.setCase(bCase);
        }
        public static void setLeerVal(bool bLeerVal)
        {
            AppLogic.TextOptions.setLeerVal(bLeerVal);
        }
        public static void setGrossVal(bool bGrossVal)
        {
            AppLogic.TextOptions.setGrossVal(bGrossVal);
        }
        public static void setKleinVal(bool bKleinVal)
        {
            AppLogic.TextOptions.setKleinVal(bKleinVal);
        }
        public static void setSatzVal(bool bSatzVal)
        {
            AppLogic.TextOptions.setSatzVal(bSatzVal);
        }
        public static void setZahlVal(bool bZahlVal)
        {
            AppLogic.TextOptions.setZahlVal(bZahlVal);
        }
        public static void setConvertCase(bool bConvertCase)
        {
            AppLogic.TextOptions.setConvertCase(bConvertCase);
        }
        public static void setAddx(bool bAddx)
        {
            AppLogic.TextOptions.setAddx(bAddx);
        }
        public static void setIngoreCase(bool bIgnoreCase)
        {
            AppLogic.TextOptions.setIngoreCase(bIgnoreCase);
        }
        public static void setStandard()
        {
            AppLogic.TextOptions.setStandard();
        }

        //GetMethods
        public static String getStrRefFile()
        {
            return AppLogic.TextOptions.getStrRefFile();
        }
        public static String getAlphabet()
        {
            return AppLogic.TextOptions.getAlphabet();
        }
        public static String getTrenn()
        {
            return AppLogic.TextOptions.getTrenn();
        }
        public static bool getFormat()
        {
            return AppLogic.TextOptions.getFormat();
        }
        public static bool getCase()
        {
            return AppLogic.TextOptions.getCase();
        }
        public static bool getLeerVal()
        {
            return AppLogic.TextOptions.getLeerVal();
        }
        public static bool getGrossVal()
        {
            return AppLogic.TextOptions.getGrossVal();
        }
        public static bool getKleinVal()
        {
            return AppLogic.TextOptions.getKleinVal();
        }
        public static bool getSatzVal()
        {
            return AppLogic.TextOptions.getSatzVal();
        }
        public static bool getZahlVal()
        {
            return AppLogic.TextOptions.getZahlVal();
        }
        public static bool getConvertCase()
        {
            return AppLogic.TextOptions.getConvertCase();
        }
        public static bool getAddx()
        {
            return AppLogic.TextOptions.getAddx();
        }
        public static bool getIgnoreCase()
        {
            return AppLogic.TextOptions.getIgnoreCase();
        }
    }
}
