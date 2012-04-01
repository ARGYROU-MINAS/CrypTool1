// ---------------------------------------------------------------------------
// Name:      actFactoryReg.h
// Product:   cv act library
// Purpose:   Templates for simple factory-registry implementation.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_FactoryReg_h
#define ACT_FactoryReg_h

#include <map>
#include <cstring>

namespace act
{
	//
	// FactoryMapEntry<>
	template<typename CreatePtrT>
	struct FactoryMapEntry
	{
		typedef char KeyType;

		struct KeyLessPredicate
			: public std::binary_function<const KeyType*, const KeyType*, bool> 
		{
			bool operator()(const KeyType* left, const KeyType* right) const
			{
				if(left == 0) return false;
				if(right == 0) return true;
				return strcmp(left, right) < 0;
			}
		};

		typedef std::map
		<	const KeyType*, CreatePtrT, KeyLessPredicate
		>	MapType;

		static const KeyType*	Empty;

		const KeyType*			Name;
		CreatePtrT				createPtr;
	};

	template<typename CreatePtrT>
	const typename FactoryMapEntry<CreatePtrT>::KeyType*
				   FactoryMapEntry<CreatePtrT>::Empty = "";


	//
	// FactoryReg<>
	template
	<
		class ResultT,
		class CreatePtrT,
		class MapEntryT,
		class MapT = typename MapEntryT::MapType
	>
	class FactoryReg
	{
	public:
		typedef typename MapEntryT::KeyType		KeyType;
		typedef MapEntryT						MapEntryType;
		typedef MapT							MapType;

		// Creates default ...
		static ResultT* Create(const KeyType* name)
		{
			if(name == 0) name = MapEntryType::Empty;
			typename MapType::const_iterator result(g_map.find(name));
			return result != g_map.end() ? result->second(name) : 0;
		}

		template<typename ParamT>
		static ResultT* Create(const KeyType* name, ParamT* param)
		{
			if(name == 0) name = MapEntryType::Empty;
			typename MapType::const_iterator result(g_map.find(name));
			return result != g_map.end() ? result->second(name, param) : 0;
		}

		template<typename ParamT>
		static ResultT* Create(ParamT* param)	{ return Create(0, param);	}
		static ResultT* Create()				{ return Create(0);			}

		static const KeyType* GetName(void* createptr)
		{
			if(createptr == 0) return 0;
			for(typename MapType::const_iterator i(g_map.begin()),
				end(g_map.end()); i != end; ++i)
				if(i->second == createptr)
					return i->first;

			return 0;
		}

		static const KeyType* GetNextName(const KeyType* name)
		{
			if(name == 0) 
				return g_map.empty() == true ? 0 : g_map.begin()->first;

			typename MapType::const_iterator result(g_map.find(name));
			return result == g_map.end() || ++result == g_map.end() ? 0 : result->first;
		}

		static CreatePtrT GetCreatePointer(const KeyType* name)
		{
			if(name != 0)
			{
				typename MapType::const_iterator result(g_map.find(name));
				return result != g_map.end() ? result->second : 0;
			}
			return 0;
		}

		static void Insert(const KeyType* name, CreatePtrT createPtr)
		{
			std::pair<typename MapType::iterator, bool> 
				result(g_map.insert(typename MapType::value_type(name, createPtr)));
		}

		static void Insert(const MapEntryType* entry)
		{
			while(entry->Name != 0)
			{
				Insert(entry->Name, entry->createPtr);
				++entry;
			}
		}

	protected:
		static MapT g_map;
	};

	template<class ResultT, class CreatePtrT, class MapEntryT, class MapT>
	MapT FactoryReg<ResultT, CreatePtrT, MapEntryT, MapT>::g_map;

} // namespace act

#endif // ACT_FactoryReg_h
