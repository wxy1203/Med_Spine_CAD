// SPN_Cmn_3DCuboid.h : main header file for the SPN_Cmn_3DCuboid application
//

#ifndef SPN_Cmn_3DCuboid_H__INCLUDED_
#define SPN_Cmn_3DCuboid_H__INCLUDED_


#	pragma once


#include "SPN_Cmn_3DPoint.h"
/////////////////////////////////////////////////////////////////////////////

template<class TP>
struct SSPN_Cmn_3DCuboid
{
public:
	SSPN_Cmn_3DPoint<TP> m_P3D_Min;
	SSPN_Cmn_3DPoint<TP> m_P3D_Max;

public:
	////���캯�����������
	//SSPN_Cmn_3DCuboid()
	//{
	//	Zero();
	//};

	//SSPN_Cmn_3DCuboid(const SSPN_Cmn_3DPoint<TP>& P3Min, const SSPN_Cmn_3DPoint<TP>& P3Max)
	//{
	//	this->m_P3D_Min = P3Min;
	//	this->m_P3D_Max = P3Max;
	//};
	//SSPN_Cmn_3DCuboid(const SSPN_Cmn_3DCuboid<TP>& Cub)
	//{
	//	*this = Cub;
	//};
	//virtual ~SSPN_Cmn_3DCuboid(){};

	inline const SSPN_Cmn_3DCuboid<TP>& operator = (const SSPN_Cmn_3DCuboid<TP>& Cub);

	inline const SSPN_Cmn_3DCuboid<TP>& operator = (const TP v)
	{
		this->m_P3D_Min.Construct(v, v, v);
		this->m_P3D_Max.Construct(v, v, v);
	};

	inline void operator += (SSPN_Cmn_3DPoint<TP> P3)
	{
		this->m_P3D_Min += P3;
		this->m_P3D_Max += P3;
	};

	inline void operator -= (SSPN_Cmn_3DPoint<TP> P3)
	{
		this->m_P3D_Min -= P3;
		this->m_P3D_Max -= P3;
	};

	inline void operator *= (double fK)
	{
		this->m_P3D_Min *= fK;
		this->m_P3D_Max *= fK;
	};

	inline CSPN_Cmn_2DRect<TP> Get_Rct2D_XY() const
	{
		CSPN_Cmn_2DRect<TP> Rct2D;

		Rct2D.xMIN = this->m_P3D_Min[0];
		Rct2D.yMIN = this->m_P3D_Min[1];

		Rct2D.xMAX = this->m_P3D_Max[0];
		Rct2D.yMAX = this->m_P3D_Max[1];

		Rct2D.Normalize();

		return Rct2D;
	};

	inline CRectInt Get_CRect_XY() const
	{
		CRectInt Rct;

		Rct.left = this->m_P3D_Min[0];
		Rct.top = this->m_P3D_Min[1];

		Rct.right = this->m_P3D_Max[0];
		Rct.bottom = this->m_P3D_Max[1];

		Rct.NormalizeRect();

		return Rct;
	};

	SPnt3D_Int GetCount_XYZ_Pnt_INT()
	{
		SPnt3D_Int sP3;
		sP3.Construct(this->m_P3D_Max[0] - this->m_P3D_Min[0] + 1,
					  this->m_P3D_Max[1] - this->m_P3D_Min[1] + 1,
					  this->m_P3D_Max[2] - this->m_P3D_Min[2] + 1);

		return sP3;
	};

	SPnt3D_Int GetCount_XYZ_Spc_INT()
	{
		SPnt3D_Int sP3;
		sP3.Construct(this->m_P3D_Max[0] - this->m_P3D_Min[0],
					  this->m_P3D_Max[1] - this->m_P3D_Min[1],
					  this->m_P3D_Max[2] - this->m_P3D_Min[2]);
		return sP3;
	};

	//�������㹹��Cub
	inline void Construct(SSPN_Cmn_3DPoint<TP> P1, SSPN_Cmn_3DPoint<TP> P2);
public:
	static inline int	GetCount_SubDim() { return 6; };
	TP&		operator[](int i)
	{
		switch (i)
		{
		case 0: return m_P3D_Min[0]; break;
		case 1: return m_P3D_Min[1]; break;
		case 2: return m_P3D_Min[2]; break;

		case 3: return m_P3D_Max[0]; break;
		case 4: return m_P3D_Max[1]; break;
		case 5: return m_P3D_Max[2]; break;
		default:
			assert(false);
			break;
		}
	};
	const TP	operator[](int i) const
	{
		switch (i)
		{
		case 0: return m_P3D_Min[0]; break;
		case 1: return m_P3D_Min[1]; break;
		case 2: return m_P3D_Min[2]; break;

		case 3: return m_P3D_Max[0]; break;
		case 4: return m_P3D_Max[1]; break;
		case 5: return m_P3D_Max[2]; break;
		default:
			assert(false);
			break;
		}
	};

	inline TP MinX()const { return m_P3D_Min[0]; };
	inline TP MinY()const { return m_P3D_Min[1]; };
	inline TP MinZ()const { return m_P3D_Min[2]; };

	inline TP MaxX()const { return m_P3D_Max[0]; };
	inline TP MaxY()const { return m_P3D_Max[1]; };
	inline TP MaxZ()const { return m_P3D_Max[2]; };

	inline TP& MinX() { return m_P3D_Min[0]; };
	inline TP& MinY() { return m_P3D_Min[1]; };
	inline TP& MinZ() { return m_P3D_Min[2]; };

	inline TP& MaxX() { return m_P3D_Max[0]; };
	inline TP& MaxY() { return m_P3D_Max[1]; };
	inline TP& MaxZ() { return m_P3D_Max[2]; };

	inline SSPN_Cmn_3DCuboid<int> To_Int()
	{
		SSPN_Cmn_3DCuboid<int> CubInt;
		CubInt.Set3DPointMin(m_P3D_Min.ToInt());
		CubInt.Set3DPointMax(m_P3D_Max.ToInt());
		return CubInt;
	};

public:
	//���������òο����ֵ
	inline const SSPN_Cmn_3DPoint<TP>& Get3DPointMin() const;
	inline const SSPN_Cmn_3DPoint<TP>& Get3DPointMax() const;

	inline SSPN_Cmn_3DPoint<TP>& GetP3D_Min() { return m_P3D_Min; };
	inline SSPN_Cmn_3DPoint<TP>& GetP3D_Max() { return m_P3D_Max; };

	inline void Set3DPointMin(const SSPN_Cmn_3DPoint<TP> P3DMin) { m_P3D_Min = P3DMin; };
	inline void Set3DPointMax(const SSPN_Cmn_3DPoint<TP> P3DMax) { m_P3D_Max = P3DMax; };

	inline bool IsContainPnt(TP X, TP Y, TP Z)//[12_24 11:47:35 ]:
	{
		return
			X >= m_P3D_Min[0] && X <= m_P3D_Max[0] &&
			Y >= m_P3D_Min[1] && Y <= m_P3D_Max[1] &&
			Z >= m_P3D_Min[2] && Z <= m_P3D_Max[2];
	};
	inline bool IsContainPnt(TP arrTP3[3])//[20210416_14:11:52 ]:
	{
		return IsContainPnt(arrTP3[0], arrTP3[1], arrTP3[2]);
	};

	inline void CutIntoCub(CSPN_Cmn_3DPoint<TP>& P3D) const
	{
		CutIntoRange<TP>(P3D[0], m_P3D_Min[0], m_P3D_Max[0]);
		CutIntoRange<TP>(P3D[1], m_P3D_Min[1], m_P3D_Max[1]);
		CutIntoRange<TP>(P3D[2], m_P3D_Min[2], m_P3D_Max[2]);
	};

	inline void CutIntoCub(SSPN_Cmn_3DCuboid<TP>& C3D) const
	{
		assert(this->IsNormalized());
		C3D.Normalize();

		CutIntoRange<TP>(C3D.m_P3D_Min[0], m_P3D_Min[0], m_P3D_Max[0]);
		CutIntoRange<TP>(C3D.m_P3D_Min[1], m_P3D_Max[1], m_P3D_Min[1]);
		CutIntoRange<TP>(C3D.m_P3D_Min[2], m_P3D_Min[2], m_P3D_Max[2]);

		CutIntoRange<TP>(C3D.m_P3D_Max[0], m_P3D_Min[0], m_P3D_Max[0]);
		CutIntoRange<TP>(C3D.m_P3D_Max[1], m_P3D_Min[1], m_P3D_Max[1]);
		CutIntoRange<TP>(C3D.m_P3D_Max[2], m_P3D_Min[2], m_P3D_Max[2]);
	};

	inline bool IsContainPnt_Int(const Pnt3D_Int P3D)//[12_24 11:47:35 ]:
	{
		return IsContainPnt(P3D[0], P3D[1], P3D[2]);
	};
	inline bool IsContainPnt_Sht(const Pnt3D_Sht P3D)//[12_24 11:47:35 ]:
	{
		return IsContainPnt(P3D[0], P3D[1], P3D[2]);
	};
	inline bool IsContainPnt_Flt(const Pnt3D_Flt P3D)//[12_24 11:47:35 ]:
	{
		return IsContainPnt(P3D[0], P3D[1], P3D[2]);
	};
	inline bool IsContainPnt_Dbl(const Pnt3D_Dbl P3D)//[12_24 11:47:35 ]:
	{
		return IsContainPnt(P3D[0], P3D[1], P3D[2]);
	};
	inline bool IsContainPnt_UInt(const Pnt3D_UInt P3D)//[12_24 11:47:35 ]:
	{
		return IsContainPnt(P3D[0], P3D[1], P3D[2]);
	};

	//���򻯣�Ҫ���������Ϊ��ȫ��С��ϵ
	inline void NormalizeCub();

	inline void Inflate(int nAdd_X, int nAdd_Y, int nAdd_Z)
	{
		Normalize();

		m_P3D_Min[0] -= nAdd_X;
		m_P3D_Min[1] -= nAdd_Y;
		m_P3D_Min[2] -= nAdd_Z;

		m_P3D_Max[0] += nAdd_X;
		m_P3D_Max[1] += nAdd_Y;
		m_P3D_Max[2] += nAdd_Z;
	};

	inline void Deflate(int nAdd_X, int nAdd_Y, int nAdd_Z)
	{
		Inflate(-nAdd_X, -nAdd_Y, -nAdd_Z);
	};

	inline void Inflate(SSPN_Cmn_3DPoint<int> P3D)
	{
		Inflate(P3D[0], P3D[1], P3D[2]);
	};
	inline void Deflate(SSPN_Cmn_3DPoint<int> P3D)
	{
		Deflate(P3D[0], P3D[1], P3D[2]);
	};

	inline void Inflate(int nAdd_XNeg, int nAdd_YNeg, int nAdd_ZNeg, int nAdd_XPos, int nAdd_YPos, int nAdd_ZPos)
	{
		Normalize();

		m_P3D_Min[0] -= nAdd_XNeg;
		m_P3D_Min[1] -= nAdd_YNeg;
		m_P3D_Min[2] -= nAdd_ZNeg;

		m_P3D_Max[0] += nAdd_XPos;
		m_P3D_Max[1] += nAdd_YPos;
		m_P3D_Max[2] += nAdd_ZPos;
	};

	inline void Deflate(int nAdd_XNeg, int nAdd_YNeg, int nAdd_ZNeg, int nAdd_XPos, int nAdd_YPos, int nAdd_ZPos)
	{
		Inflate(-nAdd_XNeg, -nAdd_YNeg, -nAdd_ZNeg, -nAdd_XPos, -nAdd_YPos, -nAdd_ZPos);
	};

	inline void Inflate(SSPN_Cmn_3DPoint<int> P3DNeg, SSPN_Cmn_3DPoint<int> P3DPos)
	{
		Inflate(P3DNeg[0], P3DNeg[1], P3DNeg[2], P3DPos[0], P3DPos[1], P3DPos[2]);
	};

	inline void Deflate(SSPN_Cmn_3DPoint<int> P3DNeg, SSPN_Cmn_3DPoint<int> P3DPos)
	{
		Deflate(P3DNeg[0], P3DNeg[1], P3DNeg[2], P3DPos[0], P3DPos[1], P3DPos[2]);
	};

	////����Cub���߳��ȡ����ĵ�
	//TP GetLengthX() const;    
	//TP GetLengthY() const;
	//TP GetLengthZ() const;
	//SSPN_Cmn_3DPoint<TP> Get3DPointCtr() const;

	//���ظ������
	//TP GetAreaXY() const;
	//TP GetAreaYZ() const;
	//TP GetAreaZX() const;

	//����Cub�����
	//TP GetVolume() const;	

	//�ж�ĳһ���Ƿ���Cub��
	inline BOOL IsInCub(const SSPN_Cmn_3DPoint<TP>& P1) const;

	//Cub����
	void UnionCub(const SSPN_Cmn_3DCuboid<TP>& Cub);		//�ϲ�����Cub
	BOOL IntersectCub(const SSPN_Cmn_3DCuboid<TP> & Cub);  //������Cub����

	//void Serialize(CSPN_Cmn_Archive& Ar);
	//};
	//
	//
	//template<typename TP>
	//struct SSPN_Cmn_3DCuboid
	//{
	inline void Zero()
	{
		m_P3D_Min.Zero();
		m_P3D_Min.Zero();
	};

	//SSPN_Cmn_3DCuboid(const SSPN_Cmn_3DCuboid<TP>& Cub3D)
	//{
	//	*this = Cub3D;
	//};

	//const SSPN_Cmn_3DCuboid<TP>& operator=(const SSPN_Cmn_3DCuboid<TP>& Cub3D)
	//{
	//	m_P3D_Min = Cub3D.m_P3D_Min;
	//	m_P3D_Max = Cub3D.m_P3D_Max;
	//	Normalize();
	//	return *this;
	//};

	inline bool operator==(const SSPN_Cmn_3DCuboid<TP>& Cub3D) const
	{
		return (m_P3D_Min == Cub3D.m_P3D_Min &&
				m_P3D_Max == Cub3D.m_P3D_Max);
	};

	//SSPN_Cmn_3DCuboid(const TP* pTp3D_Bgn, const TP* pTp3D_End)
	//{
	//	m_P3D_Min.Construct(pTp3D_Bgn);
	//	m_P3D_Max.Construct(pTp3D_End);

	//	Normalize();
	//};

	inline void Construct(const TP** pTp3D)
	{
		m_P3D_Min[0] = pTp3D[0][0];
		m_P3D_Min[1] = pTp3D[0][1];
		m_P3D_Min[2] = pTp3D[0][2];

		m_P3D_Max[0] = pTp3D[1][0];
		m_P3D_Max[1] = pTp3D[2][1];
		m_P3D_Max[2] = pTp3D[2][2];
	};


	inline bool IsFullZero() const
	{
		return
			m_P3D_Min.IsFullZero() &&
			m_P3D_Max.IsFullZero();
	};

	inline bool IsZeroVolumeAndArea() const
	{
		return
			m_P3D_Min == m_P3D_Max;
	};

	inline double GetMaxCornerDist() const
	{
		double fMaxCrnrDst = m_P3D_Min.GetDistTo(m_P3D_Max);
		return fMaxCrnrDst;
	};

	//*******************************************************************

	inline void GetLength3D_CubEdge(double* pfLeng3D) const
	{
		pfLeng3D[0] = GetLength_CubEdge_X();
		pfLeng3D[1] = GetLength_CubEdge_Y();
		pfLeng3D[2] = GetLength_CubEdge_Z();
	};

	inline SSPN_Cmn_3DPoint<TP> GetLength3D_Pnt() const
	{
		SSPN_Cmn_3DPoint<TP> P3DLen;
		P3DLen[0] = GetLength_CubEdge_X();
		P3DLen[1] = GetLength_CubEdge_Y();
		P3DLen[2] = GetLength_CubEdge_Z();
		return P3DLen;
	};

	inline double GetLength_CubEdge_X() const
	{
		double fLeng = qAbs<double>(m_P3D_Max[0] - m_P3D_Min[0]);
		return fLeng;
	};
	inline double GetLength_CubEdge_Y() const
	{
		double fLeng = qAbs<double>(m_P3D_Max[1] - m_P3D_Min[1]);
		return fLeng;
	};
	inline double GetLength_CubEdge_Z() const
	{
		double fLeng = qAbs<double>(m_P3D_Max[2] - m_P3D_Min[2]);
		return fLeng;
	};

	inline double GetLength_CubEdge_Min() const
	{
		double fLx = GetLength_CubEdge_X();
		double fLy = GetLength_CubEdge_Y();
		double fLz = GetLength_CubEdge_Z();

		double fLmin = std::min<float>(fLx, fLy);
		fLmin = std::min<float>(fLmin, fLz);

		return fLmin;
	};
	inline double GetLength_CubEdge_Max() const
	{
		double fLx = GetLength_CubEdge_X();
		double fLy = GetLength_CubEdge_Y();
		double fLz = GetLength_CubEdge_Z();

		double fLmax = std::max<double>(fLx, fLy);
		fLmax = std::max<double>(fLmax, fLz);

		return fLmax;
	};

	//*******************************************************************
	template<typename TPInt = int>
	inline void GetSize3D_NodeCount(TPInt* pnSize3D) const
	{
		pnSize3D[0] = GetSize_NodeCount_X();
		pnSize3D[1] = GetSize_NodeCount_Y();
		pnSize3D[2] = GetSize_NodeCount_Z();
	};

	template<typename TPInt = int>
	inline SSPN_Cmn_3DPoint<TPInt> GetSize3D_NodeCount_Pnt() const
	{
		SSPN_Cmn_3DPoint<TPInt> P3DSize;
		P3DSize[0] = GetSize_NodeCount_X();
		P3DSize[1] = GetSize_NodeCount_Y();
		P3DSize[2] = GetSize_NodeCount_Z();
		return P3DSize;
	};

	template<typename TPInt = int> inline TPInt GetSize_NodeCount_X() const { TPInt nSize = qAbs<TPInt>(m_P3D_Max[0] - m_P3D_Min[0]) + 1; 	return nSize; };
	template<typename TPInt = int> inline TPInt GetSize_NodeCount_Y() const { TPInt nSize = qAbs<TPInt>(m_P3D_Max[1] - m_P3D_Min[1]) + 1; 	return nSize; };
	template<typename TPInt = int> inline TPInt GetSize_NodeCount_Z() const { TPInt nSize = qAbs<TPInt>(m_P3D_Max[2] - m_P3D_Min[2]) + 1; 	return nSize; };

	template<typename TPInt = int> inline TPInt GetSize_NodeCount_Min() const
	{
		TPInt nSzX = GetSize_NodeCount_X();
		TPInt nSzY = GetSize_NodeCount_Y();
		TPInt nSzZ = GetSize_NodeCount_Z();
		TPInt nSzMin = qMin<TPInt>(nSzX, nSzY);
		nSzMin = qMin<TPInt>(nSzMin, nSzZ);
		return nSzMin;
	};
	template<typename TPInt = int> inline TPInt GetSize_NodeCount_Max() const
	{
		TPInt nSzX = GetSize_NodeCount_X();
		TPInt nSzY = GetSize_NodeCount_Y();
		TPInt nSzZ = GetSize_NodeCount_Z();
		TPInt nSzMax = qMax<TPInt>(nSzX, nSzY);
		nSzMax = qMax<TPInt>(nSzMax, nSzZ);
		return nSzMax;
	};

	//*******************************************************************

	inline bool IsNormalized() const
	{
		return
			m_P3D_Min[0] <= m_P3D_Max[0] &&
			m_P3D_Min[1] <= m_P3D_Max[1] &&
			m_P3D_Min[2] <= m_P3D_Max[2];
	};
	inline void Normalize()
	{
		Normalize_X();
		Normalize_Y();
		Normalize_Z();
	};
	inline void Normalize_X()
	{
		if (m_P3D_Min[0] > m_P3D_Max[0])
		{
			TP vTmp = m_P3D_Min[0];
			m_P3D_Min[0] = m_P3D_Max[0];
			m_P3D_Max[0] = vTmp;
		}
	};
	inline void Normalize_Y()
	{
		if (m_P3D_Min[1] > m_P3D_Max[1])
		{
			TP vTmp = m_P3D_Min[1];
			m_P3D_Min[1] = m_P3D_Max[1];
			m_P3D_Max[1] = vTmp;
		}
	};
	inline void Normalize_Z()
	{
		if (m_P3D_Min[2] > m_P3D_Max[2])
		{
			TP vTmp = m_P3D_Min[2];
			m_P3D_Min[2] = m_P3D_Max[2];
			m_P3D_Max[2] = vTmp;
		}
	};

	//inline void GetCntr(TP* pfCntr3D)
	//{
	//	pfCntr3D[0] = GetCntr_X();
	//	pfCntr3D[1] = GetCntr_Y();
	//	pfCntr3D[2] = GetCntr_Z();
	//};
	inline SSPN_Cmn_3DPoint<TP> GetCenterPnt() const
	{
		SSPN_Cmn_3DPoint<TP> PCntr;
		PCntr[0] = GetCntr_X();
		PCntr[1] = GetCntr_Y();
		PCntr[2] = GetCntr_Z();
		return PCntr;
	};
	inline TP GetCntr_X() const
	{
		return (m_P3D_Min[0] + m_P3D_Max[0]) / 2;
	};
	inline TP GetCntr_Y() const
	{
		return (m_P3D_Min[1] + m_P3D_Max[1]) / 2;
	};
	inline TP GetCntr_Z() const
	{
		return (m_P3D_Min[2] + m_P3D_Max[2]) / 2;
	};

	inline SSPN_Cmn_3DPoint<double> GetCenterPnt_Dbl() const
	{
		SSPN_Cmn_3DPoint<double> PCntr;
		PCntr[0] = GetCntr_X_Dbl();
		PCntr[1] = GetCntr_Y_Dbl();
		PCntr[2] = GetCntr_Z_Dbl();
		return PCntr;
	};
	inline double GetCntr_X_Dbl() const
	{
		return (m_P3D_Min[0] + m_P3D_Max[0]) * 0.5;
	};
	inline double GetCntr_Y_Dbl() const
	{
		return (m_P3D_Min[1] + m_P3D_Max[1]) * 0.5;
	};
	inline double GetCntr_Z_Dbl() const
	{
		return (m_P3D_Min[2] + m_P3D_Max[2]) * 0.5;
	};

	inline TP GetVolume_XYZ() const
	{
		TP vfVol =
			GetLength_CubEdge_X() * GetLength_CubEdge_Y() * GetLength_CubEdge_Z();
		return vfVol;
	};
	inline TP GetSideArea_XY() const
	{
		TP vAreaXY = GetLength_CubEdge_X() * GetLength_CubEdge_Y();
		return vAreaXY;
	};
	inline TP GetSideArea_YZ() const
	{
		TP vAreaXY = GetLength_CubEdge_Y() * GetLength_CubEdge_Z();
		return vAreaXY;
	};
	inline TP GetSideArea_ZX() const
	{
		TP vAreaXY = GetLength_CubEdge_Z() * GetLength_CubEdge_X();
		return vAreaXY;
	};

	inline double GetVolume_XYZ_Dbl() const
	{
		double fVol =
			GetLength_CubEdge_X() * GetLength_CubEdge_Y() * GetLength_CubEdge_Z();
		return fVol;
	};
	inline double GetSideArea_XY_Dbl() const
	{
		double fAreaXY = GetLength_CubEdge_X() * GetLength_CubEdge_Y();
		return fAreaXY;
	};
	inline double GetSideArea_YZ_Dbl() const
	{
		double fAreaXY = GetLength_CubEdge_Y() * GetLength_CubEdge_Z();
		return fAreaXY;
	};
	inline double GetSideArea_ZX_Dbl() const
	{
		double fAreaXY = GetLength_CubEdge_Z() * GetLength_CubEdge_X();
		return fAreaXY;
	};

	//*************************************************************************************

	inline bool IsConnect_X(const SSPN_Cmn_3DCuboid<TP>& Cub_j, const TP vTol = 1) const
	{
		SSPN_Cmn_3DCuboid<TP> Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;
		Cub_A.Normalize_X();
		Cub_B.Normalize_X();

		if ((Cub_B.m_P3D_Min[0] - Cub_A.m_P3D_Max[0] > vTol) ||
			(Cub_A.m_P3D_Min[0] - Cub_B.m_P3D_Max[0] > vTol))
		{
			return false;
		}
		else
		{
			return true;
		}
	};

	inline bool IsConnect_Y(const SSPN_Cmn_3DCuboid<TP>& Cub_j, const TP vTol = 1) const
	{
		SSPN_Cmn_3DCuboid<TP> Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;
		Cub_A.Normalize_Y();
		Cub_B.Normalize_Y();

		if ((Cub_B.m_P3D_Min[1] - Cub_A.m_P3D_Max[1] > vTol) ||
			(Cub_A.m_P3D_Min[1] - Cub_B.m_P3D_Max[1] > vTol))
		{
			return false;
		}
		else
		{
			return true;
		}
	};

	inline bool IsConnect_Z(const SSPN_Cmn_3DCuboid<TP>& Cub_j, const TP vTol = 1) const
	{
		SSPN_Cmn_3DCuboid<TP> Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;
		Cub_A.Normalize_Z();
		Cub_B.Normalize_Z();

		if ((Cub_B.m_P3D_Min[2] - Cub_A.m_P3D_Max[2] > vTol) ||
			(Cub_A.m_P3D_Min[2] - Cub_B.m_P3D_Max[2] > vTol))
		{
			return false;
		}
		else
		{
			return true;
		}
	};

	//*************************************************************************************

	inline void UnionEq(const SSPN_Cmn_3DCuboid<TP>& Cub_j)
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;

		Cub_A.Normalize();
		Cub_B.Normalize();

		UnionEq_X(Cub_j);
		UnionEq_Y(Cub_j);
		UnionEq_Z(Cub_j);
	};

	inline void UnionEq_X(const SSPN_Cmn_3DCuboid<TP>& Cub_j)
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;

		Cub_A.Normalize_X();
		Cub_B.Normalize_X();

		Cub_A.m_P3D_Min[0] = std::min<TP>(Cub_A.m_P3D_Min[0], Cub_B.m_P3D_Min[0]);
		Cub_A.m_P3D_Max[0] = std::max<TP>(Cub_A.m_P3D_Max[0], Cub_B.m_P3D_Max[0]);
	};

	inline void UnionEq_Y(const SSPN_Cmn_3DCuboid<TP>& Cub_j)
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;

		Cub_A.Normalize_Y();
		Cub_B.Normalize_Y();

		Cub_A.m_P3D_Min[1] = std::min<TP>(Cub_A.m_P3D_Min[1], Cub_B.m_P3D_Min[1]);
		Cub_A.m_P3D_Max[1] = std::max<TP>(Cub_A.m_P3D_Max[1], Cub_B.m_P3D_Max[1]);
	};

	inline void UnionEq_Z(const SSPN_Cmn_3DCuboid<TP>& Cub_j)
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;

		Cub_A.Normalize_Z();
		Cub_B.Normalize_Z();

		Cub_A.m_P3D_Min[2] = std::min<TP>(Cub_A.m_P3D_Min[2], Cub_B.m_P3D_Min[2]);
		Cub_A.m_P3D_Max[2] = std::max<TP>(Cub_A.m_P3D_Max[2], Cub_B.m_P3D_Max[2]);
	};

	inline void ExpandInclude_Pnt(SSPN_Cmn_3DPoint<TP> P3D)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.ExpandInclude_X(P3D[0]);
		Cub_A.ExpandInclude_Y(P3D[1]);
		Cub_A.ExpandInclude_Z(P3D[2]);
	};

	inline void ExpandInclude_Pnt_Flt(Pnt3D_Flt P3D)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.ExpandInclude_X(P3D[0]);
		Cub_A.ExpandInclude_Y(P3D[1]);
		Cub_A.ExpandInclude_Z(P3D[2]);
	};

	inline void ExpandInclude_Pnt_Flt(Pnt3D_Dbl P3D)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.ExpandInclude_X(P3D[0]);
		Cub_A.ExpandInclude_Y(P3D[1]);
		Cub_A.ExpandInclude_Z(P3D[2]);
	};

	inline void ExpandInclude_X(TP fPos)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.Normalize();
		Cub_A.m_P3D_Min[0] = std::min<TP>(Cub_A.m_P3D_Min[0], fPos);
		Cub_A.m_P3D_Max[0] = std::max<TP>(Cub_A.m_P3D_Max[0], fPos);
	};
	inline void ExpandInclude_Y(TP fPos)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.Normalize();
		Cub_A.m_P3D_Min[1] = std::min<TP>(Cub_A.m_P3D_Min[1], fPos);
		Cub_A.m_P3D_Max[1] = std::max<TP>(Cub_A.m_P3D_Max[1], fPos);
	};
	inline void ExpandInclude_Z(TP fPos)//[11_14 20:48:48 ]: 
	{
		SSPN_Cmn_3DCuboid<TP>& Cub_A = *this;
		Cub_A.Normalize();
		Cub_A.m_P3D_Min[2] = std::min<TP>(Cub_A.m_P3D_Min[2], fPos);
		Cub_A.m_P3D_Max[2] = std::max<TP>(Cub_A.m_P3D_Max[2], fPos);
	};

	//*************************************************************************************


	inline void GetDist_to_Cub(double* pfDst3D, const SSPN_Cmn_3DCuboid<TP>& Cub_j) const//ֻҪ��һ���ص��������Ϊ����������ʱΪ0; �뿪ʱΪ��ֵ
	{
		SSPN_Cmn_3DCuboid<TP> Cub_A = *this;
		SSPN_Cmn_3DCuboid<TP> Cub_B = Cub_j;

		SSPN_Cmn_3DPoint<double> PCntr_A = Cub_A.GetCenterPnt_Dbl();
		SSPN_Cmn_3DPoint<double> PCntr_B = Cub_B.GetCenterPnt_Dbl();

		double pfCntrDist3D[3];
		pfCntrDist3D[0] = qAbs<double>(PCntr_A[0] - PCntr_B[0]);
		pfCntrDist3D[1] = qAbs<double>(PCntr_A[1] - PCntr_B[1]);
		pfCntrDist3D[2] = qAbs<double>(PCntr_A[2] - PCntr_B[2]);

		double pfEdgeLeng3D_A[3];
		double pfEdgeLeng3D_B[3];
		Cub_A.GetLength3D_CubEdge(pfEdgeLeng3D_A);
		Cub_B.GetLength3D_CubEdge(pfEdgeLeng3D_B);

		double pfLengSum_Semi3D[3];
		pfLengSum_Semi3D[0] = 0.5 * (qAbs<double>(pfEdgeLeng3D_A[0]) + qAbs<double>(pfEdgeLeng3D_B[0]));
		pfLengSum_Semi3D[1] = 0.5 * (qAbs<double>(pfEdgeLeng3D_A[1]) + qAbs<double>(pfEdgeLeng3D_B[1]));
		pfLengSum_Semi3D[2] = 0.5 * (qAbs<double>(pfEdgeLeng3D_A[2]) + qAbs<double>(pfEdgeLeng3D_B[2]));

		pfDst3D[0] = /*qAbs<double>*/(pfCntrDist3D[0]) - /*qAbs<double>*/(pfLengSum_Semi3D[0]);
		pfDst3D[1] = /*qAbs<double>*/(pfCntrDist3D[1]) - /*qAbs<double>*/(pfLengSum_Semi3D[1]);
		pfDst3D[2] = /*qAbs<double>*/(pfCntrDist3D[2]) - /*qAbs<double>*/(pfLengSum_Semi3D[2]);
	};

	//���ص�ʱ���ص�ֵΪ���������ص�ֵΪ0��
	inline void		GetOverlapLeng3D_to_Cub(double* pf3D_OvLp, const SSPN_Cmn_3DCuboid<TP>& Cub_j) const
	{
		double pfDst3D[3];
		GetDist_to_Cub(pfDst3D, Cub_j);

		pf3D_OvLp[0] = (pfDst3D[0] < 0) ? qAbs<double>(pfDst3D[0]) : 0;
		pf3D_OvLp[1] = (pfDst3D[1] < 0) ? qAbs<double>(pfDst3D[1]) : 0;
		pf3D_OvLp[2] = (pfDst3D[2] < 0) ? qAbs<double>(pfDst3D[0]) : 0;
	};
	inline double	GetCoverRate_XY(const SSPN_Cmn_3DCuboid<TP>& Cub_j) const
	{
		double pf3D_OvLp[3];
		GetOverlapLeng3D_to_Cub(pf3D_OvLp, Cub_j);

		float fAreaXY = GetSideArea_XY();
		if (fAreaXY > 0)
		{
			float fCovRateXY = pf3D_OvLp[0] * pf3D_OvLp[1] / fAreaXY;
			return fCovRateXY;
		}
		else
		{
			return 1;
		}
	};
	inline double	GetCoverRate_YZ(const SSPN_Cmn_3DCuboid<TP>& Cub_j) const
	{
		double pf3D_OvLp[3];
		GetOverlapLeng3D_to_Cub(pf3D_OvLp, Cub_j);

		float fAreaYZ = GetSideArea_YZ();
		if (fAreaYZ > 0)
		{
			float fCovRateYZ = pf3D_OvLp[1] * pf3D_OvLp[2] / fAreaYZ;
			return fCovRateYZ;
		}
		else
		{
			return 1;
		}
	};
	inline double	GetCoverRate_ZX(const SSPN_Cmn_3DCuboid<TP>& Cub_j) const
	{
		double pf3D_OvLp[3];
		GetOverlapLeng3D_to_Cub(pf3D_OvLp, Cub_j);

		float fAreaZX = GetSideArea_ZX();
		if (fAreaZX > 0)
		{
			float fCovRateZX = pf3D_OvLp[2] * pf3D_OvLp[0] / fAreaZX;
			return fCovRateZX;
		}
		else
		{
			return 1;
		}
	};

	static double GetCoverRate_AnyMax_XY(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_XY(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_XY(CubA);
		return std::max<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
	static double GetCoverRate_AnyMin_XY(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_XY(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_XY(CubA);
		return std::min<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
	static double GetCoverRate_AnyMax_YZ(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_YZ(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_YZ(CubA);
		return std::max<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
	static double GetCoverRate_AnyMin_YZ(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_YZ(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_YZ(CubA);
		return std::min<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
	static double GetCoverRate_AnyMax_ZX(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_ZX(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_ZX(CubA);
		return std::max<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
	static double GetCoverRate_AnyMin_ZX(const SSPN_Cmn_3DCuboid<TP>& CubA, const SSPN_Cmn_3DCuboid<TP>& CubB)
	{
		double fCovRat_AbyB = CubA.GetCoverRate_ZX(CubB);
		double fCovRat_BbyA = CubB.GetCoverRate_ZX(CubA);
		return std::min<double>(fCovRat_AbyB, fCovRat_BbyA);
	};
};

template<typename TPDst, typename TPSrc>
inline void Eq_Cub3D_to(SSPN_Cmn_3DCuboid<TPDst>& CubDst, const SSPN_Cmn_3DCuboid<TPSrc>& CubSrc)
{
	Eq_Pnt3D_to(CubDst.m_P3D_Min, CubSrc.m_P3D_Min);
	Eq_Pnt3D_to(CubDst.m_P3D_Max, CubSrc.m_P3D_Max);

	CubDst.Normalize();
};

//*******************************************************************************************
//------------------------------------------------------------------------------------------
template<class TP>
const SSPN_Cmn_3DCuboid<TP>& SSPN_Cmn_3DCuboid<TP>::operator= (const SSPN_Cmn_3DCuboid<TP>& Cub)
{
	m_P3D_Max = Cub.Get3DPointMax();
	m_P3D_Min = Cub.Get3DPointMin();

	return *this;
};
//------------------------------------------------------------------------------------------
// ��֪���㹹��Cub
template<class TP>
void SSPN_Cmn_3DCuboid<TP>::Construct(SSPN_Cmn_3DPoint<TP> P1, SSPN_Cmn_3DPoint<TP> P2)
{
	//�������������������
	m_P3D_Max = P2;
	m_P3D_Min = P1;
	NormalizeCub();
};
//------------------------------------------------------------------------------------------
//���������òο����ֵ

//��С��
template<class TP>
const SSPN_Cmn_3DPoint<TP>& SSPN_Cmn_3DCuboid<TP>::Get3DPointMin() const
{
	return m_P3D_Min;
};

//���� 
template<class TP>
const SSPN_Cmn_3DPoint<TP>& SSPN_Cmn_3DCuboid<TP>::Get3DPointMax() const
{
	return m_P3D_Max;
};
//------------------------------------------------------------------------------------------

//*************************************
//*****         һά����      *********
//*************************************

////����x�᷽������֮�䳤��
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetLengthX() const
//{
//	return (m_P3D_Max.x() - m_P3D_Min.x());
//}
////-------------------------------------------
////����y�᷽������֮�䳤��
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetLengthY() const 
//{
//	return (m_P3D_Max.y() - m_P3D_Min.y());
//	
//};
////-------------------------------------------
////����z�᷽������֮�䳤��
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetLengthZ() const 
//{
//    return (m_P3D_Max.z() - m_P3D_Min.z());
//};

//-------------------------------------------------------------------------------------------
//*************************************
//*****         ��ά����      *********
//*************************************

////����xyƽ�����
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetAreaXY() const 
//{
//	return (m_P3D_Max.x() - m_P3D_Min.x()) * (m_P3D_Max.y() - m_P3D_Min.y());
//};
////----------------------------------------
////����yzƽ�����
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetAreaYZ() const 
//{
//	return (m_P3D_Max.y() - m_P3D_Min.y()) * (m_P3D_Max.z() - m_P3D_Min.z());
//};
////----------------------------------------
////����zxƽ�����
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetAreaZX() const 
//{
//	return (m_P3D_Max.x() - m_P3D_Min.x()) * (m_P3D_Max.z() - m_P3D_Min.z());
//};
////--------------------------------------------------------------------------------------------
////*************************************
////*****         ��ά����      *********
////*************************************
//
////����Cub�����
//template<class TP>
//TP SSPN_Cmn_3DCuboid<TP>::GetVolume() const 
//{
//	return (m_P3D_Max.x() - m_P3D_Min.x()) * (m_P3D_Max.y() - m_P3D_Min.y()) *  (m_P3D_Max.z()-m_P3D_Min.z());
//};
//----------------------------------------
//����Cub�����ĵ�
//template<class TP>
//SSPN_Cmn_3DPoint<TP> SSPN_Cmn_3DCuboid<TP>::Get3DPointCtr() const 
//{
//	SSPN_Cmn_3DPoint<TP> tempPoint;
//
//	tempPoint.x((m_P3D_Max.x() + m_P3D_Min.x()) / 2);
//    tempPoint.y((m_P3D_Max.y() + m_P3D_Min.y()) / 2);
//    tempPoint.z((m_P3D_Max.z() + m_P3D_Min.z()) / 2);
//
//    return tempPoint;
//};
//--------------------------------------------------------------------------------------------
//*****************************************************************************
//�����������ݲ����Ϲ�����Ҫ������,��֤��������ά��ͬʱ����һ�µĴ�С��ϵ**
//*****************************************************************************

template <class TP>
void SSPN_Cmn_3DCuboid<TP>::NormalizeCub()//���ֱ�������
{
	Normalize();
};
//--------------------------------------------------------------------------------------------
//�ж�ĳһ���Ƿ���Cub��
template<class TP>
BOOL SSPN_Cmn_3DCuboid<TP>::IsInCub(const SSPN_Cmn_3DPoint<TP> &  P) const
{
	return
		(
			m_P3D_Min.x() <= P.x() && P.x() <= m_P3D_Max.x() &&
			m_P3D_Min.y() <= P.y() && P.y() <= m_P3D_Max.y() &&
			m_P3D_Min.z() <= P.z() && P.z() <= m_P3D_Max.z()
			);
};

//--------------------------------------------------------------------------------------------

//template<class TP>
//void SSPN_Cmn_3DCuboid<TP>::Serialize(CSPN_Cmn_Archive& Ar)
//{
//	int iVer = -1;
//	if (Ar.IsStoring())
//	{
//		iVer = 1;
//		Ar << iVer;
//		m_P3D_Min.Serialize(Ar);
//		m_P3D_Max.Serialize(Ar);
//	}
//	else
//	{
//		Ar >> iVer;
//		switch (iVer)
//		{
//		case 1:
//		{
//			m_P3D_Min.Serialize(Ar);
//			m_P3D_Max.Serialize(Ar);
//		}
//		break;
//		default:
//			::ShowMsg("�ļ���ʽ����: SSPN_Cmn_3DCuboid<TP>!!!");
//		}
//	}
//}

//--------------------------------------------------------------------------------------------
////*************************************
////*****        Cub֮�����    *********
////*************************************     
//
// ����Cub�ϲ���һ��Cub���޸���������
template<class TP>
void SSPN_Cmn_3DCuboid<TP>::UnionCub(const SSPN_Cmn_3DCuboid<TP>& Cub)
{
	this->NormalizeCub();
	assert(Cub.IsNormalized());

	SSPN_Cmn_3DPoint<TP> P1 = Cub.m_P3D_Min;
	SSPN_Cmn_3DPoint<TP> P2 = Cub.m_P3D_Max;

	//ͨ��������֪��С�㹹��һ������С��
	P1[0] = P1.x() < m_P3D_Min.x() ? P1.x() : m_P3D_Min.x();
	P1[1] = P1.y() < m_P3D_Min.y() ? P1.y() : m_P3D_Min.y();
	P1[2] = P1.z() < m_P3D_Min.z() ? P1.z() : m_P3D_Min.z();

	//ͨ��������֪���㹹��һ��������
	P2[0] = P2.x() < m_P3D_Max.x() ? m_P3D_Max.x() : P2.x();
	P2[1] = P2.y() < m_P3D_Max.y() ? m_P3D_Max.y() : P2.y();
	P2[2] = P2.z() < m_P3D_Max.z() ? m_P3D_Max.z() : P2.z();

	Construct(P1, P2);
};

// Cub֮����󽻼����ı���������
template<class TP>
BOOL SSPN_Cmn_3DCuboid<TP>::IntersectCub(const SSPN_Cmn_3DCuboid<TP>& Cub)
{
	this->NormalizeCub();
	assert(Cub.IsNormalized());

	SSPN_Cmn_3DPoint<TP> PMin;
	SSPN_Cmn_3DPoint<TP> PMax;

	//ͨ��������֪��С�㹹��һ������С��(�����ܴ�
	PMin[0] = __max(m_P3D_Min[0], Cub.m_P3D_Min[0]);
	PMin[1] = __max(m_P3D_Min[1], Cub.m_P3D_Min[1]);
	PMin[2] = __max(m_P3D_Min[2], Cub.m_P3D_Min[2]);

	PMax[0] = __min(m_P3D_Max[0], Cub.m_P3D_Max[0]);
	PMax[1] = __min(m_P3D_Max[1], Cub.m_P3D_Max[1]);
	PMax[2] = __min(m_P3D_Max[2], Cub.m_P3D_Max[2]);

	//�������������С�㹹��Cub,ʵ���󽻼�	
	if (PMax[0] < PMin[0] || PMax[1] < PMin[1] || PMax[2] < PMin[2])
	{
		Construct(PMin, PMin); // 0���!
		return FALSE;
	}
	else
	{
		Construct(PMin, PMax);
		return TRUE;
	}
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator*(TPNum vNum, const SSPN_Cmn_3DCuboid<TPCub>& Cub)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst *= vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator*(const SSPN_Cmn_3DCuboid<TPCub>& Cub, TPNum vNum)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst *= vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator/(const SSPN_Cmn_3DCuboid<TPCub>& Cub, TPNum vNum)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst /= vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator+(const SSPN_Cmn_3DCuboid<TPCub>& Cub, TPNum vNum)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst += vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator+(TPNum vNum, const SSPN_Cmn_3DCuboid<TPCub>& Cub)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst += vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator-(const SSPN_Cmn_3DCuboid<TPCub>& Cub, TPNum vNum)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst -= vNum;
	return CubDst;
};

template<typename TPNum, typename TPCub>
inline SSPN_Cmn_3DCuboid<TPCub> operator-(TPNum vNum, const SSPN_Cmn_3DCuboid<TPCub>& Cub)
{
	SSPN_Cmn_3DCuboid<TPCub> CubDst(Cub);
	CubDst *= -1;
	CubDst -= vNum;
	return CubDst;
};

/////////////////////////////////////////////////////////////////////////////
template<class TP>
class CSPN_Cmn_3DCuboid : public SSPN_Cmn_3DCuboid<TP>
{
public:
	//���캯�����������
	CSPN_Cmn_3DCuboid()
	{
		this->Zero();
	};

	CSPN_Cmn_3DCuboid(const SSPN_Cmn_3DPoint<TP>& P3Min, const SSPN_Cmn_3DPoint<TP>& P3Max)
	{
		this->m_P3D_Min = P3Min;
		this->m_P3D_Max = P3Max;
	};
	CSPN_Cmn_3DCuboid(const CSPN_Cmn_3DCuboid<TP>& Cub)
	{
		*(SSPN_Cmn_3DCuboid<TP>*)this = (const SSPN_Cmn_3DCuboid<TP>&)Cub;
	};
	virtual ~CSPN_Cmn_3DCuboid() {};
};

/////////////////////////////////////////////////////////////////////////////
//*****************************************************************

typedef CSPN_Cmn_3DCuboid<int>				Cub3D_Int;
typedef CSPN_Cmn_3DCuboid<unsigned int>		Cub3D_UInt;

typedef CSPN_Cmn_3DCuboid<short>				Cub3D_Sht;
typedef CSPN_Cmn_3DCuboid<unsigned short>	Cub3D_USht;

typedef CSPN_Cmn_3DCuboid<char>				Cub3D_Char;
typedef CSPN_Cmn_3DCuboid<unsigned char>		Cub3D_UChar;

typedef CSPN_Cmn_3DCuboid<float>				Cub3D_Flt;
typedef CSPN_Cmn_3DCuboid<double>			Cub3D_Dbl;

typedef Cub3D_Int	Cub3D_Idx;

//*****************************************************************

typedef SSPN_Cmn_3DCuboid<int>				SCub3D_Int;
typedef SSPN_Cmn_3DCuboid<unsigned int>		SCub3D_UInt;

typedef SSPN_Cmn_3DCuboid<short>				SCub3D_Sht;
typedef SSPN_Cmn_3DCuboid<unsigned short>	SCub3D_USht;

typedef SSPN_Cmn_3DCuboid<char>				SCub3D_Char;
typedef SSPN_Cmn_3DCuboid<unsigned char>		SCub3D_UChar;

typedef SSPN_Cmn_3DCuboid<float>				SCub3D_Flt;
typedef SSPN_Cmn_3DCuboid<double>			SCub3D_Dbl;

typedef SCub3D_Int	SCub3D_Idx;

//*****************************************************************

#endif //  // !defined(SPN_Cmn_3DCuboid_H__INCLUDED_
