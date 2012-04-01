//////////////////////////////////////////////////////////////////////////////////
// Name:      actRNGKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_RNGKit_h
#define ACT_RNGKit_h
namespace act
{
	class IRNGAlg;

	// Dummy PRNG (uses rand() / srand(time(0)))
	IRNGAlg* CreateDummyPRNG();

	// Deterministic PRNGs
	IRNGAlg* CreateARC4RNG();
	IRNGAlg* CreateBBS();
	IRNGAlg* CreateFIPS186();
	IRNGAlg* CreateFIPS186DES();
	IRNGAlg* CreateLCG();

	// AIS 20, K1 - K4 evaluated deterministic PRNG
	IRNGAlg* CreateFIPS186K4();

	// 'True' RNGs
	IRNGAlg* CreateDevRandomRNG();
#ifndef UNDER_CE_30
	IRNGAlg* CreateWinRNG();
#endif

	// Token RNG (uses IToken::GetRandom())
#ifndef NO_SMARTCARD
	IRNGAlg* CreateTokenRNG();
#endif
}

#endif

