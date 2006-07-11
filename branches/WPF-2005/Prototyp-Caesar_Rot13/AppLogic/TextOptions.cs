using System;
using System.Collections.Generic;
using System.Text;

namespace AppLogic
{
    public class TextOptions
    {
        static private String m_alphabet;
        static private String m_StrRefFile;
        static private String m_trenn;

        static private bool m_Format;
        static private bool m_Case;
        static private bool m_LeerVal;
        static private bool m_GrossVal;
        static private bool m_KleinVal;
        static private bool m_SatzVal;
        static private bool m_ZahlVal;
        static private bool m_ConvertCase;
        static private bool m_addx;
        static private bool m_IgnoreCase;


        public TextOptions()
        {
            setStandard();
        }

        //SetMethods
        public static void setStrRefFile(String strRefFile)
        {
            m_StrRefFile = strRefFile;
        }
        public static void setAlphabet(String strAlph)
        {
            m_alphabet = strAlph;
        }
        public static void setTrenn(String strTrenn)
        {
            m_trenn = strTrenn;
        }
        public static void setFormat(bool bFormat)
        {
            m_Format = bFormat;
        }
        public static void setCase(bool bCase)
        {
            m_Case = bCase;
        }
        public static void setLeerVal(bool bLeerVal)
        {
            m_LeerVal = bLeerVal;
        }
        public static void setGrossVal(bool bGrossVal)
        {
            m_GrossVal = bGrossVal;
        }
        public static void setKleinVal(bool bKleinVal)
        {
            m_KleinVal = bKleinVal;
        }
        public static void setSatzVal(bool bSatzVal)
        {
            m_SatzVal = bSatzVal;
        }
        public static void setZahlVal(bool bZahlVal)
        {
            m_ZahlVal = bZahlVal;
        }
        public static void setConvertCase(bool bConvertCase)
        {
            m_ConvertCase = bConvertCase;
        }
        public static void setAddx(bool bAddx)
        {
            m_addx = bAddx;
        }
        public static void setIngoreCase(bool bIgnoreCase)
        {
            m_IgnoreCase = bIgnoreCase;
        }
        public static void setStandard()
        {
            m_StrRefFile = "";
            m_Format = true;
            m_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            m_Case = false;
            m_LeerVal = false;
            m_GrossVal = false;
            m_KleinVal = false;
            m_SatzVal = false;
            m_ZahlVal = false;
            m_ConvertCase = true;
            m_trenn = "X";
            m_addx = true;
            m_IgnoreCase = true;
        }

        //GetMethods
        public static String getStrRefFile()
        {
            return m_StrRefFile;
        }
        public static String getAlphabet()
        {
            return m_alphabet;
        }
        public static String getTrenn()
        {
            return m_trenn;
        }
        public static bool getFormat()
        {
            return m_Format;
        }
        public static bool getCase()
        {
            return m_Case;
        }
        public static bool getLeerVal()
        {
            return m_LeerVal;
        }
        public static bool getGrossVal()
        {
            return m_GrossVal;
        }
        public static bool getKleinVal()
        {
            return m_KleinVal;
        }
        public static bool getSatzVal()
        {
            return m_SatzVal;
        }
        public static bool getZahlVal()
        {
            return m_ZahlVal;
        }
        public static bool getConvertCase()
        {
            return m_ConvertCase;
        }
        public static bool getAddx()
        {
            return m_addx;
        }
        public static bool getIgnoreCase()
        {
            return m_IgnoreCase;
        }
        
    }
}