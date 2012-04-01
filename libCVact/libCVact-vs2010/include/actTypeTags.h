// ---------------------------------------------------------------------------
// Name:      actTypeTags.h
// Product:   cv act library
// Purpose:   TypeTag<> and usibility forward declarations.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  09/10/2010
// ---------------------------------------------------------------------------

#ifndef ACT_TypeTags_h
#define ACT_TypeTags_h

namespace act
{
	//
	// Int2Type<>
	template<unsigned Value_>
	struct Int2Type
	{
		enum { Value = Value_ };
	};

	//
	// TypeTag<>
	template<typename TypeT>
	struct TypeTag
	{
		typedef TypeT Type;
	};

	typedef TypeTag<Int2Type<0> > TagAny;
	typedef TypeTag<Int2Type<1> > TagPtr;
	typedef TypeTag<Int2Type<2> > TagPtrArr;
	typedef TypeTag<Int2Type<3> > TagPtrMap;

	//
	// CloneFactory<>
	template<typename Tag, typename P1 = void, typename P2 = void, typename P3 = void>
	struct CloneFactory;

} // namespace act

#endif // ACT_TypeTags_h
