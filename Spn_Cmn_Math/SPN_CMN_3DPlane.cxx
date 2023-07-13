
#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif // 

#include <stdio.h>
//*****************************************************************************************

#include <iostream>
//#include <windows.h>
#include <vector>
using namespace std;
#include "math.h"

double test1[24][3]
{
{-735, -312, 193},
{ -252 ,-298 ,179 },
{ 290 ,-264 ,164 },
{ 657 ,-252 ,154 },
{ -753 ,82 ,193 },
{ -92 ,27 ,175 },
{ 656 ,31 ,153 },
{ -726 ,389 ,193 },
{ -27 ,355 ,173 },
{ 652 ,413 ,153 },
{ -922 ,-306 ,199 },
{ -915 ,-114 ,199 },
{ -791 ,87 ,195 },
{ -729 ,390 ,194 },
{ 24 ,422 ,172 },
{ 1 ,273 ,173 },
{ 10 ,168 ,172 },
{ -2 ,3 ,172 },
{ -16 ,-130 ,173 },
{ -22 ,-292 ,173 },
{ 615 ,-342 ,155 },
{ 724 ,-137 ,152 },
{ 712 ,64 ,152 },
{ 728 ,359 ,151 },
};

double test[24][3] =
{
{-735 ,-312 ,6},
{-252 ,-298 ,6},
{290 ,-264 ,7},
{657 ,-252 ,7},
{-753 ,82 ,15 },
{-92 ,27 ,15 },
{656 ,31 ,14 },
{-726 ,389 ,24 },
{-27 ,355 ,25 },
{652 ,413 ,26 },
{-922 ,-306 ,4},
{-915 ,-114 ,10},
{-791 ,87 ,14 },
{-729 ,390 ,22 },
{24 ,422 ,25 },
{1 ,273 ,21 },
{10 ,168 ,18 },
{-2 ,3 ,13 },
{-16 ,-130 ,11},
{-22 ,-292 ,6},
{615 ,-342 ,5},
{724 ,-137 ,10},
{712 ,64 ,15},
{728 ,359 ,21},
};

struct Point3D
{
	double x;
	double y;
	double z;
};

void _LS_column_principle_gauss(int N, double **a)
{
	int k = 0, i = 0, r = 0, j = 0;
	double t;
	for (k = 0; k < N - 1; k++)
	{
		for (i = k; i < N; i++)
		{
			r = i;
			t = (double)fabs(a[r][k]);
			if (fabs(a[i][k]) > t)
			{
				r = i;
			}
		}

		if (a[r][k] == 0)
		{
			break;
		}
		for (j = k; j < N + 1; j++)
		{
			t = a[r][j];
			a[r][j] = a[k][j];
			a[k][j] = t;
		}

		for (i = k + 1; i < N; i++)
		{
			for (j = k + 1; j < N + 1; j++)
			{
				a[i][j] = a[i][j] - a[i][k] / a[k][k] * a[k][j];
			}
		}
	}

	double he = 0;
	for (k = N - 1; k >= 0; k--)
	{
		he = 0;
		for (j = k + 1; j < N; j++)
		{
			he = he + a[k][j] * a[j][N];
		}
		a[k][N] = (a[k][N] - he) / a[k][k];
	}
}

bool _LS_Least_squares(vector<Point3D>& v_Point, double M[3])
{
	double **c = NULL;
	c = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		c[i] = new double[4];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}

	c[0][0] = v_Point.size();
	for (int i = 0; i < v_Point.size(); i++)
	{
		c[0][1] = c[0][1] + v_Point.at(i).x;
		c[0][2] = c[0][2] + v_Point.at(i).y;
		c[0][3] = c[0][3] + v_Point.at(i).z;

		c[1][1] = c[1][1] + v_Point.at(i).x*v_Point.at(i).x;
		c[1][2] = c[1][2] + v_Point.at(i).x*v_Point.at(i).y;
		c[1][3] = c[1][3] + v_Point.at(i).x*v_Point.at(i).z;
		c[2][2] = c[2][2] + v_Point.at(i).y*v_Point.at(i).y;
		c[2][3] = c[2][3] + v_Point.at(i).y*v_Point.at(i).z;
	}

	c[1][0] = c[0][1];
	c[2][0] = c[0][2];
	c[2][1] = c[1][2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f", c[i][j]);
		}
		printf("\n");
	}
	_LS_column_principle_gauss(3, c);

	for (int i = 0; i < 3; i++)
	{
		M[i] = c[i][3];
	}

	for (int i = 0; i < 3; i++)
	{
		delete[]c[i];
		c[i] = NULL;
	}
	delete[]c;
	c = NULL;

	return true;
}

int _LS_main()
{
	Point3D temp[23];
	for (int i = 0; i < 24; i++)
	{
		temp[i].x = test[i][0];
		temp[i].y = test[i][1];
		temp[i].z = test[i][2];
	}

	vector<Point3D>v_Point;
	double M[3];
	for (int i = 0; i < 24; i++)
	{
		v_Point.push_back(temp[i]);
	}

	_LS_Least_squares(v_Point, M);

	for (int i = 0; i < 3; i++)
	{
		printf("M%d = %lf\n", i, M[i]);
	}

	//[20210727_14:56:54 ]:Sleep(100000);
	return 0;
}

bool _FitPlane3D(double fABC[3], SPnt3D_Dbl* psP3, int nP3);
bool _FitPlane3D_Call(double fABC[3], std::vector<SPnt3D_Dbl>& v_Point)
{
	bool bOK = _FitPlane3D(fABC, v_Point.data(), v_Point.size());
	return bOK;
}

void _NormMax_to_Val(double fABCD[4], double fVMaxNorm)
{
	assert(!FLT_EQ(fVMaxNorm, 0.f));

	double fAV = fabs(fABCD[0]);
	double fBV = fabs(fABCD[1]);
	double fCV = fabs(fABCD[2]);
	double fDV = fabs(fABCD[3]);

	double fMax_AbcdAvg = (fAV > fBV) ? (fAV) : (fBV);
	fMax_AbcdAvg = (fCV > fMax_AbcdAvg) ? (fCV) : (fMax_AbcdAvg);
	fMax_AbcdAvg = (fDV > fMax_AbcdAvg) ? (fDV) : (fMax_AbcdAvg);

	if (FLT_EQ(fMax_AbcdAvg, 0.f))
	{
		return;
	}

	fABCD[0] = (fVMaxNorm * fABCD[0] / fMax_AbcdAvg);
	fABCD[1] = (fVMaxNorm * fABCD[1] / fMax_AbcdAvg);
	fABCD[2] = (fVMaxNorm * fABCD[2] / fMax_AbcdAvg);
	fABCD[3] = (fVMaxNorm * fABCD[3] / fMax_AbcdAvg);
}

void CSPN_Cmn_3DPlane::NormMaxCeff_to_Val(double fVMaxNorm)
{
	_NormMax_to_Val(m_fABCD, fVMaxNorm);
}

/****************************************************************************************************************/
double _FitPlane3D_Get_fD_byABC(double fABC[3], std::vector<SPnt3D_Dbl>& Vct_sP3)
{
	CSPN_Cmn_CArray<double> Arr_fD;
	{
		Arr_fD.SetSize(Vct_sP3.size());
		Arr_fD.SetAllMember(0);
	}

	double fDsum = 0.f;
	for (int i = 0; i < Arr_fD.GetSize(); i++)
	{
		SPnt3D_Dbl& sP3 = Vct_sP3[i];
		Arr_fD[i] = 0 - (fABC[0] * sP3.x() + fABC[1] * sP3.y() + fABC[2] * sP3.z());
		fDsum += Arr_fD[i];
	}

	double fDAvg = fDsum / Arr_fD.GetSize();

	return fDAvg;
}

bool CSPN_Cmn_3DPlane::FitConstuct_3DPlane_byP3Set(std::vector<SPnt3D_Dbl>& Vct_sP3, double* pfVMaxCoef_NormTo/* = nullptr*/)
{
	/**************************************************
	此算法测试有误:
	double fABC1[3];
	bool bOK1 = Least_squares(v_Point, fABC1);
	**************************************************/

	double fABC2[3];
	bool bOK2 = _FitPlane3D_Call(fABC2, Vct_sP3);

	double* fABC = fABC2;
	bool& bOK = bOK2;
	m_fABCD[0] = fABC[0];
	m_fABCD[1] = fABC[1];
	m_fABCD[2] = fABC[2];
	m_fABCD[3] = _FitPlane3D_Get_fD_byABC(fABC, Vct_sP3);

	if (pfVMaxCoef_NormTo)
	{
		NormMaxCeff_to_Val(*pfVMaxCoef_NormTo);
	}
	return bOK;
}
/****************************************************************************************************************/
double CSPN_Cmn_3DPlane::GetCalc_X(double fY, double fZ)
{
	if (FLT_EQ(m_fABCD[0], 0.f))
	{
		return DBL_MAX;
	}
	else
	{
		double fX = -(m_fABCD[3] + (m_fABCD[1] * fY + m_fABCD[2] * fZ)) / m_fABCD[0];
		return fX;
	}
}

double CSPN_Cmn_3DPlane::GetCalc_Y(double fX, double fZ)
{
	if (FLT_EQ(m_fABCD[1], 0.f))
	{
		return DBL_MAX;
	}
	else
	{
		double fY = -(m_fABCD[3] + (m_fABCD[0] * fX + m_fABCD[2] * fZ)) / m_fABCD[1];
		return fY;
	}
}

double CSPN_Cmn_3DPlane::GetCalc_Z(double fX, double fY)
{
	if (FLT_EQ(m_fABCD[2], 0.f))
	{
		return DBL_MAX;
	}
	else
	{
		double fZ = -(m_fABCD[3] + (m_fABCD[0] * fX + m_fABCD[1] * fY)) / m_fABCD[2];
		return fZ;
	}
}

Pnt3D_Dbl CSPN_Cmn_3DPlane::GetCalc_Normale()
{
	assert(false);//???????????????????????????????????????? 待实现
	Pnt3D_Dbl P3Tmp;
	return P3Tmp;
}

//[20210524_13:46:02 ]: 此均值
bool _FitSttc__Add_RndFit_3DPlane_Sample(CSPN_Cmn_CArray<double, double>& Arr_fA,
										 CSPN_Cmn_CArray<double, double>& Arr_fB,
										 CSPN_Cmn_CArray<double, double>& Arr_fC,
										 CSPN_Cmn_CArray<double, double>& Arr_fD,
										 CSPN_Cmn_3DMtx<BYTE>& Mtx,
										 CSPN_Cmn_CArray<int, int>& Arr_iVox,
										 CSPN_Cmn_CArray<bool, bool>& Arr_bUsedVox,
										 double fLmin_Smpl_3Side,
										 double fK_DL_SideDiff_2to1)
{
	int iVox123[3] = { -1, -1, -1 };
	int iiVox123_Try[3] = { -1, -1, -1 };

	bool bOK_3P = false;
	const int nTryMax = Arr_iVox.GetSize();

	SPnt3D_Int P123[3] = {
		Pnt3D_Int(-1,-1,-1),
		Pnt3D_Int(-1,-1,-1),
		Pnt3D_Int(-1,-1,-1) };

	for (int iTry3P = 0; iTry3P < nTryMax; iTry3P++)
	{
		//找到未用过的三个随机点:
		int nOK_3P = 0;
		for (int iP = 0; iP < 3; iP++)
		{
			for (int iTry_iP = 0; iTry_iP < nTryMax; iTry_iP++)
			{
				int iiVoxTry = rand() % Arr_iVox.GetSize();
				if (!Arr_bUsedVox[iiVoxTry])
				{
					iiVox123_Try[iP] = iiVoxTry;
					nOK_3P++;
					break;
				}
			}
		}

		if (nOK_3P < 3)
		{
			return false; // 可用点不足!
		}

		//判断其效性:
		P123[3];
		{
			Mtx.GetVoxIdx3D(Arr_iVox[iiVox123_Try[0]], P123[0]);
			Mtx.GetVoxIdx3D(Arr_iVox[iiVox123_Try[1]], P123[1]);
			Mtx.GetVoxIdx3D(Arr_iVox[iiVox123_Try[2]], P123[2]);

			float fLSide123[3] =
			{
				P123[0].GetDistTo(P123[1]),
				P123[1].GetDistTo(P123[2]),
				P123[2].GetDistTo(P123[0])
			};

			//单边长度规则:
			if (fLSide123[0] < fLmin_Smpl_3Side ||
				fLSide123[1] < fLmin_Smpl_3Side ||
				fLSide123[2] < fLmin_Smpl_3Side)
			{
				bOK_3P = false;
				continue;
			}

			//三边长度规则(免花线规则):
			float fL3Sum = fLSide123[0] + fLSide123[1] + fLSide123[2];
			{
				bool bOK_3P = true;
				for (int i = 0; i < 3; i++)
				{
					float fL12 = fLSide123[i % 3] + fLSide123[((i + 1) % 3)];
					float fL3 = fLSide123[(i + 2) % 3];

					if ((fL12 - fL3) / fL12 < fK_DL_SideDiff_2to1)
					{
						bOK_3P = false;
						continue;
					}
				}
			}
		}

		bOK_3P = true;
		iVox123[0] = Arr_iVox[iiVox123_Try[0]];
		iVox123[1] = Arr_iVox[iiVox123_Try[1]];
		iVox123[2] = Arr_iVox[iiVox123_Try[2]];

		Arr_bUsedVox[iiVox123_Try[0]] = true;
		Arr_bUsedVox[iiVox123_Try[1]] = true;
		Arr_bUsedVox[iiVox123_Try[2]] = true;
		break;
	}

	//平面方程:
	if (bOK_3P)
	{
		int ii = 0;
		//for (; ii < 3; ii++)
		{
			int ii0 = ii;
			double x1 = P123[ii0][0];
			double y1 = P123[ii0][1];
			double z1 = P123[ii0][2];

			int ii1 = (ii + 1) % 3;
			double x2 = P123[ii1][0];
			double y2 = P123[ii1][1];
			double z2 = P123[ii1][2];

			int ii2 = (ii + 2) % 3;
			double x3 = P123[ii2][0];
			double y3 = P123[ii2][1];
			double z3 = P123[ii2][2];

			//#ifdef _USE_3P_2_EqtnPlane_1
			//			///****************************************************************************************************************
			//			/**********************************************************************************************************
			//			*********************以下网参公式有误!
			//			将已知三个点的坐标分别用P1(x1, y1, z1)，P2(x2, y2, z2)，P3(x3, y3, z3)表示。（P1，P2，P3不在同一条直线上。）
			//			设通过P1，P2，P3三点的平面方程为A(x - x1) + B(y - y1) + C(z - z1) = 0 。
			//			化简为一般式：Ax + By + Cz + D = 0。
			//			将P1(x1, y1, z1)点数值代入方程Ax + By + Cz + D = 0。
			//			即可得到：Ax1 + By 1 + Cz1 + D = 0。
			//			化简得D = -(A * x1 + B * y1 + C * z1)。
			//			则可以根据P1(x1, y1, z1)，P2(x2, y2, z2)，P3(x3, y3, z3)三点坐标分别求得A、B、C的值，如下：
			//				A = (y3 - y1)*(z3 - z1) - (z2 - z1)*(y3 - y1);
			//				B = (x3 - x1)*(z2 - z1) - (x2 - x1)*(z3 - z1);
			//				C = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
			//			又
			//				D = -(A * x1 + B * y1 + C * z1)，所以可以求得D的值。
			//				将求得的A、B、C、D值代入一般式方程就可得过P1，P2，P3的平面方程 :
			//					Ax + By + Cz + D = 0 (一般式)。
			//			**********************************************************************************************************/
			//			double fA = (y3 - y1)*(z3 - z1) - (z2 - z1)*(y3 - y1);
			//			double fB = (x3 - x1)*(z2 - z1) - (x2 - x1)*(z3 - z1);
			//			double fC = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
			//			double fD = -(fA * x1 + fB * y1 + fC * z1);
			//#else
						///****************************************************************************************************************
						/*
							a = +y1z2 - y1z3 - y2z1 + y2z3 + y3z1 - y3z2，
							b = -x1z2 + x1z3 + x2z1 - x2z3 - x3z1 + x3z2，
							c = +x1y2 - x1y3 - x2y1 + x2y3 + x3y1 - x3y2，
							d = -x1y2z3 + x1y3z2 + x2y1z3 - x2y3z1 - x3y1z2 + x3y2z1
						*/
			double fA = +y1 * z2 - y1 * z3 - y2 * z1 + y2 * z3 + y3 * z1 - y3 * z2;
			double fB = -x1 * z2 + x1 * z3 + x2 * z1 - x2 * z3 - x3 * z1 + x3 * z2;
			double fC = +x1 * y2 - x1 * y3 - x2 * y1 + x2 * y3 + x3 * y1 - x3 * y2;
			double fD = -x1 * y2 * z3 + x1 * y3 * z2 + x2 * y1 * z3 - x2 * y3 * z1 - x3 * y1 * z2 + x3 * y2 * z1;
			//#endif // //_USE_3P_2_EqtnPlane_1
			{
				double fAV = fabs(fA);
				double fBV = fabs(fB);
				double fCV = fabs(fC);
				double fDV = fabs(fD);

				double fMax_AbcdAvg = (fAV > fBV) ? (fAV) : (fBV);
				fMax_AbcdAvg = (fCV > fMax_AbcdAvg) ? (fCV) : (fMax_AbcdAvg);
				fMax_AbcdAvg = (fDV > fMax_AbcdAvg) ? (fDV) : (fMax_AbcdAvg);

				fA = int(1000 * fA / fMax_AbcdAvg);
				fB = int(1000 * fB / fMax_AbcdAvg);
				fC = int(1000 * fC / fMax_AbcdAvg);
				fD = int(1000 * fD / fMax_AbcdAvg);
			}
			Arr_fA.Add(fA);
			Arr_fB.Add(fB);
			Arr_fC.Add(fC);
			Arr_fD.Add(fD);
		}

		return true;
	}
	else
	{
		return false;
	}
}

#ifdef _DEBUG
int  g_nItrt_Cnvrg = -1;
#	define C_NBUF_ABCD_3DPlaneShow 20
double g_fABCD_Tail[C_NBUF_ABCD_3DPlaneShow][4];
#endif // 

bool _FitSttc__FitConstuct_3DPlane_byIdx(double fABCD[4],
										 CSPN_Cmn_3DMtx<BYTE>& Mtx,
										 BYTE vVoxMin,
										 BYTE vVoxMax,
										 int nItrtMin,
										 int nItrtMax,
										 double fTol_EndItrt,
										 Cub3D_Int* pC3_Rng_Known /*= nullptr*/)
{
	//1. 参数准备
	Cub3D_Int C3_Rng;
	{
		if (pC3_Rng_Known)
		{
			C3_Rng = *pC3_Rng_Known;
		}
		else
		{
			bool bOK = Mtx.FindBoundCub3D_InRange(vVoxMin, vVoxMax, C3_Rng.m_P3D_Min, C3_Rng.m_P3D_Max);
			if (!bOK)
			{
				return false;
			}
		}
	}

	if (0 == C3_Rng.GetLength_CubEdge_X() ||
		0 == C3_Rng.GetLength_CubEdge_Y() ||
		0 == C3_Rng.GetLength_CubEdge_Z())
	{
		return false;
	}

	CSPN_Cmn_CArray<int, int> Arr_iVox; // 以此加速随机采样速度
	{
		Arr_iVox.SetSize(0, Mtx.GetSize_Slc());

		for (int k = C3_Rng.m_P3D_Min[2]; k < C3_Rng.m_P3D_Max[2]; k++)
		{
			for (int j = C3_Rng.m_P3D_Min[1]; j < C3_Rng.m_P3D_Max[1]; j++)
			{
				BYTE* pVox = Mtx.GetSliceRowBuf(k, j) + C3_Rng.m_P3D_Min[0];
				for (int i = C3_Rng.m_P3D_Min[0]; i < C3_Rng.m_P3D_Max[0]; i++, pVox++)
				{
					if (*pVox >= vVoxMin && *pVox <= vVoxMax)
					{
						int iVox = Mtx.GetVoxID(i, j, k);
						Arr_iVox.Add(iVox);
					}
				}
			}
		}
	}
	CSPN_Cmn_CArray<bool, bool> Arr_bUsedVox; // 防止重复采样, 导致拟合结果不具代表性
	{
		Arr_bUsedVox.SetSize(Arr_iVox.GetSize());
		Arr_bUsedVox.SetAllMember(false);
	}

	double fLmin_Smpl_3Side = 0.f; //防止取点太近
	{
		double fL_AvgCubSide = 0.33f * (
			C3_Rng.GetLength_CubEdge_X() +
			C3_Rng.GetLength_CubEdge_Y() +
			C3_Rng.GetLength_CubEdge_Z());

		fLmin_Smpl_3Side = 0.5 * fL_AvgCubSide;
	}

	double fK_DL_SideDiff_2to1 = 1.f / 4.f; // 防止三点接近共线: 任意两边长之和与和三边的差, 不得小于总周长的这个比例, 否则拟合误差较大

	//开始随机采样拟合:
	CSPN_Cmn_CArray<double, double> Arr_fA;
	CSPN_Cmn_CArray<double, double> Arr_fB;
	CSPN_Cmn_CArray<double, double> Arr_fC;
	CSPN_Cmn_CArray<double, double> Arr_fD;
	{
		Arr_fA.SetSize(0, nItrtMin);
		Arr_fB.SetSize(0, nItrtMin);
		Arr_fC.SetSize(0, nItrtMin);
		Arr_fD.SetSize(0, nItrtMin);
	}

	//2. 采样拟合
	double fABCD_Avg_Lst[4] = { DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX };
	double fABCD_Avg_Cur[4] = { DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX };

	bool bOK_Fine = false;
	if (nItrtMin < 2)
	{
		nItrtMin = 2;
	}

	int nOK_Tol = 0;
	int nOK_Tol_Min = 20;

#ifdef _DEBUG
	struct _S4_DBL
	{
		double fABCD[4];
	};
	CSPN_Cmn_CArray<_S4_DBL> Arr_AvgABCD_Log;
	{
		Arr_AvgABCD_Log.SetSize(0, 1024);
	}
#endif // 

	int iIt = 0;
	for (; !bOK_Fine && iIt < nItrtMax; iIt++)
	{
		bool bOK = _FitSttc__Add_RndFit_3DPlane_Sample(Arr_fA, Arr_fB, Arr_fC, Arr_fD,
													   Mtx, Arr_iVox, Arr_bUsedVox, fLmin_Smpl_3Side, fK_DL_SideDiff_2to1);

		if (!bOK)
		{
			break;
		}

		if (iIt > 0)
		{
			memcpy(fABCD_Avg_Lst, fABCD_Avg_Cur, 4 * sizeof(double));
		}
		fABCD_Avg_Cur[0] = Arr_fA.GetAvg();
		fABCD_Avg_Cur[1] = Arr_fB.GetAvg();
		fABCD_Avg_Cur[2] = Arr_fC.GetAvg();
		fABCD_Avg_Cur[3] = Arr_fD.GetAvg();
		{
			_NormMax_to_Val(fABCD_Avg_Cur, 1.f);
		}

#ifdef _DEBUG
		_S4_DBL sfABCD_Avg;
		{
			memcpy(sfABCD_Avg.fABCD, fABCD_Avg_Cur, 4 * sizeof(double));
		};
		Arr_AvgABCD_Log.Add(sfABCD_Avg);
#endif // 


		if (iIt < 1)
		{
			continue;
		}
		double fABCD_Mrg = DBL_MAX;
		{
			double fAV = fabs(Arr_fA.GetLast());
			double fBV = fabs(Arr_fB.GetLast());
			double fCV = fabs(Arr_fC.GetLast());
			double fDV = fabs(Arr_fD.GetLast());
			//fABCD_Mrg = (fAV > fBV) ? (fAV) : (fBV);
			//fABCD_Mrg = (fCV > fABCD_Mrg) ? (fCV) : (fABCD_Mrg);
			//fABCD_Mrg = (fDV > fABCD_Mrg) ? (fDV) : (fABCD_Mrg);
			fABCD_Mrg = (fAV + fBV + fCV + fDV) / 4; // 均值更有利于振荡控制????????
		}

		double fMax_dABCD = DBL_MAX;
		{
			double fdAV = fabs(Arr_fA.GetLast() - Arr_fA[Arr_fA.GetUpperBound() - 1]);
			double fdBV = fabs(Arr_fB.GetLast() - Arr_fB[Arr_fB.GetUpperBound() - 1]);
			double fdCV = fabs(Arr_fC.GetLast() - Arr_fC[Arr_fC.GetUpperBound() - 1]);
			double fdDV = fabs(Arr_fD.GetLast() - Arr_fD[Arr_fD.GetUpperBound() - 1]);

			fMax_dABCD = (fdAV > fdBV) ? (fdAV) : (fdBV);
			fMax_dABCD = (fdCV > fMax_dABCD) ? (fdCV) : (fMax_dABCD);
			fMax_dABCD = (fdDV > fMax_dABCD) ? (fdDV) : (fMax_dABCD);
		}

		if (fMax_dABCD / fABCD_Mrg < fTol_EndItrt)
		{
			nOK_Tol++;
			if (nOK_Tol > nOK_Tol_Min)
			{
				break;
			}
		}
		else
		{
			nOK_Tol = 0;
		}
	}
#ifdef _DEBUG
	g_nItrt_Cnvrg = iIt + 1;

	for (int iTail = 0; iTail < C_NBUF_ABCD_3DPlaneShow; iTail++)
	{
		int iIt_Log = iIt - iTail - 1;
		if (iIt_Log < 0)
		{
			break;
		}

		::memcpy(g_fABCD_Tail[iTail], Arr_AvgABCD_Log[iIt_Log].fABCD, 4 * sizeof(double));
	}
#endif // 

	//3. 平均结果:
	fABCD[0] = fABCD_Avg_Cur[0];
	fABCD[1] = fABCD_Avg_Cur[1];
	fABCD[2] = fABCD_Avg_Cur[2];
	fABCD[3] = fABCD_Avg_Cur[3];

	return true;
}

bool CSPN_Cmn_3DPlane::FitConstuct_3DPlane_byIdx(CSPN_Cmn_3DMtx<BYTE>& Mtx,
												BYTE vVoxMin,
												BYTE vVoxMax,
												Cub3D_Int* pC3_Rng_Known/* = nullptr*/,
												double* pfVMaxCoef_NormTo/* = nullptr*/)
{
	//1. 参数准备
	Cub3D_Int C3_Rng;
	{
		if (pC3_Rng_Known)
		{
			C3_Rng = *pC3_Rng_Known;
		}
		else
		{
			bool bOK = Mtx.FindBoundCub3D_InRange(vVoxMin, vVoxMax, C3_Rng.m_P3D_Min, C3_Rng.m_P3D_Max);
			if (!bOK)
			{
				return false;
			}
		}
	}

	if (0 == C3_Rng.GetLength_CubEdge_X() ||
		0 == C3_Rng.GetLength_CubEdge_Y() ||
		0 == C3_Rng.GetLength_CubEdge_Z())
	{
		return false;
	}

	std::vector<SPnt3D_Dbl> vP3;
	{
		SPnt3D_Dbl sP3;
		for (int k = C3_Rng.m_P3D_Min[2]; k < C3_Rng.m_P3D_Max[2]; k++)
		{
			for (int j = C3_Rng.m_P3D_Min[1]; j < C3_Rng.m_P3D_Max[1]; j++)
			{
				BYTE* pVox = Mtx.GetSliceRowBuf(k, j) + C3_Rng.m_P3D_Min[0];
				for (int i = C3_Rng.m_P3D_Min[0]; i < C3_Rng.m_P3D_Max[0]; i++, pVox++)
				{
					if (*pVox >= vVoxMin && *pVox <= vVoxMax)
					{
						sP3.x() = i;
						sP3.y() = j;
						sP3.z() = k;

						vP3.push_back(sP3);
					}
				}
			}
		}
	}

	bool bOK = FitConstuct_3DPlane_byP3Set(vP3, pfVMaxCoef_NormTo);

	return bOK;
}

bool CSPN_Cmn_3DPlane::FitConstuct_3DPlane_byCrd(CSPN_Cmn_3DMtx<BYTE>& Mtx,
												BYTE vVoxMin,
												BYTE vVoxMax,
												Cub3D_Int* pC3_Rng_Known/* = nullptr*/,
												double* pfVMaxCoef_NormTo/* = nullptr*/)
{
	bool bOK = FitConstuct_3DPlane_byIdx(Mtx, vVoxMin, vVoxMax, pC3_Rng_Known, nullptr);
	if (!bOK)
	{
		return false;
	}

	/**************************************************************************
		a*iX + b*iY + c*iZ + d = 0
	=>　a*(fX-X0)/fSpcX + b*(fY-Y0)/fSpcY + c*(fZ-Z0)/fSpcZ + d = 0;
	=>　(a/SpcX)*fX + (a/SpcY)*fY + (a/SpcZ)*fZ + (d - a*X0/fSpcX - b*Y0/SpcY - c*Z0/SpcZ)= 0;
	=> 	a' = a / SpcX;
		b' = b / SpcY;
		c' = c / SpcZ;
		d' = d - a*X0/fSpcX - b*Y0/SpcY - c*Z0/SpcZ;
	**************************************************************************/
	double& fAi = m_fABCD[0];
	double& fBi = m_fABCD[1];
	double& fCi = m_fABCD[2];
	double& fDi = m_fABCD[3];

	Pnt3D_Dbl P0 = Mtx.GetP3D_Bgn().ToDouble();

	double fSpcX = Mtx.GetP3D_Spc_X();
	double fSpcY = Mtx.GetP3D_Spc_Y();
	double fSpcZ = Mtx.GetP3D_Spc_Z();
	assert(!FLT_EQ(fSpcX, 0) && !FLT_EQ(fSpcY, 0) && !FLT_EQ(fSpcZ, 0));

	m_fABCD[0] = fAi / fSpcX;
	m_fABCD[1] = fBi / fSpcY;
	m_fABCD[2] = fCi / fSpcZ;
	m_fABCD[3] = fDi - (fAi * P0.x() / fSpcX + fBi * P0.y() / fSpcY + fCi * P0.z() / fSpcZ);

	if (pfVMaxCoef_NormTo)
	{
		NormMaxCeff_to_Val(*pfVMaxCoef_NormTo);
	}

	return bOK;
}

//肋体形态操作边界为2即有病例被破坏, 所以形态分割只应尝试到1层, 如失败, 则用此平面拟合织造面切!

void CSPN_Cmn_3DPlane::TestUnit()
{
	double kABCD[4] = { 1, 1, 1, -100 };
	double fTolR = 5;

	CSPN_Cmn_3DMtx<BYTE> Mtx;
	{
		Mtx.Set_nXYZ(100, 100, 100);
		Mtx.SetVox_All(0);

		for (int k = 0; k < Mtx.GetSize_Z(); k++)
		{
			for (int j = 0; j < Mtx.GetSize_Y(); j++)
			{
				for (int i = 0; i < Mtx.GetSize_X(); i++)
				{
					float fZero = kABCD[0] * i + kABCD[1] * j + kABCD[2] * k + kABCD[3];
					if (fZero > -fTolR && fZero < fTolR)
					{
						Mtx.SetVox(i, j, k, 1);
					}
				}
			}
		}
	}

	//__GetAllowRef_Global__for_ShowMtx_Dbg() = 1;
	//ShowMtx_Dbg(Mtx, "Mtx_3DPlangFit_UnitTest");
	//__GetAllowRef_Global__for_ShowMtx_Dbg() = 0;

	BYTE iVoxMin = 1;
	BYTE iVoxMax = 1;

	/*************************************************************************************
	//[20210524_13:56:44 ]: 已证实此方法效果不佳XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	CSPN_Cmn_3DPlane Pln3D_TB;
	int nItMin = 100;
	int nItMax = 10000;
	float fTol_Itrt = 0.001f;
	_FitSttc__FitConstuct_3DPlane_byIdx(Pln3D_TB.m_fABCD, Mtx, iVoxMin, iVoxMax, nItMin, nItMax, fTol_Itrt, nullptr);
	*************************************************************************************/

	//[20210524_13:56:44 ]: 已证实此方法效果OK**************************************
	CSPN_Cmn_3DPlane Pln3D_TA;
	double fNormCoeff = 1000;
	Pln3D_TA.FitConstuct_3DPlane_byIdx(Mtx, iVoxMin, iVoxMax, nullptr, &fNormCoeff);

#ifdef _DEBUG
	int iBrk = 1;
#endif // 
}

void CSPN_Cmn_3DPlane::CalcSetVox_atPane(CSPN_Cmn_3DMtx<BYTE>& Mtx, Cub3D_Int C3_ROI, BYTE vSet, float fTol)
{
	assert(fTol > 0.f);

#pragma omp parallel for
	for (int k = C3_ROI.MinZ(); k <= C3_ROI.MaxZ(); k++)
	{
		float fCZ_n_D = k * m_fABCD[2] + m_fABCD[3];
		for (int j = C3_ROI.MinY(); j <= C3_ROI.MaxY(); j++)
		{
			float fBY_n_CZ_n_D = j * m_fABCD[1] + fCZ_n_D;
			BYTE* pVox = Mtx.GetSliceRowBuf(k, j);
			for (int i = C3_ROI.MinX(); i <= C3_ROI.MaxX(); i++)
			{
				float fAX_n_fBY_n_CZ_n_D = i * m_fABCD[0] + fBY_n_CZ_n_D;
				if (fabs(fAX_n_fBY_n_CZ_n_D) < fTol)
				{
					pVox[i] = vSet;
				}
			}
		}
	}
}
