// BitParity.h: Schnittstelle f�r die Klasse BitParity.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_)
#define AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BitParity  
{
public:
	BitParity();

	char GetParity(const char ch) const
// Beschreibung:	gibt die Parit�t (= Anzahl der 1en des Bin�rwerts (mod 2)) des Bin�rwertes des �bergebenen ASCII-Zeichens
//					zur�ck;
// Parameter:		ASCII-Zeichen, dessen Parit�t berechnet werden soll [in];
// R�ckgabewert:	Parit�t des �bergebenen ASCII-Zeichens [out];
	{
		return GetSumOfBits(ch) % 2;
	}

	char GetSumOfBits(const char ch) const
// Beschreibung:	gibt die Anzahl der 1en des Bin�rwertes des �bergebenen ASCII-Zeichens zur�ck;
// Parameter:		ASCII-Zeichen, dessen Anzahl der 1en im Bin�rwert berechnet werden soll [in];
// R�ckgabewert:	Anzahl der 1en [out];
	{
		return m_ParityBitTable[(unsigned char)ch];
	}

	char GetParity(const char *String, const long NumberOfBits) const
// Beschreibung:	gibt die Gesamt-Parit�t eines character-Strings zur�ck;
// Parameter:		ASCII-Zeichen, dessen Anzahl der 1en im Bin�rwert berechnet werden soll [in];
// R�ckgabewert:	Anzahl der 1en [out];
	{
		return (GetSumOfBits(String, NumberOfBits) % 2);
	}

	int GetSumOfBits(const char *String, const long NumberOfBits) const;
// Beschreibung:	gibt die Anzahl der 1en (= Parit�t) der Bin�rwerte des �bergebenen character-Strings zur�ck;
// Parameter:		character-String, dessen Parit�t berechnet werden soll [in];
// R�ckgabewert:	Parit�t des �bergebenen ASCII-Zeichens [out];

private:
	char m_ParityBitTable[256];

};

#endif // !defined(AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_)
