/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

#ifndef _OSTREAM_H
#define _OSTREAM_H 1

#include "la_string.h"

#ifndef _ITERATOR_H
#include "Iterator.h"
#endif
#ifndef _FORMAT_H
#include "Format.h"
#endif

#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////
// OStream

class OStream : public _OStreamFormat
{
public:
	enum Sorting {Off=0, On=1, MaxFirst=1, Descending=1, MinFirst=2, Ascending=2};
	//enum NumericFormat {Default, Int, Percent, Float};
	// Constructors
	OStream(ostream& out=cout);
	OStream(const char* s);
	~OStream();
	// Operations
	operator ostream&() {return *m_out;}
	OStream& flush() {m_out->flush(); return *this;}
	OStream& endl() {*m_out << GetFormat(LF); m_out->flush(); return *this;}
	OStream& sep() {*m_out << GetFormat(Sep); m_out->flush(); return *this;}
// Implementation
private:
	// Helpers
	void Init();
	OStream(const OStream&);
	OStream operator=(const OStream&);
	// Data
//private:
protected:
	ostream* m_out;
	int m_freeout;
	__OStreamFormat m_format;
public:
	long GetFormat(Format::Index i) const {return m_format.Get(i);}
	const String& GetFormat(Format::SIndex i) const {return m_format.Get(i);}
	long operator[](Format::Index i) const {return m_format.Get(i);}
	const String& operator[](Format::SIndex i) const {return m_format.Get(i);}

/////////////////////////////////////////////////////////////////////
// OStream manipulators
friend inline OStream& operator<<(OStream& b, const Manipulator<Format>& m) { m.manip(b.m_format); return b; }
//friend inline OStream& operator<<(OStream& b, const CManip2<Format,int, String const&>& m) { m.manip(b.m_format); return b; }
//friend inline OStream& operator<<(OStream& b, const CManip2<Format,int, String const&> m) { m.manip(b.m_format); return b; }
//friend inline OStream& operator<<(OStream& b, const CManip2<Format,int, long>& m) { m.manip(b.m_format); return b; }
//friend inline OStream& operator<<(OStream& b, const CManip2<Format,int, long> m) { m.manip(b.m_format); return b; }

friend inline OStream& operator<<(OStream& out, OStream& (* _f)(OStream&)) { (*_f)(out); return out; }
friend inline OStream& flush(OStream& out) { return out.flush(); }
friend inline OStream& endl(OStream& out) { return out.endl(); }
friend inline OStream& sep(OStream& out) { return out.sep(); }

};

extern OStream DefaultOStream;

/////////////////////////////////////////////////////////////////////
// PlotStream

class PlotStream : public OStream
{
public:
	PlotStream(const char *s="PlotData.txt");
	~PlotStream();
// Implementation
private:
	String m_filename;
};


/////////////////////////////////////////////////////////////////////
// OStream << 

inline OStream& operator<<(OStream& out, double t)
{ 
	if (out[OStream::Percent]) 
		(ostream&)out << setw(out[OStream::Width]) << setiosflags(ios::fixed)<< setprecision(out[OStream::Precision])<< t*100.0 << resetiosflags(ios::fixed) << setprecision(6);
	else 
		(ostream&)out << setw(out[OStream::Width]) << setprecision(out[OStream::Precision])<< t << setprecision(6);
	return out; 
}

inline OStream& operator<<(OStream& out, unsigned long t)
{ 
	if (out[OStream::Hex]) 
		(ostream&)out << hex << t << dec;
	else 
		(ostream&)out << t;
	return out; 
}
inline OStream& operator<<(OStream& out, long t)
{ 
	if (out[OStream::Hex]) 
		(ostream&)out << hex << t << dec;
	else 
		(ostream&)out << t;
	return out; 
}
inline OStream& operator<<(OStream& out, int t)
{ 
	if (out[OStream::Hex]) 
		(ostream&)out << hex << t << dec;
	else 
		(ostream&)out << t;
	return out; 
}


#define OSTREAMOP(T) inline OStream& operator<<(OStream& out, T t){ (ostream&)out << t; return out; }
OSTREAMOP(char)
OSTREAMOP(char*)
#undef OSTREAMOP


#endif /* _OSTREAM_H */