// SPN_Cmn_DSize.cpp: implementation of the CSPN_Cmn_2DSize class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"

//
#ifdef _DEBUG
#	ifdef _USE_VC_DBG_NEW
#		define new DEBUG_NEW
#	else
#		ifdef _USE_SPN_DBG_NEW
#			define new _DEBUG_NEW
//#			define delete _DEBUG_DEL
#		endif
#	endif
#endif // 
//

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void Test_Compile_DSize()
{
	CSizeInt Sz;
	CSPN_Cmn_2DSize<float> SzFlt;
	SzFlt = Sz;

	CSPN_Cmn_2DSize<float> SzFlt1;
	SzFlt1 = SzFlt;
}