// SPN_Cmn_3DLine.h: interface for the CSPN_Cmn_3DLine<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_3DLine_H__INCLUDED_
#define SPN_Cmn_3DLine_H__INCLUDED_


#	pragma once



//----------------------------------------------------------------------------------------------------------
// 该类以有向线段表示一条3D空间中的直线。(详细注释以后添加)
//----------------------------------------------------------------------------------------------------------

#include "SPN_Cmn_3DPoint.h"

template<class TP>
class CSPN_Cmn_3DLine
{
public:
	CSPN_Cmn_3DLine();
	CSPN_Cmn_3DLine(const CSPN_Cmn_3DPoint<TP>& PBgn, const CSPN_Cmn_3DPoint<TP>& PEnd);

	//Attributes:
public:
	TP DX() const;
	TP DY() const;
	TP DZ() const;
	TP DXYZ(int i) const;

	CSPN_Cmn_3DPoint<TP>& PointBgn();
	CSPN_Cmn_3DPoint<TP>& PointEnd();

	void PointBgn(const CSPN_Cmn_3DPoint<TP>& PBgn);
	void PointEnd(const CSPN_Cmn_3DPoint<TP>& PEnd);

	double GetLength() const;											//线段长度
	double GetLengthSq() const;											//线段长度的平方（对比长度时可以加速）

	CSPN_Cmn_3DPoint<TP> GetUnitVect_Tangent() const;						//线段单位切向矢量
	CSPN_Cmn_3DPoint<TP> GetUnitVect_Tangent_Negative() const;				//线段单位切向矢量,负向

//Operations:
public:
	void SameDir_ByXYZ(CSPN_Cmn_3DLine<TP>& Line, const int i) const;
	void ComputePointOnLine_byAnyKnownCorrd(CSPN_Cmn_3DPoint<TP>& P, const int i_OK) const;	//已知线上一点的某一坐标分量，求其他两坐标分量;
	void Limit_BgnEnd_onLn__into_Range_Z(TP zMin, TP zMax);

	CSPN_Cmn_3DPoint<TP> MidPoint() const;												//求线段的中点
	CSPN_Cmn_3DPoint<TP> MidPoint(TP fDistFrBgn) const;								//指定由起点的距离占线段长的比例，以求线段的内点，

	CSPN_Cmn_3DPoint<TP> GetUnitVect_Normal(const CSPN_Cmn_3DPoint<TP>& P) const;			//过点P求直线的法向单位矢量
	CSPN_Cmn_3DPoint<TP> GetUnitVect_Normal_Negative(const CSPN_Cmn_3DPoint<TP>& P) const;//过点P求直线的法向单位矢量,负向

	CSPN_Cmn_3DPoint<TP> GetPerpendFoot(const CSPN_Cmn_3DPoint<TP>& P) const;

	//过P点向直线投影，求以m_PBgn为原点、X正轴指向m_PEnd、以该线段长度为单位的一维坐标系中垂足的坐标，同时计算出垂足的三维坐标
	float				GetPrjPos(const SSPN_Cmn_3DPoint<TP>& P, SSPN_Cmn_3DPoint<TP>& PpndFt) const;

	BOOL PtInLine(const SSPN_Cmn_3DPoint<TP>& Point, int& iPosFlag) const;			// 当返回值为TRUE时,iPosFlag有效: < 0 -- 在m_PBgn之前
																					//                                ==0 -- 在m_PBgn和m_PEnd之前
																					//								  > 0 -- 在m_PEnd之后
	CSPN_Cmn_3DPoint<TP> ToVector();													//计算矢量：(终点-起点)

	//void Serialize(CSPN_Cmn_Archive& Ar);

	//Implementations:
protected:
	CSPN_Cmn_3DPoint<TP> m_PBgn;	//有向线段起点
	CSPN_Cmn_3DPoint<TP> m_PEnd;	//有向线段终点
};



typedef CSPN_Cmn_3DLine<int>				Ln3D_Int;
typedef CSPN_Cmn_3DLine<unsigned int>	Ln3D_UInt;

typedef CSPN_Cmn_3DLine<short>			Ln3D_Sht;
typedef CSPN_Cmn_3DLine<unsigned short>	Ln3D_USht;

typedef CSPN_Cmn_3DLine<char>			Ln3D_Char;
typedef CSPN_Cmn_3DLine<unsigned char>	Ln3D_UChar;

typedef CSPN_Cmn_3DLine<float>			Ln3D_Flt;
typedef CSPN_Cmn_3DLine<double>			Ln3D_Dbl;

typedef CSPN_Cmn_3DLine<int>				Ln3D_Idx;



//-------------------------------------------------------------------------------------------------------------------
template<class TP>
CSPN_Cmn_3DLine<TP>::CSPN_Cmn_3DLine()
{
}
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
CSPN_Cmn_3DLine<TP>::CSPN_Cmn_3DLine(const CSPN_Cmn_3DPoint<TP>& PBgn, const CSPN_Cmn_3DPoint<TP>& PEnd)
{
	m_PBgn = PBgn;
	m_PEnd = PEnd;
}
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline void CSPN_Cmn_3DLine<TP>::ComputePointOnLine_byAnyKnownCorrd(CSPN_Cmn_3DPoint<TP>& P, const int i_OK) const
{
	int j = (i_OK + 1) % 3;
	int k = (i_OK + 2) % 3;

	TP fk = (P[i_OK] - m_PBgn[i_OK]) / DXYZ(i_OK);
	P[j] = m_PBgn[j] + fk * DXYZ(j);
	P[k] = m_PBgn[k] + fk * DXYZ(k);
}
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline TP CSPN_Cmn_3DLine<TP>::DX() const { return m_PEnd.x() - m_PBgn.x(); };
template<class TP> inline TP CSPN_Cmn_3DLine<TP>::DY() const { return m_PEnd.y() - m_PBgn.y(); };
template<class TP> inline TP CSPN_Cmn_3DLine<TP>::DZ() const { return m_PEnd.z() - m_PBgn.z(); };
template<class TP> inline TP CSPN_Cmn_3DLine<TP>::DXYZ(int i) const
{
	assert(i >= 0 && i < 3);
	return m_PEnd[i] - m_PBgn[i];
};
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline CSPN_Cmn_3DPoint<TP>& CSPN_Cmn_3DLine<TP>::PointBgn() { return m_PBgn; };
template<class TP> inline CSPN_Cmn_3DPoint<TP>& CSPN_Cmn_3DLine<TP>::PointEnd() { return m_PEnd; };
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline void	CSPN_Cmn_3DLine<TP>::PointBgn(const CSPN_Cmn_3DPoint<TP>& PBgn) { m_PBgn = PBgn; };
template<class TP> inline void	CSPN_Cmn_3DLine<TP>::PointEnd(const CSPN_Cmn_3DPoint<TP>& PEnd) { m_PEnd = PEnd; };
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline double CSPN_Cmn_3DLine<TP>::GetLength() const { return m_PBgn.GetDistTo(m_PEnd); };
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline double CSPN_Cmn_3DLine<TP>::GetLengthSq() const { return m_PBgn.GetDistTo_Sq(m_PEnd); };
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::GetUnitVect_Tangent() const
{
	CSPN_Cmn_3DPoint<TP> PVctTngnt;
	{
		TP fLength = GetLength();

		PVctTngnt[0] = DX() / fLength;
		PVctTngnt[1] = DY() / fLength;
		PVctTngnt[2] = DZ() / fLength;
	}

	return PVctTngnt;
};
//-------------------------------------------------------------------------------------------------------------------
template<class TP> inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::GetUnitVect_Tangent_Negative() const { return -GetUnitVect_Tangent(); };
template<class TP> inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::GetUnitVect_Normal_Negative(const CSPN_Cmn_3DPoint<TP>& P) const { return -GetUnitVect_Normal(P); };
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::GetUnitVect_Normal(const CSPN_Cmn_3DPoint<TP>& P) const
{
	CSPN_Cmn_3DPoint<TP> PFoot = GetPerpendFoot(P);
	CSPN_Cmn_3DLine<TP> LnFP(PFoot, P);
	return LnFP.GetUnitVect_Tangent();
};
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::MidPoint() const
{
	CSPN_Cmn_3DPoint<TP> PMid(m_PBgn);
	PMid += m_PEnd;
	PMid /= 2;
	return PMid;
};
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::MidPoint(TP fDistFrBgn) const
{
	CSPN_Cmn_3DPoint<TP> PBgn(m_PBgn);
	CSPN_Cmn_3DPoint<TP> PEnd(m_PEnd);
	PBgn *= (1.0 - fDistFrBgn);
	PEnd *= fDistFrBgn;
	PBgn += PEnd;
	return PBgn;
};
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::ToVector()
{
	CSPN_Cmn_3DPoint<TP> PVct(m_PEnd);
	PVct -= m_PBgn;
	return PVct;
};
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DPoint<TP> CSPN_Cmn_3DLine<TP>::GetPerpendFoot(const CSPN_Cmn_3DPoint<TP>& P) const
{
	const CSPN_Cmn_3DPoint<TP>& A = m_PBgn;
	const CSPN_Cmn_3DPoint<TP>& B = m_PEnd;

	//求过P点到线段AB的垂足：
	assert(A != B);

	//AB的切向矢量：(a,b,c)
	TP a = B.x() - A.x();
	TP b = B.y() - A.y();
	TP c = B.z() - A.z();

	//PA在AB上的投影 / AB的长度,按点乘计算:
	TP t = (a*(P.x() - A.x()) + b * (P.y() - A.y()) + c * (P.z() - A.z())) / (a*a + b * b + c * c);
	return CSPN_Cmn_3DPoint<TP>(A.x() + a * t, A.y() + b * t, A.z() + c * t);
};
//-------------------------------------------------------------------------------------------------------------------
//过P点向直线投影，求以m_PBgn为原点、X正轴指向m_PEnd、以该线段长度为单位的一维坐标系中垂足的坐标，同时计算出垂足的三维坐标
template<class TP>
inline float CSPN_Cmn_3DLine<TP>::GetPrjPos(const SSPN_Cmn_3DPoint<TP>& P, SSPN_Cmn_3DPoint<TP>& PpndFt) const
{
	if (FLT_EQ(GetLengthSq(), 0.f))
		return 0.f;

	PpndFt = GetPerpendFoot(P);

	float fPos = 0.f;

	float fVLengSqPFtFrBgn = PpndFt.GetDistTo_Sq(m_PBgn);
	float fVLengSqPFtFrEnd = PpndFt.GetDistTo_Sq(m_PEnd);
	float fVLengSqEndFrBgn = GetLengthSq();

	if (fVLengSqEndFrBgn > 0.f)
	{
		fPos = sqrt(fVLengSqPFtFrBgn / fVLengSqEndFrBgn);
		if (fVLengSqPFtFrEnd > fVLengSqEndFrBgn && fVLengSqPFtFrBgn < fVLengSqPFtFrEnd)
		{
			fPos = -fPos;
		}
	}

	return fPos;
};
//-------------------------------------------------------------------------------------------------------------------
// 当返回值为TRUE时,iPosFlag有效: < 0 -- 在m_PBgn之前
//                                ==0 -- 在m_PBgn和m_PEnd之前
//								  > 0 -- 在m_PEnd之后
template<class TP>
inline BOOL CSPN_Cmn_3DLine<TP>::PtInLine(const SSPN_Cmn_3DPoint<TP>& P, int& iPosFlag) const
{
	CSPN_Cmn_3DPoint<TP> PFoot = GetPerpendFoot(P);
	TP fDist = P.GetDistTo_Sq(PFoot);
	if (FLT_EQ(fDist, 0.0f))
	{
		TP fDist_BgnToPFoot = P.GetDistTo_Sq(m_PBgn);
		TP fDist_EndToPFoot = P.GetDistTo_Sq(m_PEnd);
		TP fLength = GetLengthSq();

		if (fDist_BgnToPFoot <= fLength && fDist_EndToPFoot <= fLength)
			iPosFlag = 0;
		else if (fDist_BgnToPFoot < fDist_EndToPFoot)
			iPosFlag = -1;
		else
			iPosFlag = 1;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
};
//-------------------------------------------------------------------------------------------------------------------
// line's two head points: oPoint[3] and (m_fLampX, m_fLampY, m_fLampZ).
// if there are two intersect point, return TRUE, else return FALSE
/*
BOOL CMTGR_View_Bev::LineSectToCuboid(TP oPoint[3], TP intersectPoint[6])
{
	TP lampX, lampY, lampZ;
	{
		TP a[3];
		CalculDirectionFromAngle(m_fCita, m_fFai, a);
		lampX = m_fDistance * a[0];
		lampY = m_fDistance * a[1];
		lampZ = m_fDistance * a[2];
	}

	// 计算射线的法向量
	int Normal[3];
	{
		Normal[0] = oPoint[0] - lampX;
		Normal[1] = oPoint[1] - lampY;
		Normal[2] = oPoint[2] - lampZ;
	}

	TP tmin = -1000000.0, tmax = 1000000.0;
	// 对三个轴进行判断
	for(int i = 0; i < 3; i++)
	{
		// 射线是否与某坐标轴平行？
		if(Normal[i] == 0)
		{
			// 起点在体数据长方体之外？
			if(oPoint[i] >= m_MaxPoint[i] || oPoint[i] <= m_MinPoint[i])
				return FALSE;// no intersect points
		}
		else
		{
			TP t1, t2;// 得到两交点参数：t1、t2，并把它们排序
			t1 = (m_MinPoint[i] - oPoint[i]) / Normal[i];
			t2 = (m_MaxPoint[i] - oPoint[i]) / Normal[i];
			if(t1 > t2)
			{
				TP tt = t1;
				t1 = t2;
				t2 = tt;
			}

			// 查看是否存在交点范围？
			if(t2 < tmax)
			{
				if(t2 < tmin)
					return FALSE;
				tmax = t2;
			}
			if(t1 > tmin)
			{
				if(t1 > tmax)
					return FALSE;
				tmin = t1;
			}
		}
	}

	// 计算两交点坐标值
	for(int i=0; i<3; i++)
	{
		intersectPoint[i]   = oPoint[i] + Normal[i]*tmin;
		intersectPoint[i+3] = oPoint[i] + Normal[i]*tmax;
	}
	return TRUE;
}
*/
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_3DLine<TP> operator-(const CSPN_Cmn_3DLine<TP>& Line)
{
	return CSPN_Cmn_3DLine<TP>(Line.PointEnd(), Line.PointBgn());
};

//-------------------------------------------------------------------------------------------------------------------
//template<class TP>
//inline void CSPN_Cmn_3DLine<TP>::Serialize(CSPN_Cmn_Archive& Ar)
//{
//	if (Ar.IsStoring())
//	{
//		UINT iVer = 1;
//		Ar << iVer;
//		m_PBgn.Serialize(Ar);
//		m_PEnd.Serialize(Ar);
//	}
//	else
//	{
//		UINT iVer = 0;
//		Ar >> iVer;
//		switch (iVer)
//		{
//		case 1:
//			m_PBgn.Serialize(Ar);
//			m_PEnd.Serialize(Ar);
//			break;
//		default:
//			::ShowMsg("文件版本无法识别!");
//			return;
//		}
//	}
//};
//-------------------------------------------------------------------------------------------------------------------
template<class TP>
inline void CSPN_Cmn_3DLine<TP>::SameDir_ByXYZ(CSPN_Cmn_3DLine<TP>& Line, const int i) const
{
	if ((DXYZ(i) > 0 && Line.DXYZ(i) < 0) || (DXYZ(i) < 0 && Line.DXYZ(i) > 0))
	{
		CSPN_Cmn_3DPoint<TP> PTmp(Line.PointBgn());
		Line.PointBgn(Line.PointEnd());
		Line.PointEnd(PTmp);
	}
};
//-------------------------------------------------------------------------------------------------------------------
// 如果当前线与Z向垂直, 且Z不在范围内, 则会发生平移;
// 否则, 会保持当前直线方向进行伸缩, 以确保任何一端不超过指定范围
template<class TP>
inline void CSPN_Cmn_3DLine<TP>::Limit_BgnEnd_onLn__into_Range_Z(TP zMin, TP zMax)
{
	if (zMin > zMax)
	{
		TP zTmp = zMin;
		zMin = zMax;
		zMax = zTmp;
	}

	if (FLT_EQ(m_PBgn[2], m_PEnd[2]))
	{
		::CutIntoRange(m_PBgn[2], zMin, zMax);
		m_PEnd[2] = m_PBgn[2];
	}
	else
	{
		CSPN_Cmn_3DPoint<TP>* arrpP3Old[2];
		{
			arrpP3Old[0] = &m_PBgn;
			arrpP3Old[1] = &m_PEnd;
		}
		CSPN_Cmn_3DPoint<TP> arrP3New[2];
		{
			arrP3New[0] = m_PBgn;
			arrP3New[1] = m_PEnd;
		}

		for (int i = 0; i < 2; i++)
		{
			CSPN_Cmn_3DPoint<TP>& P3Old_Cur = *arrpP3Old[i];
			CSPN_Cmn_3DPoint<TP>& P3Old_Far = *arrpP3Old[1 - i];

			CSPN_Cmn_3DPoint<TP>& P3New_Cur = arrP3New[i];
			TP& rzNew = P3New_Cur[2];

			if (rzNew >= zMin && rzNew <= zMax)
			{
				continue;
			}

			::CutIntoRange<TP>(rzNew, zMin, zMax);
			assert(!FLT_EQ(rzNew, P3Old_Cur[2]));

			assert(!FLT_EQ(P3Old_Cur[2], P3Old_Far[2]));
			double fK_Chg = (rzNew - P3Old_Far[2]) / (P3Old_Cur[2] - P3Old_Far[2]);

			P3New_Cur[0] = fK_Chg * (P3Old_Cur[0] - P3Old_Far[0]) + P3Old_Far[0];
			P3New_Cur[1] = fK_Chg * (P3Old_Cur[1] - P3Old_Far[1]) + P3Old_Far[1];
		}

		m_PBgn = arrP3New[0];
		m_PEnd = arrP3New[1];
	}
};
//-------------------------------------------------------------------------------------------------------------------

#endif //  // !defined(SPN_Cmn_3DLine_H__INCLUDED_
