// ---------------------------------------------------------------------------
// Name:      actITokenFileOwner.h
// Product:   cv act library
// Purpose:   The ITokenFileOwner interface is implemented by objects which
//			  refer to a specific location on token represented by ITokenFile.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  28/03/2010
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenFileOwner_h
#define ACT_ITokenFileOwner_h

namespace act
{
	class ITokenFile;

	//
	// ITokenFileOwner
	class ITokenFileOwner
	{
	public:
		virtual ITokenFile* GetPath() const = 0;
		virtual void SetPath(ITokenFile* file) = 0;

	protected:
		virtual ~ITokenFileOwner() { }
	};

} // namespace act

#endif // ACT_ITokenFileOwner_h
