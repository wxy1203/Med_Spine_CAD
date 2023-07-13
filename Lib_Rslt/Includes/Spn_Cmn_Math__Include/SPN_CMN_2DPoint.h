// SPN_Cmn_2DPoint.h: interface for the SSPN_Cmn_2DPoint<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_2DPoint_H__INCLUDED_
#define SPN_Cmn_2DPoint_H__INCLUDED_

#include <vector>
#include "stdio.h"
////#include "afx.h"
//[9_17 16:11:27 ]:#include "TCHAR.h"
//[9_17 16:11:27 ]:#include "CTYPE.H"
////#include <afxcoll.h>
//#include "_From_MFC_afxtempl.h"//#include <From_MFC_afxtempl.h>
#include "_From_MFC_afxtempl.h"
////#include <fstream.h>

#include "SPN_Cmn_Science.h"
#include "SPN_Cmn_CArray.h"
#include "SPN_Cmn_2DSize.h"

#	pragma once

const float CONST_FLT_LINE_INTERSECT_TOL = FLT_EPSILON * 10.f;

template<class TP>
class SSPN_Cmn_2DPoint
{
public:
	inline const SSPN_Cmn_2DPoint<TP>&  operator=(double fV) { (*this).x(fV); (*this).y(fV); return *this; };

	//template<typename TPVal>
	//inline const SSPN_Cmn_2DPoint<TP>&  operator=(TPVal vX, TPVal vY) { (*this).x(vX); (*this).y(vY); return *this};

	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const SSPN_Cmn_2DPoint<TP>& P2D) { (*this).x(P2D.x());	(*this).y(P2D.y());	return *this; };

	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const QPoint& P2D) { (*this).x(P2D.x());	(*this).y(P2D.y());	return *this; };
	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const QPointF& P2D) { (*this).x(P2D.x());	(*this).y(P2D.y());	return *this; };

public:
	void Construct(TP fx, TP fy);

	inline SSPN_Cmn_2DPoint<short> ToShort() const//[11_13 22:23:43 ]: 
	{
		SSPN_Cmn_2DPoint<short> P2;
		P2[0] = fRound(this->m_arrf2D[0]);
		P2[1] = fRound(this->m_arrf2D[1]);
		return P2;
	};

	inline SSPN_Cmn_2DPoint<int> ToInt() const//[11_13 22:23:43 ]: 
	{
		SSPN_Cmn_2DPoint<int> P2;
		P2[0] = fRound(this->m_arrf2D[0]);
		P2[1] = fRound(this->m_arrf2D[1]);
		return P2;
	};

	inline SSPN_Cmn_2DPoint<float> ToFloat() const//[11_13 22:23:43 ]: 
	{
		SSPN_Cmn_2DPoint<float> P2f;
		P2f[0] = this->m_arrf2D[0];
		P2f[1] = this->m_arrf2D[1];
		return P2f;
	};

	inline SSPN_Cmn_2DPoint<double> ToDouble() const//[11_13 22:23:50 ]: 
	{
		SSPN_Cmn_2DPoint<double> P2f;
		P2f[0] = this->m_arrf2D[0];
		P2f[1] = this->m_arrf2D[1];
		return P2f;
	};

	QPoint	To_QPoint()	  const { return QPoint((*this).x(), (*this).y()); };
	QPointF To_QPointF()  const { return QPointF((*this).x(), (*this).y()); };

	//Attritutes:
public:
	static inline int	GetCount_SubDim() { return 2; };
	TP&			operator[](int i);
	const TP&	operator[](int i) const;

	const TP&	x()	const;
	const TP&	y()	const;

	inline TP&	x() { return this->m_arrf2D[0]; };
	inline TP&	y() { return this->m_arrf2D[1]; };

	void x(TP fx);
	void y(TP fy);

	TP GetVectLength() const;
	TP GetVectLengthSq() const;

	TP	GetDistTo(const CPointInt& P) const;
	TP	GetDistTo(const SSPN_Cmn_2DPoint<TP>& P, CSPN_Cmn_2DSize<TP> const* pUnitFlt) const;
	TP	GetDistTo(const SSPN_Cmn_2DPoint<TP>& P) const;
	TP	GetDistTo_Sq(const SSPN_Cmn_2DPoint<TP>& P) const;

	BOOL IsPointNearPoint(const SSPN_Cmn_2DPoint<TP>& P, TP fTol) const;
	BOOL IsPointNearLine(const SSPN_Cmn_2DPoint<TP>& P1, const SSPN_Cmn_2DPoint<TP>& P2, const TP fTol) const;

	//CPointInt Get_CPoint () const;

//Calculations:
public:
	void Construct(const CPointInt& P) { this->m_arrf2D[0] = P.x; this->m_arrf2D[1] = P.y; };
	void operator += (const SSPN_Cmn_2DPoint<TP>& P);
	void operator -= (const SSPN_Cmn_2DPoint<TP>& P);
	void operator *= (double fK);//[1_17 10:40:06 ]:(TP fK);
	void operator /= (double fK);//[1_17 10:40:14 ]:(TP fK);

	void operator += (const TP fV) { this->m_arrf2D[0] += fV;  this->m_arrf2D[1] += fV; };
	void operator -= (const TP fV) { this->m_arrf2D[0] -= fV;  this->m_arrf2D[1] -= fV; };

	SSPN_Cmn_2DPoint<TP> NegPoint(const SSPN_Cmn_2DPoint<TP>& P) const;

	BOOL operator> (const SSPN_Cmn_2DPoint<TP>& P2) const;
	BOOL operator< (const SSPN_Cmn_2DPoint<TP>& P2) const;
	BOOL operator==(const SSPN_Cmn_2DPoint<TP>& P2) const;
	BOOL operator!=(const SSPN_Cmn_2DPoint<TP>& P2) const;
	BOOL operator>=(const SSPN_Cmn_2DPoint<TP>& P2) const;
	BOOL operator<=(const SSPN_Cmn_2DPoint<TP>& P2) const;

	bool IsEqualTo(const SSPN_Cmn_2DPoint<TP>& Pnt) const
	{
		return *this == Pnt;
	};

	//member function:
public:
	int Compare(const SSPN_Cmn_2DPoint<TP>& P2) const;

	static void SetSortKey(int iSortKey);
	static BOOL IsSortKey(int iSortKey);
	static int  GetSortKey();

	//friend ::ofstream& operator<<(::ofstream &stream,const SSPN_Cmn_2DPoint<TP>& P);
	//friend ::ifstream& operator>>(::ifstream &stream,SSPN_Cmn_2DPoint<TP>& P);
	//void Serialize(CSPN_Cmn_Archive& ar);

	//static:
public:
	static void InsertPoint(SSPN_Cmn_2DPoint<TP>& pointBgn,
							SSPN_Cmn_2DPoint<TP>& pointEnd,
							CSPN_Cmn_CArray<SSPN_Cmn_2DPoint<TP>, SSPN_Cmn_2DPoint<TP>&>& ArrPoint,
							int nSect,
							TP  dx,
							TP  dy);

	//��;:	��ѡһ���Ҵ�ֵ����������ͬ�㣻������Y��ƽ��ʱ������xֵ��Ľ��㣬����Y
	static const SSPN_Cmn_2DPoint<TP>& Max2D_XFirst(const SSPN_Cmn_2DPoint<TP>& P1,	//	�Ƚϵĵ�һ��ֵ
												   const SSPN_Cmn_2DPoint<TP>& P2,	//	�Ƚϵĵڶ���ֵ
												   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  ������ȱȽ�ʱ�����ݲ�

   //��;:	��ѡһ����Сֵ����������ͬ�㣻������Y��ƽ��ʱ������xֵС�Ľ��㣬����Y
	static const SSPN_Cmn_2DPoint<TP>& Min2D_XFirst(const SSPN_Cmn_2DPoint<TP>& P1,	//	�Ƚϵĵ�һ��ֵ
												   const SSPN_Cmn_2DPoint<TP>& P2,	//	�Ƚϵĵڶ���ֵ
												   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  ������ȱȽ�ʱ�����ݲ�

#ifdef _DEBUG
	//void AssertValid(SSPN_Cmn_2DPoint<TP>& P);
	//void TraceFmt(std::string& StrTrace) const;
#endif // 

//data member:
	TP* GetDataBuf()
	{
		return this->m_arrf2D;
	};
	const TP* GetDataBuf() const
	{
		return this->m_arrf2D;
	};

protected:
	TP			m_arrf2D[2];
	static int	m_iSortKey;
};
//**************************************************************************************************
//--------------------------------------------------------------------------------------------------
template<class TP>
void SSPN_Cmn_2DPoint<TP>::Construct(TP fx, TP fy)
{
	x(fx);
	(*this).y(fy);
}
//--------------------------------------------------------------------------------------------------
//template<class TP> 
//inline CPointInt SSPN_Cmn_2DPoint<TP>::Get_CPoint() const 
//{
//	return CPointInt(this->m_arrf2D[0], this->m_arrf2D[1]); 
//};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::IsPointNearPoint(const SSPN_Cmn_2DPoint<TP>& P, TP fTol) const
{
	return GetDistTo(P) < fTol;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::SetSortKey(int iSortKey)
{
	m_iSortKey = iSortKey % 2;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline int SSPN_Cmn_2DPoint<TP>::GetSortKey()
{
	return m_iSortKey;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::IsSortKey(int iSortKey)
{
	if (iSortKey == m_iSortKey)
		return TRUE;
	else
		return FALSE;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline int SSPN_Cmn_2DPoint<TP>::Compare(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	if ((*this) == P2)
		return 0;
	if (*this < P2)
		return -1;
	else
		return 1;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetDistTo(const CPointInt& P) const
{
	TP dx = P.x - (*this).x();
	TP dy = P.y - (*this).y();
	return sqrt(dx*dx + dy * dy);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetDistTo(const SSPN_Cmn_2DPoint<TP>& P) const
{
	TP dx = P.x() - (*this).x();
	TP dy = P.y() - (*this).y();
	return sqrt(dx*dx + dy * dy);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetDistTo_Sq(const SSPN_Cmn_2DPoint<TP>& P) const
{
	TP dx = P.x() - (*this).x();
	TP dy = P.y() - (*this).y();
	return (dx*dx + dy * dy);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetDistTo(const SSPN_Cmn_2DPoint<TP>& P, CSPN_Cmn_2DSize<TP> const* pUnitFlt) const
{
	TP dx = P.x() - (*this).x();
	TP dy = P.y() - (*this).y();

	if (pUnitFlt)
	{
		dx *= (*pUnitFlt)[0];
		dy *= (*pUnitFlt)[1];
	}
	return sqrt(dx*dx + dy * dy);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetVectLength()const
{
	return (TP)sqrt((*this).x()*x() + (*this).y()*y());
};

template<class TP>
inline TP SSPN_Cmn_2DPoint<TP>::GetVectLengthSq()const
{
	return (*this).x()*x() + (*this).y()*y();
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline SSPN_Cmn_2DPoint<TP> operator +(const SSPN_Cmn_2DPoint<TP>& P1, const SSPN_Cmn_2DPoint<TP>& P2)
{
	SSPN_Cmn_2DPoint<TP> sP2D;
	sP2D.x() = P1.x() + P2.x();
	sP2D.y() = P1.y() + P2.y();

	return sP2D;
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline SSPN_Cmn_2DPoint<TP> operator -(const SSPN_Cmn_2DPoint<TP>& P1, const SSPN_Cmn_2DPoint<TP>& P2)
{
	SSPN_Cmn_2DPoint<TP> sP2D;
	sP2D.x() = P1.x() - P2.x();
	sP2D.y() = P1.y() - P2.y();

	return sP2D;
}
//--------------------------------------------------------------------------------------------------
template<class TP> inline
SSPN_Cmn_2DPoint<TP> operator *(const SSPN_Cmn_2DPoint<TP>& P, const TP fK)
{
	return SSPN_Cmn_2DPoint<TP>(P.x()*fK, P.y()*fK);
}
//--------------------------------------------------------------------------------------------------
template<class TP> inline
SSPN_Cmn_2DPoint<TP> operator /(const SSPN_Cmn_2DPoint<TP>& P, const TP fK)
{
	assert(!FLT_EQ(fK, 0.0f));
	return SSPN_Cmn_2DPoint<TP>(P.x() / fK, P.y() / fK);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template<class TP>
inline SSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DPoint<TP>::NegPoint(const SSPN_Cmn_2DPoint<TP> &P) const
{
	SSPN_Cmn_2DPoint<TP> sP2D;
	sP2D.x() = -this->m_arrf2D[0];
	sP2D.y() = -this->m_arrf2D[1];

	return sP2D;
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::operator +=(const SSPN_Cmn_2DPoint<TP> &P)
{
	this->m_arrf2D[0] += P.x();
	this->m_arrf2D[1] += P.y();
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::operator -=(const SSPN_Cmn_2DPoint<TP> &P)
{
	this->m_arrf2D[0] -= P.x();
	this->m_arrf2D[1] -= P.y();
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::operator *=(double fK)
{
	this->m_arrf2D[0] *= fK;
	this->m_arrf2D[1] *= fK;
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::operator /=(double fK)
{
	assert(!FLT_EQ(fK, 0.0f));
	this->m_arrf2D[0] /= fK;
	this->m_arrf2D[1] /= fK;
}
//--------------------------------------------------------------------------------------------------
template<class TP>
inline const TP& SSPN_Cmn_2DPoint<TP>::x() const
{
	return this->m_arrf2D[0];
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline const TP& SSPN_Cmn_2DPoint<TP>::y() const
{
	return this->m_arrf2D[1];
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::x(TP fx)
{
	this->m_arrf2D[0] = fx;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::y(TP fy)
{
	this->m_arrf2D[1] = fy;
};
//--------------------------------------------------------------------------------------------------
//Assume the the point as TP array that hold two member; It's easy for cycle:
template<class TP>
inline TP& SSPN_Cmn_2DPoint<TP>::operator[](int i)
{
	assert(i >= 0 && i < 2);
	return this->m_arrf2D[i];
};
//--------------------------------------------------------------------------------------------------
//Assume the the point as TP array that hold two member; It's easy for cycle:
template<class TP>
inline const TP& SSPN_Cmn_2DPoint<TP>::operator[](int i) const
{
	assert(i >= 0 && i < 2);
	return this->m_arrf2D[i];
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator>(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	if (IsSortKey(0))//x first and y second:
	{
		if ((*this).x() - P2.x() > FLT_EPSILON)
			return TRUE;
		else if ((*this).x() - P2.x() < -FLT_EPSILON)
			return FALSE;
		else if ((*this).y() - P2.y() > FLT_EPSILON)
			return TRUE;
		else
			return FALSE;
	}
	else//y first and x second:
	{
		if ((*this).y() - P2.y() > FLT_EPSILON)
			return TRUE;
		else if ((*this).y() - P2.y() < -FLT_EPSILON)
			return FALSE;
		else if ((*this).x() - P2.x() > FLT_EPSILON)
			return TRUE;
		else
			return FALSE;

	}
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator<(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	if (IsSortKey(0))//x first and y second:
	{
		if ((*this).x() - P2.x() < -FLT_EPSILON)
			return TRUE;
		else if ((*this).x() - P2.x() > FLT_EPSILON)
			return FALSE;
		else if ((*this).y() - P2.y() < -FLT_EPSILON)
			return TRUE;
		else
			return FALSE;
	}
	else//y first and x second:
	{
		if ((*this).y() - P2.y() < -FLT_EPSILON)
			return TRUE;
		else if ((*this).y() - P2.y() > FLT_EPSILON)
			return FALSE;
		else if ((*this).x() - P2.x() < -FLT_EPSILON)
			return TRUE;
		else
			return FALSE;
	}
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator==(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	if (FLT_EQ((*this).x(), P2.x()) && FLT_EQ((*this).y(), P2.y()))
		return TRUE;
	else
		return FALSE;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator != (const SSPN_Cmn_2DPoint<TP>& P2) const
{
	return !(*this == P2);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator>=(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	return !(*this < P2);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::operator<=(const SSPN_Cmn_2DPoint<TP>& P2) const
{
	return !(*this > P2);
};
//--------------------------------------------------------------------------------------------------
template<class TP>
int SSPN_Cmn_2DPoint<TP>::m_iSortKey = 0;//for sorting points;
//--------------------------------------------------------------------------------------------------
//template<class TP>
//inline void SSPN_Cmn_2DPoint<TP>::Serialize(CSPN_Cmn_Archive& ar)
//{
//	if (ar.IsStoring())
//	{
//		ar << this->m_arrf2D[0];
//		ar << this->m_arrf2D[1];
//	}
//	else
//	{
//		ar >> this->m_arrf2D[0];
//		ar >> this->m_arrf2D[1];
//	}
//};
//------------------------------------------------------------------------------
//template<class TP>
//::ifstream& operator>>(::ifstream &stream, SSPN_Cmn_2DPoint<TP>& P)
//{
//	stream>>P.this->m_arrf2D[0]>>P.this->m_arrf2D[1];
//	return stream;
//}
////------------------------------------------------------------------------------
//template<class TP>
//::ofstream& operator<<(::ofstream &stream, const SSPN_Cmn_2DPoint<TP>& P)
//{
//	stream<<P.this->m_arrf2D[0]<<P.this->m_arrf2D[1];
//	return stream;
//}
//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DPoint<TP>::IsPointNearLine(const SSPN_Cmn_2DPoint<TP>& P1, const SSPN_Cmn_2DPoint<TP>& P2, const TP fTol) const
{
	TP fDistP1P2 = P1.GetDistTo(P2);
	TP fDistP1P = GetDistTo(P1);
	TP fDistP2P = GetDistTo(P2);

	return fabs(fDistP1P + fDistP2P - fDistP1P2) < fTol;
};
//--------------------------------------------------------------------------------------------------
//Get a point array on a line section defined by the tow input points:
template<class TP>
inline void SSPN_Cmn_2DPoint<TP>::InsertPoint(SSPN_Cmn_2DPoint<TP>& pointBgn,
											 SSPN_Cmn_2DPoint<TP>& pointEnd,
											 CSPN_Cmn_CArray<SSPN_Cmn_2DPoint<TP>, SSPN_Cmn_2DPoint<TP>&>& ArrPoint,
											 int   nSect,
											 TP    dx,
											 TP    dy)
{
#ifdef _DEBUG
	assert((nSect > 0 && 0 == dx && 0 == dy)
			   || (0 == nSect && 0 != dx && 0 == dy)
			   || (0 == nSect && 0 == dx && 0 != dy));
	if (pointEnd[0] == pointBgn[0])
		assert(dx == 0);
	if (pointEnd[1] == pointBgn[1])
		assert(dy == 0);
#endif // 

	SSPN_Cmn_2DPoint pointMid;
	TP lengthX = pointEnd[0] - pointBgn[0];
	TP lengthY = pointEnd[1] - pointBgn[1];
	TP tmp;
	//calculate nSect, dx and dy:
	if (nSect > 0)
	{
		dx = lengthX / nSect;
		dy = lengthY / nSect;
	}
	else if (dx != 0)
	{
		nSect = ceil(fabs(lengthX / dx));
		tmp = fabs(dx / lengthX);
		dx = lengthX * tmp;
		dy = lengthY * tmp;
	}
	else
	{
		nSect = ceil(fabs(lengthY / dy));
		tmp = fabs(dy / lengthY);
		dy = lengthY * tmp;
		dx = lengthX * tmp;
	}

	//Calc the mid point and save them into the array:
	ArrPoint.SetSize(nSect + 1);
	int i;
	for (pointMid = pointBgn, i = 0; i < nSect; i++)
	{
		ArrPoint[i] = pointMid;
		pointMid[0] += dx;
		pointMid[1] += dy;
	}
	ArrPoint[nSect] = pointEnd;
};

//--------------------------------------------------------------------------------------------------

template<class TP>
const SSPN_Cmn_2DPoint<TP>& SSPN_Cmn_2DPoint<TP>::Max2D_XFirst(const SSPN_Cmn_2DPoint<TP>& P1,	//	�Ƚϵĵ�һ��ֵ
															 const SSPN_Cmn_2DPoint<TP>& P2,	//	�Ƚϵĵڶ���ֵ
															 TP fTol						//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(P1.x(), P2.x(), fTol))	//	��Y��ƽ��
	{
		return (P1.y() > P2.y()) ? P1 : P2;
	}
	else
	{
		return (P1.x() > P2.x()) ? P1 : P2;
	}
}

template<class TP>
const SSPN_Cmn_2DPoint<TP>& SSPN_Cmn_2DPoint<TP>::Min2D_XFirst(const SSPN_Cmn_2DPoint<TP>& P1,	//  �Ƚϵĵ�һ��ֵ
															 const SSPN_Cmn_2DPoint<TP>& P2,	//  �Ƚϵĵڶ���ֵ
															 TP fTol						//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(P1.x(), P2.x(), fTol))	//	��Y��ƽ��
	{
		return (P1.y() < P2.y()) ? P1 : P2;
	}
	else
	{
		return (P1.x() < P2.x()) ? P1 : P2;
	}
}

template<typename TPNum, typename TPPnt>
inline SSPN_Cmn_2DPoint<TPPnt> operator*(TPNum vNum, const SSPN_Cmn_2DPoint<TPPnt>& Pnt)
{
	SSPN_Cmn_2DPoint<TPPnt> PntDst(Pnt);
	PntDst *= vNum;
	return PntDst;
}

template<typename TPNum, typename TPPnt>
inline SSPN_Cmn_2DPoint<TPPnt> operator*(const SSPN_Cmn_2DPoint<TPPnt>& Pnt, TPNum vNum)
{
	SSPN_Cmn_2DPoint<TPPnt> PntDst(Pnt);
	PntDst *= vNum;
	return PntDst;
}

template<typename TPNum, typename TPPoint>
inline SSPN_Cmn_2DPoint<TPPoint> operator/(const SSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
{
	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
	PointDst /= vNum;
	return PointDst;
};

//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator+(const SSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst += vNum;
//	return PointDst;
//};

//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator+(TPNum vNum, const SSPN_Cmn_2DPoint<TPPoint>& Point)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst += vNum;
//	return PointDst;
//};

//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator-(const SSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst -= vNum;
//	return PointDst;
//};

//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator-(TPNum vNum, const SSPN_Cmn_2DPoint<TPPoint>& Point)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(vNum-Point[0], vNum-Point[1]);
//	return PointDst;
//};

typedef SSPN_Cmn_2DPoint<int>			SPnt2D_Int;
typedef SSPN_Cmn_2DPoint<unsigned int>	SPnt2D_UInt;

typedef SSPN_Cmn_2DPoint<short>			SPnt2D_Sht;
typedef SSPN_Cmn_2DPoint<unsigned short>	SPnt2D_USht;

typedef SSPN_Cmn_2DPoint<char>			SPnt2D_Char;
typedef SSPN_Cmn_2DPoint<unsigned char>	SPnt2D_UChar;

typedef SSPN_Cmn_2DPoint<float>			SPnt2D_Flt;
typedef SSPN_Cmn_2DPoint<double>			SPnt2D_Dbl;

typedef SSPN_Cmn_2DPoint<int>			SPnt2D_Idx;

//**************************************************************************************************

template<class TP>
class CSPN_Cmn_2DPoint : public SSPN_Cmn_2DPoint<TP>
{
public:
	CSPN_Cmn_2DPoint()
	{
		this->m_arrf2D[0] = 0;
		this->m_arrf2D[1] = 0;
	};

	CSPN_Cmn_2DPoint(TP fx, TP fy)
	{
		this->m_arrf2D[0] = fx;
		this->m_arrf2D[1] = fy;
	};

	//CSPN_Cmn_2DPoint(TP v)
	//{
	//	this->m_arrf2D[0] = v; 
	//	this->m_arrf2D[1] = v;
	//};

	explicit CSPN_Cmn_2DPoint(const TP*& pfXY)
	{
		x(pfXY[0]);
		(*this).y(pfXY[1]);
	};


	explicit CSPN_Cmn_2DPoint(const CPointInt& P)//copy constructor:
	{
		(*this).x(P.x);
		(*this).y(P.y);
	};

	CSPN_Cmn_2DPoint(const CSPN_Cmn_2DPoint<TP>& P2D)
	{
		(*this).x(P2D.x());
		(*this).y(P2D.y());
	};

	CSPN_Cmn_2DPoint(const SSPN_Cmn_2DPoint<TP>& sP2D)
	{
		(*this).x(sP2D.x());
		(*this).y(sP2D.y());
	};

	explicit CSPN_Cmn_2DPoint(const QPoint& QP) { (*this).x(QP.x());	(*this).y(QP.y()); };
	explicit CSPN_Cmn_2DPoint(const QPointF& QPF) { (*this).x(QPF.x());	(*this).y(QPF.y()); };

public:
	inline const SSPN_Cmn_2DPoint<TP>&  operator=(double fV) { (*(SSPN_Cmn_2DPoint<TP>*)(this)) = fV; return *this; };

	////template<typename TPVal>
	////inline const SSPN_Cmn_2DPoint<TP>&  operator=(TPVal vX, TPVal vY) { (*this).x(vX); (*this).y(vY); return *this};

	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const SSPN_Cmn_2DPoint<TP>& P2D) { (*(SSPN_Cmn_2DPoint<TP>*)(this)) = P2D; return *this; };

	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const QPoint& P2D) { (*(SSPN_Cmn_2DPoint<TP>*)(this)) = P2D; return *this; };
	inline const SSPN_Cmn_2DPoint<TP>&  operator=(const QPointF& P2D) { (*(SSPN_Cmn_2DPoint<TP>*)(this)) = P2D; return *this; };
};

//-------------------------------------------------------------------------------------------------

template<typename TPNum, typename TPPnt>
inline SSPN_Cmn_2DPoint<TPPnt> operator*(TPNum vNum, const CSPN_Cmn_2DPoint<TPPnt>& Pnt)
{
	SSPN_Cmn_2DPoint<TPPnt> PntDst = Pnt;
	PntDst *= vNum;
	return PntDst;
}

template<typename TPNum, typename TPPnt>
inline SSPN_Cmn_2DPoint<TPPnt> operator*(const CSPN_Cmn_2DPoint<TPPnt>& Pnt, TPNum vNum)
{
	SSPN_Cmn_2DPoint<TPPnt> PntDst = Pnt;
	PntDst *= vNum;
	return PntDst;
}

template<typename TPNum, typename TPPoint>
inline SSPN_Cmn_2DPoint<TPPoint> operator/(const CSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
{
	SSPN_Cmn_2DPoint<TPPoint> PointDst = Point;
	PointDst /= vNum;
	return PointDst;
};

//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator+(const SSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst += vNum;
//	return PointDst;
//};
//
//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator+(TPNum vNum, const SSPN_Cmn_2DPoint<TPPoint>& Point)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst += vNum;
//	return PointDst;
//};
//
//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator-(const SSPN_Cmn_2DPoint<TPPoint>& Point, TPNum vNum)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(Point);
//	PointDst -= vNum;
//	return PointDst;
//};
//
//template<typename TPNum, typename TPPoint>
//inline SSPN_Cmn_2DPoint<TPPoint> operator-(TPNum vNum, const SSPN_Cmn_2DPoint<TPPoint>& Point)
//{
//	SSPN_Cmn_2DPoint<TPPoint> PointDst(vNum - Point[0], vNum - Point[1]);
//	return PointDst;
//};
/***************************************************************************

����Bressenham�㷨, ������֪����֮��Ĺ�դ�߶��ϵĸ����ص��λ��

parameter	:	PntBgn -- �߶ε���ʼ������
				PntEnd -- �߶ε���ֹ������
***************************************************************************/

inline void MapLine_ToPixel(SPnt2D_Int PntBgn,
							SPnt2D_Int PntEnd,
							CArrayT<SPnt2D_Int, SPnt2D_Int&>& ArrPtOnLine)
{
	ArrPtOnLine.SetSize(0, 100);
	int x1 = PntBgn.x();
	int y1 = PntBgn.y();

	int x2 = PntEnd.x();
	int y2 = PntEnd.y();

	int Pixel_X = x1;
	int Pixel_Y = y1;

	int t1 = x2 - x1;
	int t2 = y2 - y1;
	int dx = abs(t1);
	int dy = abs(t2);
	int s1 = Compare(x2, x1);
	int s2 = Compare(y2, y1);//s1,s2�ֱ�ΪX��Y����Ĳ���ֵ��1��-1��

	int mark = 0;
	if (dy > dx)//�߶ε�б�ʵľ���ֵ����1,��mark=1���
	{
		int t = dx;
		dx = dy;
		dy = t;
		mark = 1;
	}

	int Determin = 2 * dy - dx;//�����ʼ���߲���
	for (int i = 1; i <= dx + 1; i++)
	{
		//��¼�߶��ϵ����ص�
		if (i != 1)// do not record the begin and end pixel-Point
		{
			SPnt2D_Int P; P.Construct(Pixel_X, Pixel_Y);
			ArrPtOnLine.Add(P);
		}
		//������߲�������һ�����ص��λ��	 
		if (Determin >= 0)
		{
			if (mark == 1)
				Pixel_X = Pixel_X + s1;
			else
				Pixel_Y = Pixel_Y + s2;
			Determin = Determin + 2 * (dy - dx);
		}
		else
			Determin = Determin + 2 * dy;

		if (mark == 1)
			Pixel_Y = Pixel_Y + s2;
		else
			Pixel_X = Pixel_X + s1;
	}
};
/***************************************************************************/


typedef CSPN_Cmn_2DPoint<int>			Pnt2D_Int;
typedef CSPN_Cmn_2DPoint<unsigned int>	Pnt2D_UInt;

typedef CSPN_Cmn_2DPoint<short>			Pnt2D_Sht;
typedef CSPN_Cmn_2DPoint<unsigned short>Pnt2D_USht;

typedef CSPN_Cmn_2DPoint<char>			Pnt2D_Char;
typedef CSPN_Cmn_2DPoint<unsigned char>	Pnt2D_UChar;

typedef CSPN_Cmn_2DPoint<float>			Pnt2D_Flt;
//#define Pnt2D_Flt CSPN_Cmn_2DPoint<float>

typedef CSPN_Cmn_2DPoint<double>		Pnt2D_Dbl;

typedef CSPN_Cmn_2DPoint<int>			Pnt2D_Idx;

//**************************************************************************************************
//**************************************************************************************************

#endif //  // !defined(SPN_Cmn_2DPoint_H__INCLUDED_
