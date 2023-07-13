// SPN_Cmn_DRect.cpp: implementation of the CSPN_Cmn_2DRect class.
//
//////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"
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

#ifdef _DEBUG
void TestCompile_CSPN_Cmn_2DRect()
{
	CSPN_Cmn_2DRect<float>  RctD;
	CSPN_Cmn_2DPoint<float> PD;

	RctD.IntersectWithLineSect(PD, PD, PD, PD);

	RctD.IsNormalized();
	RctD.IsCoveredBy_Full(RctD);
	RctD.IsCoveredBy_Part(RctD);
}
#endif // 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

