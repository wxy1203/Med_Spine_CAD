// SPN_Cmn_3DCuboid.cpp : Defines the class behaviors for the application.
//

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


void TestCompile_CSPN_Cmn_3DCuboid()
{
	CSPN_Cmn_3DCuboid<int> C3;
	SSPN_Cmn_3DCuboid<int> sC3;

	Pnt3D_Int P3;
	C3 += P3;
	C3 -= P3;

	//C3 = 0.5;

	C3.IntersectCub(C3);
	C3.UnionCub(C3);

	C3.GetCount_XYZ_Pnt_INT();

	C3 = C3;
}