
#ifndef __Include__CSPN_Cmn_3DPlane__H__
#define __Include__CSPN_Cmn_3DPlane__H__


class SPN_CMN_MATH_EXPORT CSPN_Cmn_3DPlane
{
public:
	CSPN_Cmn_3DPlane() {};
	~CSPN_Cmn_3DPlane() {};

public:
	bool FitConstuct_3DPlane_byP3Set(std::vector<SPnt3D_Dbl>& VctP3, double* pfVMaxCoef_NormTo = nullptr);

	bool FitConstuct_3DPlane_byIdx(CSPN_Cmn_3DMtx<BYTE>& Mtx, BYTE vVoxMin, BYTE vVoxMax, Cub3D_Int* pC3_Rng_Known = nullptr, double* pfVMaxCoef_NormTo = nullptr/*提示：指定NORM值会导致平面平移*/);
	bool FitConstuct_3DPlane_byCrd(CSPN_Cmn_3DMtx<BYTE>& Mtx, BYTE vVoxMin, BYTE vVoxMax, Cub3D_Int* pC3_Rng_Known = nullptr, double* pfVMaxCoef_NormTo = nullptr/*提示：指定NORM值会导致平面平移*/);

	void NormMaxCeff_to_Val(double fVMaxNorm);/*提示：指定NORM值会导致平面平移*/


public:
	Pnt3D_Dbl GetCalc_Normale();

	double GetCalc_X(double fY, double fZ);
	double GetCalc_Y(double fX, double fZ);
	double GetCalc_Z(double fX, double fY);

	void CalcSetVox_atPane(CSPN_Cmn_3DMtx<BYTE>& Mtx, Cub3D_Int C3_ROI, BYTE vSet, float fTol);

	// A*X  + B*Y + C*Z + D = 0
	double m_fABCD[4] = { DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX };

public:
	static void TestUnit();
};
#endif //  // __Include__CSPN_Cmn_3DPlane__H__
