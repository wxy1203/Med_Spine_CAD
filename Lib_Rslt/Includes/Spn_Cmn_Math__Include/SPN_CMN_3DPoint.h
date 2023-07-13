// SPN_Cmn_3DPoint.h: interface for the SSPN_Cmn_3DPoint<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_3DPoint_H__INCLUDED_
#define SPN_Cmn_3DPoint_H__INCLUDED_


#	pragma once


#include "SPN_Cmn_MATRIX.h"
#include "SPN_Cmn_2DPoint.h"

template<typename TP>
struct SSPN_Cmn_3DPoint
{
	//Constructor/destructor:
public:
	//SSPN_Cmn_3DPoint();
	//
	//SSPN_Cmn_3DPoint(TP dx, TP dy, TP dz);//[8_22 14:51:23 ]:���ṩ���캯��, ��������Ч������!
	///*explicit*/ SSPN_Cmn_3DPoint(const TP pTP3D[3])				{ x(pTP3D[0]);	y(pTP3D[1]);	z(pTP3D[2]); };

	////[11_30 5:38:12 ]: explicit SSPN_Cmn_3DPoint(CSPN_Cmn_2DPoint<TP> P2D)		{ x(P2D.x());	y(P2D.y());		z(TP(0));	 };
	//SSPN_Cmn_3DPoint(CSPN_Cmn_2DPoint<TP> P2D, TP vZ=0)				{ x(P2D.x());	y(P2D.y());		z(vZ);		 };
	//SSPN_Cmn_3DPoint(const SSPN_Cmn_3DPoint<TP>& P3D)				{ x(P3D.x());	y(P3D.y());		z(P3D.z());  };//[11_30 5:32:48 ]: 

	////[11_30 5:24:13 ]: explicit SSPN_Cmn_3DPoint(const CPointInt& P)						{ x(P.x); 		y(P.y);			z(TP(0));	 };
	//SSPN_Cmn_3DPoint(const CPointInt& P, TP vZ)					{ x(P.x); 		y(P.y);			z(vZ);		 };

	inline void Construct(TP dx, TP dy, TP dz) { x(dx);		y(dy);			z(dz); };
	inline void Construct(const TP pTP3D[3]) { x(pTP3D[0]);	y(pTP3D[1]);	z(pTP3D[2]); };

	inline void Construct(const CSPN_Cmn_2DPoint<TP>& P2D) { x(P2D.x());	y(P2D.y());		z(TP(0)); };
	inline void Construct(const CSPN_Cmn_2DPoint<TP>& P2D, TP vZ) { x(P2D.x());	y(P2D.y());		z(vZ); };

	inline void Construct(const CPointInt& P) { x(P.x); 		y(P.y);			z(TP(0)); };
	inline void Construct(const CPointInt& P, TP vZ) { x(P.x); 		y(P.y);			z(vZ); };

	inline void GetMemData(TP pTP3D[3])
	{
		pTP3D[0] = x();
		pTP3D[1] = y();
		pTP3D[2] = z();
	};

	//Attributes:
public:
	static inline int	GetCount_SubDim() { return 3; };

	TP&			operator[](int i);
	const TP&	operator[](int i) const;

	inline const TP&	x() const;
	inline const TP&	y() const;
	inline const TP&	z() const;

	inline TP&	x() { return m_arr_XYZ[0]; };
	inline TP&	y() { return m_arr_XYZ[1]; };
	inline TP&	z() { return m_arr_XYZ[2]; };

	inline void x(TP fx);
	inline void y(TP fy);
	inline void z(TP fz);

	inline SSPN_Cmn_3DPoint<short> ToShort() const//[11_30 19:44:39 ]: 
	{
		SSPN_Cmn_3DPoint<short> P3Sht;
		P3Sht[0] = fRound(m_arr_XYZ[0]);
		P3Sht[1] = fRound(m_arr_XYZ[1]);
		P3Sht[2] = fRound(m_arr_XYZ[2]);
		return P3Sht;
	};

	inline SSPN_Cmn_3DPoint<int> ToInt() const//[11_30 19:44:39 ]: 
	{
		SSPN_Cmn_3DPoint<int> P3Int;
		P3Int[0] = fRound(m_arr_XYZ[0]);
		P3Int[1] = fRound(m_arr_XYZ[1]);
		P3Int[2] = fRound(m_arr_XYZ[2]);
		return P3Int;
	};

	inline SSPN_Cmn_3DPoint<float> ToFloat() const//[11_13 22:21:57 ]: 
	{
		SSPN_Cmn_3DPoint<float> P3f;
		P3f[0] = m_arr_XYZ[0];
		P3f[1] = m_arr_XYZ[1];
		P3f[2] = m_arr_XYZ[2];
		return P3f;
	};

	inline SSPN_Cmn_3DPoint<double> ToDouble() const//[11_13 22:21:53 ]: 
	{
		SSPN_Cmn_3DPoint<double> P3f;
		P3f[0] = m_arr_XYZ[0];
		P3f[1] = m_arr_XYZ[1];
		P3f[2] = m_arr_XYZ[2];
		return P3f;
	};

	inline SSPN_Cmn_2DPoint<TP> ToPnt2D_XY() const//[7_9 9:52:12 ]:
	{
		SSPN_Cmn_2DPoint<TP> P2;
		P2[0] = m_arr_XYZ[0];
		P2[1] = m_arr_XYZ[1];
		return P2;
	};

	inline SSPN_Cmn_2DPoint<TP> ToPnt2D_YZ() const//[7_9 9:52:12 ]:
	{
		SSPN_Cmn_2DPoint<TP> P2;
		P2[0] = m_arr_XYZ[1];
		P2[1] = m_arr_XYZ[2];
		return P2;
	};

	inline SSPN_Cmn_2DPoint<TP> ToPnt2D_ZX() const//[7_9 9:52:12 ]:
	{
		SSPN_Cmn_2DPoint<TP> P2;
		P2[0] = m_arr_XYZ[2];
		P2[1] = m_arr_XYZ[0];
		return P2;
	};

	//Calculations:
public:
	//inline const SSPN_Cmn_3DPoint<TP>& operator = (const TP v)
	//{
	//	Construct(v, v, v);
	//	return *this;
	//};
	inline const SSPN_Cmn_3DPoint<TP>& operator=(TP fV) { x(fV); y(fV); z(fV);	return *this; };


	inline const SSPN_Cmn_3DPoint<TP>& operator=(const SSPN_Cmn_3DPoint<TP>& P3D)//[11_30 5:35:17 ]: 
	{
		m_arr_XYZ[0] = P3D[0];
		m_arr_XYZ[1] = P3D[1];
		m_arr_XYZ[2] = P3D[2];
		return *this;
	};

	/*LNX_CMPT*/
	//template<typename TPVal>
	//inline const SSPN_Cmn_3DPoint<TP>& operator=(const SSPN_Cmn_3DPoint<TPVal>& P3D) { x(P3D.x()); y(P3D.y()); z(P3D.z());	return *this; };
	//template<typename TP1, typename TP2> void	MidPoint(const SSPN_Cmn_3DPoint<TP1>& P1, const SSPN_Cmn_3DPoint<TP2>& P2);
	//
	void	operator+=	(const SSPN_Cmn_3DPoint<TP>& P);
	void	operator-=	(const SSPN_Cmn_3DPoint<TP>& P);
	void	operator*=	(const SSPN_Cmn_3DPoint<TP>& P);
	void	operator/=	(const SSPN_Cmn_3DPoint<TP>& P);

	void	operator+=	(double fK);
	void	operator-=	(double fK);
	void	operator*=	(double fK);
	void	operator/=	(double fK);

	////[20210729_13:41:09 ]:
	/*LNX_CMPT*/
	//template<typename TP1,typename TP2>		static TP					Multiply_Dot(const SSPN_Cmn_3DPoint<TP1>& VctA,
	//																				 const SSPN_Cmn_3DPoint<TP2>& VctB);//[11_14 10:00:25 ]:
	//
	//template<typename TP1, typename TP2>	static SSPN_Cmn_3DPoint<TP>	Multiply_Crs(const SSPN_Cmn_3DPoint<TP1>& VctA,
	//																				 const SSPN_Cmn_3DPoint<TP2>& VctB);//[11_14 10:00:22 ]:
	//
	//template<typename TP1>	inline SSPN_Cmn_3DPoint<TP> Multiply_XYZ(const SSPN_Cmn_3DPoint<TP1>& VctB) const//[9_3 10:00:58 ]:
	//{
	//	SSPN_Cmn_3DPoint sP;
	//	{
	//		sP[0] = (*this)[0] * VctB[0];
	//		sP[1] = (*this)[1] * VctB[1];
	//		sP[2] = (*this)[2] * VctB[2];
	//	}
	//	return sP;
	//};
	//
	inline BOOL	operator==(const SSPN_Cmn_3DPoint<TP>& P) const
	{
		return
			FLT_EQ(P.x(), x()) &&
			FLT_EQ(P.y(), y()) &&
			FLT_EQ(P.z(), z());
	};
	inline BOOL	operator!=(const SSPN_Cmn_3DPoint<TP>& P) const
	{
		return !(*this == P);
	};
	//
	//template<typename TP1, typename TP2>
	//inline void LimitXYZ_to_MinMaxEq(TP1 xMin, TP1 yMin, TP1 zMin, TP2 xMax, TP2 yMax, TP2 zMax)
	//{
	//	(*this)[0] = std::max<TP>((*this)[0], std::min<TP>(xMin, xMax));
	//	(*this)[1] = std::max<TP>((*this)[1], std::min<TP>(yMin, yMax));
	//	(*this)[2] = std::max<TP>((*this)[2], std::min<TP>(zMin, zMax));
	//
	//	(*this)[0] = std::min<TP>((*this)[0], std::max<TP>(xMin, xMax));
	//	(*this)[1] = std::min<TP>((*this)[1], std::max<TP>(yMin, yMax));
	//	(*this)[2] = std::min<TP>((*this)[2], std::max<TP>(zMin, zMax));
	//};
	//
	//template<typename TP1, typename TP2>
	//inline void LimitXYZ_to_MinMaxEq(SSPN_Cmn_3DPoint<TP1> P3Min, SSPN_Cmn_3DPoint<TP2> P3Max)
	//{
	//	LimitXYZ_to_MinMaxEq(P3Min[0], P3Min[1], P3Min[2],
	//						 P3Max[0], P3Max[1], P3Max[2]);
	//};

	double		GetVectLength()		const;
	double		GetVectLengthSq()	const;

	SSPN_Cmn_3DPoint<TP> GetUnitVect() const;

	BOOL IsFullZero() const;

	//Operations:
public:
	//void Serialize(CSPN_Cmn_Archive& ar);

	double GetDistTo(const SSPN_Cmn_3DPoint<TP>& P3D) const;	//��P��ľ���
	double GetDistTo_Sq(const SSPN_Cmn_3DPoint<TP>& P3D) const;	//��P��ľ����ƽ��(ʡ���˿�������, ͨ�������ڼ��پ���ıȽϼ���)

//Static:
public:
	//[20210729_13:43:38 ]: /*LNX_CMPT*/
	//template<typename TPFLT>
	//static BOOL IntersectLineAndSphere_PointOut(const SSPN_Cmn_3DPoint<TPFLT>& PC,
	//											const TPFLT  R,
	//											const SSPN_Cmn_3DPoint<TPFLT>& PA,
	//											const SSPN_Cmn_3DPoint<TPFLT>& PB,
	//											SSPN_Cmn_3DPoint<TP>& P);

	static void MovePoint(const SSPN_Cmn_3DPoint<TP> PDxyz, SSPN_Cmn_3DPoint<TP>* pP, const UINT nP = 1);

	//template<typename TPFLT>
	//static void GetRotMtxT_RotateCoordSys_StretchAllow_Yes(SPN_Cmn_Matrix<TPFLT>& RT,
	//													   const SSPN_Cmn_3DPoint<TPFLT>& sP3_X_Dst,
	//													   const SSPN_Cmn_3DPoint<TPFLT>& sP3_Y_Dst,
	//													   const SSPN_Cmn_3DPoint<TPFLT>& sP3_Z_Dst);//[11_14 10:14:06 ]:
	//template<typename TPFLT>
	//static void GetRotMtxT_RotateCoordSys_StretchAllow_No(SPN_Cmn_Matrix<TPFLT>& RT,
	//													  const SSPN_Cmn_3DPoint<TPFLT>& sP3_X_Dst,
	//													  const SSPN_Cmn_3DPoint<TPFLT>& sP3_Y_Dst,
	//													  const SSPN_Cmn_3DPoint<TPFLT>& sP3_Z_Dst);//[11_14 10:14:06 ]:
	//
	//
	//template<typename TPFLT>
	//static void GetRotMtxT_RotatePoint(	const SSPN_Cmn_3DPoint<TPFLT>& PUnitVectAxis,	//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TPFLT> object 
	//									TPFLT thet,									//rotating angle
	//									BOOL bDegree,								//denote the unit of thet: 0-radian/1-degree
	//									SPN_Cmn_Matrix<TPFLT>& RT);						//output;Transpose of the Rotating matrix; 
	//																				//Note: for speed consideration, RT rather than R is returned, which different from the format in the BOOK;
	//template<typename TPFLT>
	//static void GetRotMtxT_RotateCoordSys(const SSPN_Cmn_3DPoint<TPFLT>& PUnitVectAxis,	//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TPFLT> object 
	//									  TPFLT thet,									//rotating angle
	//									  BOOL bDegree,								//denote the unit of thet: 0-radian/1-degree
	//									  SPN_Cmn_Matrix<TPFLT>& RT						//output;Transpose of the Rotating matrix; 
	//																				//Note: for speed consideration, RT rather than R is returned, which different from the format in the BOOK;
	//									 );
	//template<typename TPFLT>
	//static void RotateCoordSys(const SSPN_Cmn_3DPoint<TPFLT>& PUnitVectAxis,		//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TPFLT> object 
	//						   const TPFLT thet,									//rotating angle
	//						   const BOOL bDegree,								//denote the unit of thet: 0-radian/1-degree
	//						   SSPN_Cmn_3DPoint<TP> *pPoint, const int nPoint=1);//points to be converted: from *pPoint for nPoint points.
	//
	//template<typename TPFLT>
	//static void RotatePoint(const SSPN_Cmn_3DPoint<TPFLT>& PUnitVectAxis,			//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TPFLT> object 
	//						const TPFLT thet,										//rotating angle
	//						const BOOL bDegree,									//denote the unit of thet: 0-radian/1-degree
	//						SSPN_Cmn_3DPoint<TP> *pPoint, const int nPoint=1);	//points to be converted: from *pPoint for nPoint points.
	//
	////[11_7 15:47:28 ]: 
	//template<typename TPFLT>
	//static void RotatePoint(const SSPN_Cmn_3DPoint<TPFLT>& PAxisBgn,
	//						const SSPN_Cmn_3DPoint<TPFLT>& PAxisEnd,
	//						const TPFLT thet,
	//						const BOOL bDegree,
	//						SSPN_Cmn_3DPoint<TP> *pPoint, const int nPoint=1);
	//
	//template<typename TPFLT>
	//static SSPN_Cmn_3DPoint<TPFLT> GetPerpendFoot(const SSPN_Cmn_3DPoint<TPFLT>& A,
	//										  const SSPN_Cmn_3DPoint<TPFLT>& B,	//define a line
	//										  const SSPN_Cmn_3DPoint<TP>& P);				//a point
	//
	//template<typename TPFLT>
	//static BOOL IntersectLineAndSphere_PointIn(const SSPN_Cmn_3DPoint<TPFLT>& PC,
	//										   const TPFLT  R,
	//										   const SSPN_Cmn_3DPoint<TPFLT>& PA,
	//										   const SSPN_Cmn_3DPoint<TPFLT>& PB,
	//										   SSPN_Cmn_3DPoint<TP>& P);
	//template<typename TPFLT>
	//static void IntersectLineAndPlane(const SSPN_Cmn_3DPoint<TPFLT>& NormVect,//normline of the plane
	//								  const SSPN_Cmn_3DPoint<TPFLT>& pointP,  //point on the plane
	//								  const SSPN_Cmn_3DPoint<TPFLT>& pointA,  //point A to define the line
	//								  const SSPN_Cmn_3DPoint<TPFLT>& pointB,	//point B to defint the line 
	//								  SSPN_Cmn_3DPoint<TP>& pointI);	//point of intersection
	//*******************************************************************************************

	static void	SetSortKey(int iSortKey);
	static int  GetSortKey();
	static BOOL IsSortKey(int iSortKey);

	inline void Zero()
	{
		m_arr_XYZ[0] = 0;
		m_arr_XYZ[1] = 0;
		m_arr_XYZ[2] = 0;
	};

	//Operations:
public:

#ifdef _DEBUG
	////void AssertValid(SSPN_Cmn_3DPoint<TP>& P);
	////void TraceFmt(std::string& StrTrace)const;
#endif // 

//friend:
	friend ::SSPN_Cmn_3DPoint<TP>  operator-(const SSPN_Cmn_3DPoint<TP>& P);

	//friend ::CSPN_Cmn_Archive& operator<<(CSPN_Cmn_Archive& ar, const SSPN_Cmn_3DPoint<TP>& P);
	//friend ::CSPN_Cmn_Archive& operator>>(CSPN_Cmn_Archive& ar, const SSPN_Cmn_3DPoint<TP>& P);

	//void WrStringGrow(std::string &S);


//data member:
	TP* GetDataBuf() { return m_arr_XYZ; };
	const TP* GetDataBuf() const { return m_arr_XYZ; };
protected:
	static int	m_iSortKey;
	TP			m_arr_XYZ[3];
};

template<typename TP, typename TP1>
inline SSPN_Cmn_3DPoint<TP> SSPN_Cmn_3DPoint__Mk(const SSPN_Cmn_3DPoint<TP1>& sP3)
{
	SSPN_Cmn_3DPoint<TP> sP3_R;
	sP3_R.Construct(sP3[0], sP3[1], sP3[2]);
	return sP3_R;
}

template<typename TP, typename TP1 = TP, typename TP2 = TP1>
inline SSPN_Cmn_3DPoint<TP> SSPN_Cmn_3DPoint__Multiply_XYZ(const SSPN_Cmn_3DPoint<TP1>& sP3A, const SSPN_Cmn_3DPoint<TP2>& VctB)
{
	SSPN_Cmn_3DPoint<TP> sP;
	{
		sP[0] = sP3A[0] * VctB[0];
		sP[1] = sP3A[1] * VctB[1];
		sP[2] = sP3A[2] * VctB[2];
	}
	return sP;
};

//------------------------------------------------------------------------------
//[12_29 17:23:36 ]:
template<typename TP>
std::fstream& operator <<(std::fstream& FStream, const SSPN_Cmn_3DPoint<TP>& sP3)
{
	FStream << sP3[0];
	FStream << sP3[1];
	FStream << sP3[2];
	return FStream;
};
template<typename TP>
std::fstream& operator >>(std::fstream& FStream, SSPN_Cmn_3DPoint<TP>& sP3)
{
	FStream >> sP3[0];
	FStream >> sP3[1];
	FStream >> sP3[2];
	return FStream;
};

//------------------------------------------------------------------------------
template<typename TP>
inline TP& SSPN_Cmn_3DPoint<TP>::operator[](int i)
{
	assert(i >= 0 && i < 3);
	return m_arr_XYZ[i];
};
//------------------------------------------------------------------------------
template<typename TP>
inline const TP& SSPN_Cmn_3DPoint<TP>::operator[](int i) const
{
	assert(i >= 0 && i < 3);
	return m_arr_XYZ[i];
};
//------------------------------------------------------------------------------
template<typename TP> inline const TP& SSPN_Cmn_3DPoint<TP>::x() const { return m_arr_XYZ[0]; };
template<typename TP> inline const TP& SSPN_Cmn_3DPoint<TP>::y() const { return m_arr_XYZ[1]; };
template<typename TP> inline const TP& SSPN_Cmn_3DPoint<TP>::z() const { return m_arr_XYZ[2]; };
//------------------------------------------------------------------------------
template<typename TP> inline void SSPN_Cmn_3DPoint<TP>::x(TP fx) { m_arr_XYZ[0] = fx; };
template<typename TP> inline void SSPN_Cmn_3DPoint<TP>::y(TP fy) { m_arr_XYZ[1] = fy; };
template<typename TP> inline void SSPN_Cmn_3DPoint<TP>::z(TP fz) { m_arr_XYZ[2] = fz; };
//------------------------------------------------------------------------------
template<typename TP>
inline SSPN_Cmn_3DPoint<TP> operator-(const SSPN_Cmn_3DPoint<TP>& P)
{
	SSPN_Cmn_3DPoint<TP> sP3;
	sP3.Construct(-P[0], -P[1], -P[2]);
	return sP3;
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::SetSortKey(int iSortKey)
{
	m_iSortKey = iSortKey % 3;
};
//------------------------------------------------------------------------------
template<typename TP>
inline int SSPN_Cmn_3DPoint<TP>::GetSortKey()
{
	return m_iSortKey;
};
//------------------------------------------------------------------------------
template<typename TP>
inline BOOL SSPN_Cmn_3DPoint<TP>::IsSortKey(int iSortKey)
{
	if (iSortKey == m_iSortKey)
		return TRUE;
	else
		return FALSE;
};
//------------------------------------------------------------------------------
template<typename TP1, typename TP2>
inline BOOL SSPN_Cmn_3DPoint__Eq(const SSPN_Cmn_3DPoint<TP1>& P1, const SSPN_Cmn_3DPoint<TP2>& P2)
{
	return
		FLT_EQ(P1.x(), P2.x()) &&
		FLT_EQ(P1.y(), P2.y()) &&
		FLT_EQ(P1.z(), P2.z());
};
//------------------------------------------------------------------------------
template<typename TP1, typename TP2>
inline BOOL SSPN_Cmn_3DPoint__NotEq(const SSPN_Cmn_3DPoint<TP1>& P1, const SSPN_Cmn_3DPoint<TP2>& P2)
{
	return !SSPN_Cmn_3DPoint__Eq(P1, P2);
}
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator +=(const SSPN_Cmn_3DPoint<TP>& P)
{
	m_arr_XYZ[0] += P.x();
	m_arr_XYZ[1] += P.y();
	m_arr_XYZ[2] += P.z();
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator -=(const SSPN_Cmn_3DPoint<TP>& P)
{
	m_arr_XYZ[0] -= P.x();
	m_arr_XYZ[1] -= P.y();
	m_arr_XYZ[2] -= P.z();
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator *=(const SSPN_Cmn_3DPoint<TP>& P)
{
	m_arr_XYZ[0] *= P.x();
	m_arr_XYZ[1] *= P.y();
	m_arr_XYZ[2] *= P.z();
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator /=(const SSPN_Cmn_3DPoint<TP>& P)
{
	m_arr_XYZ[0] /= P.x();
	m_arr_XYZ[1] /= P.y();
	m_arr_XYZ[2] /= P.z();
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator +=(double fK)
{
	m_arr_XYZ[0] += fK;
	m_arr_XYZ[1] += fK;
	m_arr_XYZ[2] += fK;
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator -=(double fK)
{
	assert(!FLT_EQ(fK, 0.0f));
	m_arr_XYZ[0] -= fK;
	m_arr_XYZ[1] -= fK;
	m_arr_XYZ[2] -= fK;
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator *=(double fK)
{
	m_arr_XYZ[0] *= fK;
	m_arr_XYZ[1] *= fK;
	m_arr_XYZ[2] *= fK;
};
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::operator /=(double fK)
{
	assert(!FLT_EQ(fK, 0.0f));
	m_arr_XYZ[0] /= fK;
	m_arr_XYZ[1] /= fK;
	m_arr_XYZ[2] /= fK;
};
//------------------------------------------------------------------------------
template<typename TPR, typename TP2> /*�������޷�֧�����ֲ���!*/
inline SSPN_Cmn_3DPoint<TPR> operator+(const SSPN_Cmn_3DPoint<TPR>& P1, const SSPN_Cmn_3DPoint<TP2>& P2)
{
	SSPN_Cmn_3DPoint<TPR> SP3;
	SP3.Construct(P1.x() + P2.x(), P1.y() + P2.y(), P1.z() + P2.z());
	return SP3;
};
//------------------------------------------------------------------------------
template<typename TPR, typename TP2> /*�������޷�֧�����ֲ���!*/
inline SSPN_Cmn_3DPoint<TPR> operator-(const SSPN_Cmn_3DPoint<TPR>& P1, const SSPN_Cmn_3DPoint<TP2>& P2)
{
	SSPN_Cmn_3DPoint<TPR> SP3;
	SP3.Construct(P1.x() - P2.x(), P1.y() - P2.y(), P1.z() - P2.z());
	return SP3;
};
//------------------------------------------------------------------------------
template<typename TP, typename TP1 = TP, typename TP2 = TP1>
inline void SSPN_Cmn_3DPoint__MidPoint(const SSPN_Cmn_3DPoint<TP1>& P1, const SSPN_Cmn_3DPoint<TP2>& P2)
{
	SSPN_Cmn_3DPoint<TP> sP3R;
	sP3R.x((P1.x() + P2.x()) / 2);
	sP3R.y((P1.y() + P2.y()) / 2);
	sP3R.z((P1.z() + P2.z()) / 2);
};
//------------------------------------------------------------------------------
template<typename TP, typename TP1 = TP, typename TP2 = TP1>
inline TP SSPN_Cmn_3DPoint__Multiply_Dot(const SSPN_Cmn_3DPoint<TP1>& VctA,
										const SSPN_Cmn_3DPoint<TP2>& VctB) //[11_14 10:00:25 ]:
{
	TP vR =
		VctA[0] * VctB[0] +
		VctA[1] * VctB[1] +
		VctA[2] * VctB[2];
	return vR;
};
//------------------------------------------------------------------------------
template<typename TP, typename TP1 = TP, typename TP2 = TP1>
inline SSPN_Cmn_3DPoint<TP> SSPN_Cmn_3DPoint__Multiply_Crs(const SSPN_Cmn_3DPoint<TP1>& VctA,
														 const SSPN_Cmn_3DPoint<TP2>& VctB) //[11_14 10:00:22 ]:
{
	// {a} X {b}=
	// ({a_2}{b_3}-{a_3}{b_2})i + 
	// ({a_3}{b_1}-{a_1}{b_3})j +
	// ({a_1}{b_2}-{a_2}{b_1})k

	SSPN_Cmn_3DPoint<TP> VctC;
	VctC[0] = VctA[1] * VctB[2] - VctA[2] * VctB[1];
	VctC[1] = VctA[2] * VctB[0] - VctA[0] * VctB[2];
	VctC[2] = VctA[0] * VctB[1] - VctA[1] * VctB[0];
	return VctC;
};
//------------------------------------------------------------------------------
template<typename TPR, typename TPP> /*�������޷�֧�����ֲ���!*/
inline SSPN_Cmn_3DPoint<TPR> operator*(const SPN_Cmn_Matrix<TPR>& Mtx, const SSPN_Cmn_3DPoint<TPP>& P1)
{
	assert(3 == Mtx.GetSizeM() && 3 == Mtx.GetSizeN());

	SPN_Cmn_Matrix<TPR> P1M(3, 1);
	{
		P1M[0][0] = P1.x();
		P1M[1][0] = P1.y();
		P1M[2][0] = P1.z();
	}

	SPN_Cmn_Matrix<TPR> P2M = Mtx * P1M;

	SSPN_Cmn_3DPoint<TPR> P2;
	{
		P2[0] = P2M[0][0];
		P2[1] = P2M[1][0];
		P2[2] = P2M[2][0];
	}

	return P2;
};
////------------------------------------------------------------------------------
//template<typename TPR, typename TP2>
//inline SSPN_Cmn_3DPoint<TPR> operator *(const SSPN_Cmn_3DPoint<TPR>& P, TP2 vK)
//{
//	SSPN_Cmn_3DPoint<TPR> sP3D;
//	sP3D.Construct(P.x() * vK, P.y() * vK, P.z() * vK);
//	return sP3D;
//};
//------------------------------------------------------------------------------
//template<typename TPR, typename TP2>
//inline SSPN_Cmn_3DPoint<TPR> operator /(const SSPN_Cmn_3DPoint<TPR>& P, TP2 vK)
//{
//	assert(!FLT_EQ(vK, 0.0f));
//	SSPN_Cmn_3DPoint<TP> sP3D;
//	sP3D.Construct(P.x() / vK, P.y() / vK, P.z() / vK);
//	return sP3D;
//};

template<typename TP>
inline double SSPN_Cmn_3DPoint<TP>::GetVectLength() const
{
	return sqrt(x()*x() + y()*y() + z()*z());
};
template<typename TP>
inline double SSPN_Cmn_3DPoint<TP>::GetVectLengthSq() const
{
	return x()*x() + y()*y() + z()*z();
};
//------------------------------------------------------------------------------
template<typename TP1, typename TP2 = TP1>
inline void SSPN_Cmn_3DPoint__MovePoint(const SSPN_Cmn_3DPoint<TP2> PDxyz, SSPN_Cmn_3DPoint<TP1>* pP, const UINT nP/*=1*/)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i][0] += PDxyz[0];
		pP[i][1] += PDxyz[1];
		pP[i][2] += PDxyz[2];
	}
}
//------------------------------------------------------------------------------
template<typename TP>
inline void SSPN_Cmn_3DPoint<TP>::MovePoint(const SSPN_Cmn_3DPoint<TP> PDxyz, SSPN_Cmn_3DPoint<TP>* pP, const UINT nP/*=1*/)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i][0] += PDxyz[0];
		pP[i][1] += PDxyz[1];
		pP[i][2] += PDxyz[2];
	}
}
//------------------------------------------------------------------------------
template<typename TPR, typename TPP = TPR>
inline SSPN_Cmn_3DPoint<TPR> SSPN_Cmn_3DPoint__GetUnitVect(const SSPN_Cmn_3DPoint<TPP>& P3D)
{
	SSPN_Cmn_3DPoint<TPR> sP3_Vct;

	double r = sqrt(P3D.x()*P3D.x() + P3D.y()*P3D.y() + P3D.z()*P3D.z());
	if (r <= FLT_MIN)
	{
		sP3_Vct.Construct(P3D.x(), P3D.y(), P3D.z());
	}
	else
	{
		sP3_Vct.Construct(P3D.x() / r, P3D.y() / r, P3D.z() / r);
	}
	return sP3_Vct;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template<typename TP>
inline SSPN_Cmn_3DPoint<TP> SSPN_Cmn_3DPoint<TP>::GetUnitVect() const
{
	const SSPN_Cmn_3DPoint<TP>& P3D = *this;

	SSPN_Cmn_3DPoint<TP> sP3_Vct;

	double r = sqrt(P3D.x()*P3D.x() + P3D.y()*P3D.y() + P3D.z()*P3D.z());
	if (r <= FLT_MIN)
	{
		sP3_Vct.Construct(P3D.x(), P3D.y(), P3D.z());
	}
	else
	{
		sP3_Vct.Construct(P3D.x() / r, P3D.y() / r, P3D.z() / r);
	}
	return sP3_Vct;
}
//------------------------------------------------------------------------------
//template<typename TP>
//void SSPN_Cmn_3DPoint<TP>::Serialize(CSPN_Cmn_Archive& ar)
//{
//	if (ar.IsStoring())
//	{
//		ar << m_arr_XYZ[0];
//		ar << m_arr_XYZ[1];
//		ar << m_arr_XYZ[2];
//	}
//	else
//	{
//		ar >> m_arr_XYZ[0];
//		ar >> m_arr_XYZ[1];
//		ar >> m_arr_XYZ[2];
//	}
//}
////------------------------------------------------------------------------------
//template<typename TP>
//::CSPN_Cmn_Archive& operator<<(CSPN_Cmn_Archive& ar, SSPN_Cmn_3DPoint<TP>& P)
//{
//	ar << P[0] << P[1] << P[2];
//	return ar;
//}
//template<typename TP>
//::CSPN_Cmn_Archive& operator>>(CSPN_Cmn_Archive& ar, SSPN_Cmn_3DPoint<TP>& P)
//{
//	ar >> P[0] >> P[1] >> P[2];
//	return ar;
//}
//------------------------------------------------------------------------------
//template<typename TP>
//inline void SSPN_Cmn_3DPoint<TP>::WrStringGrow(std::string &S)
//{
//	std::string StrTmp;
//	StrTmp.Format("<%f,%f,%f> ", x(), y(), z());
//	S+=StrTmp;
//}
//------------------------------------------------------------------------------
//#ifdef _DEBUG
//template<typename TP>
//void SSPN_Cmn_3DPoint<TP>::AssertValid(SSPN_Cmn_3DPoint<TP>& P)
//{
//	std::string S;
//	for(int i=0; i<3; i++)
//	{
//		S.Format("%f",P[i]);
//		std::string SzErr("#IND");
//		if(S.FindOneOf(SzErr)>=0)
//		{
//			std::string Stmp;
//			P.TraceFmt(Stmp);
//			::ShowMsg(Stmp);
//			abort();
//		}
//	}
//};
//template<typename TP>
//void SSPN_Cmn_3DPoint<TP>::TraceFmt(std::string& StrTrace) const
//{
//	StrTrace.Format("%sPoint3D<%f,%f,%f>", StrTrace, x(), y(), z());
//};
//#endif // 
//------------------------------------------------------------------------------
template<typename TPAx, typename TPMtx = TPAx>
inline void SSPN_Cmn_3DPoint__GetRotMtxT_RotateCoordSys(const SSPN_Cmn_3DPoint<TPAx>& PUnitVectAxis,	//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TP> object 
													   double thet,									//rotating angle
													   BOOL bDegree,									//denote the unit of thet: 0-radian/1-degree
													   SPN_Cmn_Matrix<TPMtx>& RT)						//output;Transpose of the Rotating matrix; 
																									   //Note: for speed consideration, RT rather than R is returned, which different from the format in the BOOK;
{
	assert(RT.GetSizeM() == RT.GetSizeN() && RT.GetSizeN() == 3);
	if (bDegree)
		thet *= CNST_dbl_RADpDEG;

	//1. data define:
	double L1 = PUnitVectAxis[0];
	double L2 = PUnitVectAxis[1];
	double L3 = PUnitVectAxis[2];

	double dCos = cos(thet);
	double dSin = sin(thet);

	//2. Calculate the rotating matrix:
	double d1_cos = 1 - dCos;

	double L1L2 = L1 * L2;
	double L2L3 = L2 * L3;
	double L1L3 = L1 * L3;

	RT[0][0] = dCos + L1 * L1*(d1_cos);    RT[1][0] = L1L2 * (d1_cos)-L3 * dSin;  RT[2][0] = L1L3 * (d1_cos)+L2 * dSin;
	RT[0][1] = L1L2 * (d1_cos)+L3 * dSin;  RT[1][1] = dCos + L2 * L2*(d1_cos);    RT[2][1] = L2L3 * (d1_cos)-L1 * dSin;
	RT[0][2] = L1L3 * (d1_cos)-L2 * dSin;  RT[1][2] = L2L3 * (d1_cos)+L1 * dSin;  RT[2][2] = dCos + L3 * L3*(d1_cos);
}
//--------------------------------------------------------------------------------------------------------------------
//Rotating Matrix: the format is from "���� 2.14" in Page 44 of <<������Ӿ�--�㷨��ϵͳԭ��>>: 
//
template<typename TPAx, typename TPPnt = TPAx>
inline void SSPN_Cmn_3DPoint__RotateCoordSys(const SSPN_Cmn_3DPoint<TPAx>& PUnitVectAxis,		//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TP> object 
											const double thet,									//rotating angle
											const BOOL bDegree,								//denote the unit of thet: 0-radian/1-degree
											SSPN_Cmn_3DPoint<TPPnt> *pPoint, const int nPoint = 1)//points to be converted: from *pPoint for nPoint points.
{
	SPN_Cmn_Matrix<double> RT(3, 3);//Transpose of the Rotating matrix; 
							//Note: for speed consideration, RT rather than R is used, which different from the format in the BOOK;
	SPN_Cmn_Matrix<double> PointM(3, 1);
	SSPN_Cmn_3DPoint__GetRotMtxT_RotateCoordSys<TPAx, double>(PUnitVectAxis, thet, bDegree, RT);

	int i;
	for (int i = 0; i < nPoint; i++)
	{
		PointM[0][0] = pPoint[i].x();
		PointM[1][0] = pPoint[i].y();
		PointM[2][0] = pPoint[i].z();

		PointM = RT * PointM;

		pPoint[i][0] = PointM[0][0];
		pPoint[i][1] = PointM[1][0];
		pPoint[i][2] = PointM[2][0];
	}
}
//--------------------------------------------------------------------------------------------------------------------
template<typename TPAx, typename TPPnt = TPAx>
inline void SSPN_Cmn_3DPoint__RotatePoint(const SSPN_Cmn_3DPoint<TPAx>& PAxisBgn,
										 const SSPN_Cmn_3DPoint<TPAx>& PAxisEnd,
										 const double thet,
										 const BOOL bDegree,
										 SSPN_Cmn_3DPoint<TPPnt> *pPoint,
										 const int nPoint = 1)
{
	assert(PAxisBgn != PAxisEnd);

	SSPN_Cmn_3DPoint<TPAx> PUnitVectAxis;
	{
		PUnitVectAxis = PAxisEnd;
		PUnitVectAxis -= PAxisBgn;
		double vVctLen = PUnitVectAxis.GetVectLength();
		assert(vVctLen > 0);
		PUnitVectAxis /= vVctLen;
	}

	for (int iP = 0; iP < nPoint; iP++)
	{
		pPoint[iP] -= PAxisBgn;
	}
	SSPN_Cmn_3DPoint__RotatePoint(PUnitVectAxis, thet, bDegree, pPoint, nPoint);
	for (int iP = 0; iP < nPoint; iP++)
	{
		pPoint[iP] += PAxisBgn;
	}
}

//--------------------------------------------------------------------------------------------------------------------
template<typename TPAx, typename TPPnt = TPAx>
inline void SSPN_Cmn_3DPoint__RotatePoint(const SSPN_Cmn_3DPoint<TPAx>& PUnitVectAxis,					//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TP> object 
										 const double thet,											//rotating angle
										 const BOOL bDegree,									//denote the unit of thet: 0-radian/1-degree
										 SSPN_Cmn_3DPoint<TPPnt> *pPoint,
										 const int nPoint = 1)	//points to be converted: from *pPoint for nPoint points.
{
	SSPN_Cmn_3DPoint__RotateCoordSys<TPAx, TPPnt>(PUnitVectAxis, -thet, bDegree, pPoint, nPoint);
}
//--------------------------------------------------------------------------------------------------------------------
template<typename TPR, typename TPA = TPR, typename TPB = TPA, typename TPP = TPB>
inline SSPN_Cmn_3DPoint<TPR> SSPN_Cmn_3DPoint__GetPerpendFoot(const SSPN_Cmn_3DPoint<TPA>& A,
															const SSPN_Cmn_3DPoint<TPB>& B,	//define a line
															const SSPN_Cmn_3DPoint<TPP>& P)	//a point
{
	assert(A != B);
	double a = B[0] - A[0], b = B[1] - A[1], c = B[2] - A[2];						// AB������ʸ����(a,b,c);
	double t = (a*(P[0] - A[0]) + b * (P[1] - A[1]) + c * (P[2] - A[2])) / (a*a + b * b + c * c);	//��PA��AB�ϵ�ͶӰ / AB�ĳ���)

	SSPN_Cmn_3DPoint<TPR> sP3_Rslt;
	sP3_Rslt.Construct(A[0] + a * t, A[1] + b * t, A[2] + c * t);
	return sP3_Rslt;
}
//--------------------------------------------------------------------------------------------------------------------
template<typename TPR, typename TPAx = TPR, typename TPTh = TPAx>
inline void SSPN_Cmn_3DPoint__GetRotMtxT_RotatePoint(const SSPN_Cmn_3DPoint<TPAx>& PUnitVectAxis,//unit vector as rotating axis, which represented as a SSPN_Cmn_3DPoint<TP> object 
													TPTh thet,									//rotating angle
													BOOL bDegree,								//denote the unit of thet: 0-radian/1-degree
													SPN_Cmn_Matrix<TPR>& RT)						//output;Transpose of the Rotating matrix; 
																								//Note: for speed consideration, RT rather than R is returned, which different from the format in the BOOK;
{
	SSPN_Cmn_3DPoint__GetRotMtxT_RotateCoordSys(PUnitVectAxis, -thet, bDegree, RT);
}
//--------------------------------------------------------------------------------------------------------------------
template<typename TPR, typename TP1>
inline void SSPN_Cmn_3DPoint__GetRotMtxT_RotateCoordSys_StretchAllow_No(SPN_Cmn_Matrix<TPR>& RT,
																	   const SSPN_Cmn_3DPoint<TP1>& sP3_X_Dst,
																	   const SSPN_Cmn_3DPoint<TP1>& sP3_Y_Dst,
																	   const SSPN_Cmn_3DPoint<TP1>& sP3_Z_Dst)//[11_14 10:14:06 ]:
{
	RT.SetSize(3, 3);

	SSPN_Cmn_3DPoint<TP1> Vx = sP3_X_Dst.GetUnitVect/*<TPFLT>*/();
	SSPN_Cmn_3DPoint<TP1> Vy = sP3_Y_Dst.GetUnitVect/*<TPFLT>*/();
	SSPN_Cmn_3DPoint<TP1> Vz = sP3_Z_Dst.GetUnitVect/*<TPFLT>*/();

	RT[0][0] = Vx[0];
	RT[1][0] = Vx[1];
	RT[2][0] = Vx[2];

	RT[0][1] = Vy[0];
	RT[1][1] = Vy[1];
	RT[2][1] = Vy[2];

	RT[0][2] = Vz[0];
	RT[1][2] = Vz[1];
	RT[2][2] = Vz[2];
};
template<typename TPR, typename TP1>
inline void SSPN_Cmn_3DPoint__GetRotMtxT_RotateCoordSys_StretchAllow_Yes(SPN_Cmn_Matrix<TPR>& RT,
																		const SSPN_Cmn_3DPoint<TP1>& sP3_X_Dst,
																		const SSPN_Cmn_3DPoint<TP1>& sP3_Y_Dst,
																		const SSPN_Cmn_3DPoint<TP1>& sP3_Z_Dst)//[11_14 10:14:06 ]:
{
	RT.SetSize(3, 3);

	RT[0][0] = sP3_X_Dst[0];
	RT[1][0] = sP3_X_Dst[1];
	RT[2][0] = sP3_X_Dst[2];

	RT[0][1] = sP3_Y_Dst[0];
	RT[1][1] = sP3_Y_Dst[1];
	RT[2][1] = sP3_Y_Dst[2];

	RT[0][2] = sP3_Z_Dst[0];
	RT[1][2] = sP3_Z_Dst[1];
	RT[2][2] = sP3_Z_Dst[2];
};

//*******************************************************************************************
//���������ʵ��ͼ�ε��㷨������P.127:����������Ľ�
// for this MLCTPS project:
//    just one intersection point is needed. 
template<typename TPR, typename TPFLT = TPR>
inline BOOL SSPN_Cmn_3DPoint__IntersectLineAndSphere_PointIn(const SSPN_Cmn_3DPoint<TPFLT>& PC,
															const TPFLT  R,
															const SSPN_Cmn_3DPoint<TPFLT>& PA,
															const SSPN_Cmn_3DPoint<TPFLT>& PB,
															SSPN_Cmn_3DPoint<TPR>& P)
{
	/*
	3D parameter line equation:			|	sphere equation:
		x=a+ut							|		(x-PC.x)**2 + (y-PC.y)**2 +(z-PC.z)**2=R**2
		y=b+vt							|
		z=c+wt							|

	  => At**2+Bt+C=0;
	  => t=...
	  => (x,y,z)=(...);
	*/
	TPFLT 	u = PB.x() - PA.x();
	TPFLT	v = PB.y() - PA.y();
	TPFLT	w = PB.z() - PA.z();

	TPFLT	a = PA.x();
	TPFLT	b = PA.y();
	TPFLT	c = PA.z();

	TPFLT	dxa = a - PC[0];
	TPFLT	dya = b - PC[1];
	TPFLT	dza = c - PC[2];

	TPFLT	A = u * u + v * v + w * w;
	TPFLT	B0 = (u*dxa + v * dya + w * dza);
	TPFLT	C = dxa * dxa + dya * dya + dza * dza - R * R;

	TPFLT	B = B0 + B0;

	TPFLT	Judge = B * B - 4 * A*C;

	TPFLT t;
	if (FLT_EQ(0, Judge))//just one intersection point
		t = -B / (A + A);
	else if (Judge < 0)//no intersection point
		return FALSE;
	else
	{
		t = (-B + pow(Judge, 0.5)) / (A + A);//abandon t=(-B-root)/(2*A) directly, because of A>0//!!!!!!Special for my use.
		if (t > 1)//The intersection point is out of the line section.//!!!!!!Special for my use.
			return FALSE;
	}

	//calculate the intersection point:
	P[0] = a + u * t;
	P[1] = b + v * t;
	P[2] = c + w * t;

	return TRUE;
};
//------------------------------------------------------------------------------
template<typename TPR, typename TPFLT = TPR>
inline BOOL SSPN_Cmn_3DPoint__IntersectLineAndSphere_PointOut(const SSPN_Cmn_3DPoint<TPFLT>& PC,
															 const TPFLT R,
															 const SSPN_Cmn_3DPoint<TPFLT>& PA,
															 const SSPN_Cmn_3DPoint<TPFLT>& PB,
															 SSPN_Cmn_3DPoint<TPR>& P)//
{
	/*
	3D parameter line equation:			|	sphere equation:
		x=a+ut							|		(x-PC.x)**2 + (y-PC.y)**2 +(z-PC.z)**2=R**2
		y=b+vt							|
		z=c+wt							|

	  => At**2+Bt+C=0;
	  => t=...
	  => (x,y,z)=(...);
	*/
	TPFLT	u = PB[0] - PA[0];
	TPFLT	v = PB[1] - PA[1];
	TPFLT	w = PB[2] - PA[2];

	TPFLT 	a = PA[0];
	TPFLT 	b = PA[1];
	TPFLT 	c = PA[2];

	TPFLT 	dxa = a - PC[0];
	TPFLT 	dya = b - PC[1];
	TPFLT 	dza = c - PC[2];

	TPFLT 	A = u * u + v * v + w * w;
	TPFLT 	B0 = u * dxa + v * dya + w * dza;
	TPFLT 	C = dxa * dxa + dya * dya + dza * dza - R * R;

	TPFLT 	B = B0 + B0;

	TPFLT	Judge = B * B - 4 * A*C;

	TPFLT t;
	if (Judge < 0)//no intersection point
		return FALSE;
	else if (0 == Judge)//just one intersection point
		t = -B / (A + A);
	else
		t = (-B - pow(Judge, 0.5)) / (A + A);//abandon t=(-B+root)/(2*A) directly, because of A>0//!!!!!!Special for my use.

	//calculate the intersection point:
	P[0] = a + u * t;
	P[1] = b + v * t;
	P[2] = c + w * t;

	return TRUE;
}
//------------------------------------------------------------------------------
template<typename TPR, typename TPFLT>
inline void SSPN_Cmn_3DPoint__IntersectLineAndPlane(const SSPN_Cmn_3DPoint<TPFLT>& NormVect,//normline of the plane
												   const SSPN_Cmn_3DPoint<TPFLT>& pointP,  //point on the plane
												   const SSPN_Cmn_3DPoint<TPFLT>& pointA,  //point A to define the line
												   const SSPN_Cmn_3DPoint<TPFLT>& pointB,  //point B to defint the line 
												   SSPN_Cmn_3DPoint<TPR>& pointI)  //point of intersection
{
	::IntersectLineAndPlane(NormVect[0], NormVect[1], NormVect[2],
							pointP[0], pointP[1], pointP[2],
							pointA[0], pointA[1], pointA[2],
							pointB[0], pointB[1], pointB[2],
							pointI[0], pointI[1], pointI[2]);
};

//template<typename TP>
//struct SSPN_Cmn_3DPoint
//{
//	SSPN_Cmn_3DPoint()
//	{
//		Zero();
//	};
//
//	void Zero()
//	{
//		::memset(m_arr_XYZ, 0, 3 * sizeof(TP));
//	};
//
//	SSPN_Cmn_3DPoint(const SSPN_Cmn_3DPoint<TP>& P3D)
//	{
//		*this = P3D;
//	};
//
//	SSPN_Cmn_3DPoint(const TP* pTp3D)
//	{
//		Construct(pTp3D);
//	};
//
//	inline void Construct(const TP* pTp3D)
//	{
//		m_arr_XYZ[0] = pTp3D[0];
//		m_arr_XYZ[1] = pTp3D[1];
//		m_arr_XYZ[2] = pTp3D[2];
//	};
//
//	inline SSPN_Cmn_3DPoint<TP>& operator=(const SSPN_Cmn_3DPoint<TP>& P3D)
//	{
//		::std::memcpy(m_arr_XYZ, P3D.m_arr_XYZ, 3 * sizeof(TP));
//		return *this;
//	};
//
//	inline TP operator[](unsigned int iDim) const
//	{
//		assert(iDim < 3);
//		return m_arr_XYZ[iDim];
//	};
//
//	inline TP& operator[](unsigned int iDim)
//	{
//		assert(iDim < 3);
//		return m_arr_XYZ[iDim];
//	};
//
//	inline bool operator==(const SSPN_Cmn_3DPoint<TP>& P3D) const
//	{
//		return
//			DBL_EQ(m_arr_XYZ[0], P3D[0]) &&
//			DBL_EQ(m_arr_XYZ[1], P3D[1]) &&
//			DBL_EQ(m_arr_XYZ[2], P3D[2]);
//	};
//
//

template<typename TPR, typename TP1 = TPR, typename TP2 = TP1>
inline TPR SSPN_Cmn_3DPoint__GetDistTo_Sq(const SSPN_Cmn_3DPoint<TP1>& P3DA, const SSPN_Cmn_3DPoint<TP2>& P3DB)
{
	double fDX = P3DA[0] - P3DB[0];
	double fDY = P3DA[1] - P3DB[1];
	double fDZ = P3DA[2] - P3DB[2];

	return fDX * fDX + fDY * fDY + fDZ * fDZ;
};

template<typename TPR, typename TP1 = TPR, typename TP2 = TP1>
inline TPR SSPN_Cmn_3DPoint__GetDistTo(const SSPN_Cmn_3DPoint<TP1>& P3DA, const SSPN_Cmn_3DPoint<TP2>& P3DB)
{
	double fDstSq = SSPN_Cmn_3DPoint__GetDistTo_Sq<TPR, TP2, TP2>(P3DA, P3DB);
	double fDst = sqrt(fDstSq);
	return fDst;
};

template<typename TP>
inline double SSPN_Cmn_3DPoint<TP>::GetDistTo(const SSPN_Cmn_3DPoint<TP>& P3DB) const
{
	return SSPN_Cmn_3DPoint__GetDistTo<double, TP, TP>(*this, P3DB);
};

template<typename TP>
inline double SSPN_Cmn_3DPoint<TP>::GetDistTo_Sq(const SSPN_Cmn_3DPoint<TP>& P3DB) const
{
	return SSPN_Cmn_3DPoint__GetDistTo_Sq<double, TP, TP>(*this, P3DB);
};
//
//	inline TP* GetDataBuf(){ return m_arr_XYZ; };
//
//protected:
//	TP m_arr_XYZ[3];
//};

template<> inline BOOL SSPN_Cmn_3DPoint<double>::IsFullZero() const
{
	return
		DBL_EQ(m_arr_XYZ[0], 0) &&
		DBL_EQ(m_arr_XYZ[1], 0) &&
		DBL_EQ(m_arr_XYZ[2], 0);
};

template<> inline BOOL SSPN_Cmn_3DPoint<float>::IsFullZero() const
{
	return
		FLT_EQ(m_arr_XYZ[0], 0) &&
		FLT_EQ(m_arr_XYZ[1], 0) &&
		FLT_EQ(m_arr_XYZ[2], 0);
};

template<typename TP>
inline BOOL SSPN_Cmn_3DPoint<TP>::IsFullZero() const
{
	return
		(0 == m_arr_XYZ[0]) &&
		(0 == m_arr_XYZ[1]) &&
		(0 == m_arr_XYZ[2]);
};


typedef SSPN_Cmn_3DPoint<int>			SPnt3D_Int;
typedef SSPN_Cmn_3DPoint<unsigned int>	SPnt3D_UInt;

typedef SSPN_Cmn_3DPoint<short>			SPnt3D_Sht;
typedef SSPN_Cmn_3DPoint<unsigned short>	SPnt3D_USht;

typedef SSPN_Cmn_3DPoint<char>			SPnt3D_Char;
typedef SSPN_Cmn_3DPoint<unsigned char>	SPnt3D_UChar;

typedef SSPN_Cmn_3DPoint<float>			SPnt3D_Flt;
typedef SSPN_Cmn_3DPoint<double>			SPnt3D_Dbl;

typedef SSPN_Cmn_3DPoint<int>			SPnt3D_Idx;

template<typename TPDst, typename TPSrc>
inline void Eq_Pnt3D_to(SSPN_Cmn_3DPoint<TPDst>& P3DDst, const SSPN_Cmn_3DPoint<TPSrc>& P3DSrc)
{
	P3DDst[0] = P3DSrc[0];
	P3DDst[1] = P3DSrc[1];
	P3DDst[2] = P3DSrc[2];
};

//[20210802_15:06:20 ]:
/***********************************************************************************************
*****
*****	��R = A (op) B ˫Ԫ����ģ�塿
*****	��֧�� R<TR> = A<TA> (op) B<TB> 3��ģ��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*****	��֧�� R<TR> = A<TR> (op) B<TB> 2��ģ��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*****	������������뷵�ؽ�����빲����ͬģ�� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*****
************************************************************************************************/

template<typename TPR, typename TPPnt>
inline SSPN_Cmn_3DPoint<TPR> operator*(TPR vNum, const SSPN_Cmn_3DPoint<TPPnt>& Point)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(vNum * Point[0], vNum * Point[1], vNum * Point[2]);
	return PointDst;
};

template<typename TPR, typename TPNum>
inline SSPN_Cmn_3DPoint<TPR> operator*(const SSPN_Cmn_3DPoint<TPR>& Point, TPNum vNum)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(vNum * Point[0], vNum * Point[1], vNum * Point[2]);
	return PointDst;
};


template<typename TPR, typename TPNum>
inline SSPN_Cmn_3DPoint<TPR> operator/(const SSPN_Cmn_3DPoint<TPR>& Point, TPNum vNum)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	assert(!FLT_EQ(vNum, 0.0f));
	PointDst.Construct(Point[0] / vNum, Point[1] / vNum, Point[2] / vNum);
	return PointDst;
};

template<typename TPR, typename TPPnt>
inline SSPN_Cmn_3DPoint<TPR> operator/(TPR vNum, const SSPN_Cmn_3DPoint<TPPnt>& Point)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(vNum / Point[0], vNum / Point[1], vNum / Point[2]);
	return PointDst;
};

//*****	�����vNum(op+-)Point �� Point(op+-)Point �������, ��vNum��������, ֻ��֧����Point<TP>��ͬTPģ��!

template<typename TPR>
inline SSPN_Cmn_3DPoint<TPR> operator+(const SSPN_Cmn_3DPoint<TPR>& Point, TPR vNum)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(Point[0] + vNum, Point[1] + vNum, Point[2] + vNum);
	return PointDst;
};

template<typename TPR>
inline SSPN_Cmn_3DPoint<TPR> operator+(TPR vNum, const SSPN_Cmn_3DPoint<TPR>& Point)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(Point[0] + vNum, Point[1] + vNum, Point[2] + vNum);
	return PointDst;
};

template<typename TPR>
inline SSPN_Cmn_3DPoint<TPR> operator-(const SSPN_Cmn_3DPoint<TPR>& Point, TPR vNum)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(Point[0] - vNum, Point[1] - vNum, Point[2] - vNum);
	return PointDst;
};

template<typename TPR>
inline SSPN_Cmn_3DPoint<TPR> operator-(TPR vNum, const SSPN_Cmn_3DPoint<TPR>& Point)
{
	SSPN_Cmn_3DPoint<TPR> PointDst;
	PointDst.Construct(vNum - Point[0], vNum - Point[1], vNum - Point[2]);
	return PointDst;
};

template<typename TP>
class CSPN_Cmn_3DPoint : public SSPN_Cmn_3DPoint<TP>
{
	//Constructor/destructor:
public:
	CSPN_Cmn_3DPoint();

	CSPN_Cmn_3DPoint(TP dx, TP dy, TP dz);
	/*explicit*/ CSPN_Cmn_3DPoint(const TP pTP3D[3]) { x(pTP3D[0]);	y(pTP3D[1]);	z(pTP3D[2]); };

	//[11_30 5:38:12 ]: explicit CSPN_Cmn_3DPoint(CSPN_Cmn_2DPoint<TP> P2D)		{ x(P2D.x());	y(P2D.y());		z(TP(0));	 };
	CSPN_Cmn_3DPoint(CSPN_Cmn_2DPoint<TP> P2D, TP vZ = 0) { this->x(P2D.x());	this->y(P2D.y());		this->z(vZ); };
	CSPN_Cmn_3DPoint(const CSPN_Cmn_3DPoint<TP>& P3D) { this->x(P3D.x());	this->y(P3D.y());		this->z(P3D.z()); };//[11_30 5:32:48 ]:

	//[11_30 5:24:13 ]: explicit CSPN_Cmn_3DPoint(const CPointInt& P)						{ x(P.x); 		y(P.y);			z(TP(0));	 };
	CSPN_Cmn_3DPoint(const CPointInt& P, TP vZ) { this->x(P.x); 		this->y(P.y);			this->z(vZ); };

	CSPN_Cmn_3DPoint(const SSPN_Cmn_3DPoint<TP>& sP3D) { (SSPN_Cmn_3DPoint<TP>&)(*this) = sP3D; };

	inline const SSPN_Cmn_3DPoint<TP>&	operator=(TP tpV) { this->Construct(tpV, tpV, tpV);	return *this; };

	const SSPN_Cmn_3DPoint<TP>&			operator=(const SSPN_Cmn_3DPoint<TP>& sP3D) { (SSPN_Cmn_3DPoint<TP>&)(*this) = sP3D;	return *this; };
};

//------------------------------------------------------------------------------
//template<typename TPR, typename TP2>
//inline CSPN_Cmn_3DPoint<TPR> operator+(const CSPN_Cmn_3DPoint<TPR>& P1, const CSPN_Cmn_3DPoint<TP2>& P2)
//{
//	CSPN_Cmn_3DPoint<TPR> sP3R;
//	sP3R.Construct(P1.x() + P2.x(), P1.y() + P2.y(), P1.z() + P2.z());
//	return sP3R;
//};
////------------------------------------------------------------------------------
//template<typename TPR, typename TP2>
//inline CSPN_Cmn_3DPoint<TPR> operator-(const CSPN_Cmn_3DPoint<TPR>& P1, const CSPN_Cmn_3DPoint<TP2>& P2)
//{
//	return CSPN_Cmn_3DPoint<TP>(P1.x() - P2.x(), P1.y() - P2.y(), P1.z() - P2.z());
//};

//------------------------------------------------------------------------------
template<typename TP>
CSPN_Cmn_3DPoint<TP>::CSPN_Cmn_3DPoint()
{
	this->m_arr_XYZ[0] = 0;
	this->m_arr_XYZ[1] = 0;
	this->m_arr_XYZ[2] = 0;
};

template<typename TP>
CSPN_Cmn_3DPoint<TP>::CSPN_Cmn_3DPoint(TP fx, TP fy, TP fz)
{
	this->x(fx);
	this->y(fy);
	this->z(fz);
};

typedef CSPN_Cmn_3DPoint<int>			Pnt3D_Int;
typedef CSPN_Cmn_3DPoint<unsigned int>	Pnt3D_UInt;

typedef CSPN_Cmn_3DPoint<short>			Pnt3D_Sht;
typedef CSPN_Cmn_3DPoint<unsigned short>	Pnt3D_USht;

typedef CSPN_Cmn_3DPoint<char>			Pnt3D_Char;
typedef CSPN_Cmn_3DPoint<unsigned char>	Pnt3D_UChar;

typedef CSPN_Cmn_3DPoint<float>			Pnt3D_Flt;
typedef CSPN_Cmn_3DPoint<double>			Pnt3D_Dbl;

typedef CSPN_Cmn_3DPoint<int>			Pnt3D_Idx;

//------------------------------------------------------------------------------
#endif //  // !defined(SPN_Cmn_3DPoint_H__INCLUDED_