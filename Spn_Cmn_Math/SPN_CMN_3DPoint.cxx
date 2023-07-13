// SPN_Cmn_3DPoint.cpp: implementation of the CSPN_Cmn_3DPoint class.
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

void Test_Compile_CSPN_Cmn_3DPoint()
{
	CSPN_Cmn_3DPoint<float> P3D;

	CSPN_Cmn_3DPoint<int> P3D_B = SSPN_Cmn_3DPoint__Mk<int, float>(P3D);

	P3D_B = SSPN_Cmn_3DPoint__Multiply_Crs<int, float, int>(P3D, P3D_B);
	float fR = SSPN_Cmn_3DPoint__Multiply_Dot<float, float, int>(P3D, P3D_B);
	P3D = SSPN_Cmn_3DPoint__Multiply_XYZ<float, int, float>(P3D_B, P3D);

	P3D = 0;
	P3D = 0.;
	P3D = 0.f;

	int k = 0;
	{
		SSPN_Cmn_3DPoint<float>	sP3_f;
		SSPN_Cmn_3DPoint<int>	sP3_i;
		SSPN_Cmn_3DPoint<float> sP3_d = sP3_f + sP3_i;
		SSPN_Cmn_3DPoint<float> sP3_ff = (float)k * sP3_i;
		SSPN_Cmn_3DPoint<float> sPkj_Src = sP3_f + sP3_i;

		sP3_i = sP3_i + k * sP3_d;
	}

	{
		SPnt3D_Flt sP3Src_fr_Dst;
		SPnt3D_Flt sP3SrcIncZ_fr_Dst;
		SPnt3D_Flt sPkj_Src = float(k)*sP3SrcIncZ_fr_Dst;
		sPkj_Src = sP3Src_fr_Dst + float(k)*sP3SrcIncZ_fr_Dst;
	}


	//CSPN_Cmn_Matrix<float> Mtx;
	SSPN_Cmn_3DPoint<int> P;
	//SSPN_Cmn_3DPoint<float> sP3R = Mtx  P;
}