// ---------------------------------------------------------------------------
// Name:      actSubsystemReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create Subsystem objects.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
//			  Markus Tesche
// Date:	  05/14/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SubsystemReg_h
#define ACT_SubsystemReg_h

namespace act
{
	class ISubsystem;
	class ISubsystemConfig;

	typedef ISubsystem* (*CreateSubsystemPtr)(const char*);
	typedef ISubsystem* (*CreateSubsystemExPtr)(ISubsystemConfig*);

	struct SubsystemMapEntry
	{
		const char*				Name;
		CreateSubsystemPtr		CreatePtr;
		CreateSubsystemExPtr	CreateExPtr;
	};

	class SubsystemReg
	{
	public:
		static ISubsystem* CreateSubsystem(ISubsystemConfig* config);
		static ISubsystem* CreateSubsystem(const char* name, const char* dll_name = 0);

		static CreateSubsystemPtr GetCreatePointer(const char* name);
		static CreateSubsystemExPtr GetCreateExPointer(const char* name);

		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);

		static void Insert(const char* name, CreateSubsystemPtr createptr);
		static void Insert(const char* name, CreateSubsystemExPtr createexptr);
		static void Insert(const SubsystemMapEntry* map);
	};

} // namespace act

#endif	// ACT_SubsystemReg_h
