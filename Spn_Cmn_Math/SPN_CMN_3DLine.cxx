// SPN_Cmn_3DLine.cpp: implementation of the CSPN_Cmn_3DLine class.
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

void TestCompile_CSPN_Cmn_3DLine()
{
	CSPN_Cmn_3DLine<float> Ln3D;
	float zMin = 0, zMax = 0;
	Ln3D.Limit_BgnEnd_onLn__into_Range_Z(zMin, zMax);

	Ln3D.SameDir_ByXYZ(Ln3D, 0);

	Ln3D.ComputePointOnLine_byAnyKnownCorrd(Ln3D.PointBgn(), 0);
}
