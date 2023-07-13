// SPN_Cmn_2DLine.cpp: implementation of the CSPN_Cmn_2DLine class.
//
//////////////////////////////////////////////////////////////////////

//{{pch========================================================================
#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"
//}}pch========================================================================

//#include "_SPN_Cmn_Math__inLib.h"
//#include "_SPN_Cmn_Math__inLib.h"

//**************************************************************
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
//**************************************************************

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


#ifdef _DEBUG
void TestCompile_CSPN_Cmn_2DLine()
{
	CSPN_Cmn_2DPoint<float> P1;
	CSPN_Cmn_2DPoint<float> P2;

	CSPN_Cmn_2DPoint<float> P;

	CSPN_Cmn_2DLine<float> Ln(P1, P2);

	bool bOK1 = Ln.GetPoint_onLine_byX(P);
	bool bOK2 = Ln.GetPoint_onLine_byY(P);

	float f1=0;
	CSPN_Cmn_2DLine<float>::IntersectLineAndCircle(f1, P1, P2, P2, P2);
};

#endif // 
