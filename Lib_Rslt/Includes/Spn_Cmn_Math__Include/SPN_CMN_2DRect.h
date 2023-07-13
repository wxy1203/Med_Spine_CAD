// SPN_Cmn_2DRect.h: interface for the CSPN_Cmn_2DRect<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_2DRECT_H__INCLUDED_
#define SPN_Cmn_2DRECT_H__INCLUDED_

#pragma once

#include "SPN_Cmn_2DPoint.h"
#include <algorithm>

template<class TP>
class SSPN_Cmn_2DRect
{
	//Constructor/Destructor:
public:
	SSPN_Cmn_2DRect();
	SSPN_Cmn_2DRect(const TP xMin, const TP xMax, const TP yMin, const TP yMax);
	SSPN_Cmn_2DRect(const CSPN_Cmn_2DPoint<TP>& point1, const CSPN_Cmn_2DPoint<TP>& point2);
	SSPN_Cmn_2DRect(const CRectInt& rect);

	SSPN_Cmn_2DRect(const SSPN_Cmn_2DRect<TP>& rect);
	const SSPN_Cmn_2DRect<TP>& operator = (const SSPN_Cmn_2DRect<TP>& Rct2D);

public:
	explicit SSPN_Cmn_2DRect(const QRect&  Rct) { SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); };
	explicit SSPN_Cmn_2DRect(const QRectF& Rct) { SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); };
	const SSPN_Cmn_2DRect<TP>& operator  =	(const QRect&  Rct) { SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); return *this; };
	const SSPN_Cmn_2DRect<TP>& operator  =	(const QRectF& Rct) { SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); return *this; };

	QRect					To_QRect() { return QRect(this->xMIN, this->yMIN, Width(), Height()); };
	QRectF					To_QRectF() { return QRectF(this->xMIN, this->yMIN, Width(), Height()); };

	SSPN_Cmn_2DRect<int>		To_Int() { return SSPN_Cmn_2DRect<int>(fRound(this->xMIN), fRound(this->xMAX), fRound(this->yMIN), fRound(this->yMAX)); };
	SSPN_Cmn_2DRect<float>	To_Float() { return SSPN_Cmn_2DRect<float>(this->xMIN, this->xMAX, this->yMIN, this->yMAX); };

	bool IsEqualTo(const SSPN_Cmn_2DRect<TP>& Rct) const
	{
		bool bEq =
			FLT_EQ(this->xMIN, Rct.xMIN) &&
			FLT_EQ(this->xMAX, Rct.xMAX) &&
			FLT_EQ(this->yMIN, Rct.yMIN) &&
			FLT_EQ(this->yMAX, Rct.yMAX);
		return bEq;
	};

public:
	void	SetRect(const TP xMin, const TP xMax, const TP yMin, const TP yMax);
	void	SetRect(const CRectInt& rect);

	static inline int	GetCount_SubDim() { return 4; };
	TP&		operator[](int i)
	{
		switch (i)
		{
		case 0: return this->xMIN; break;
		case 1: return this->xMAX; break;
		case 2: return this->yMIN; break;
		case 3: return this->yMAX; break;
		default:
			assert(false);
			return this->yMIN;
			break;
		}
	};
	const TP	operator[](int i) const
	{
		switch (i)
		{
		case 0: return this->xMIN; break;
		case 1: return this->xMAX; break;
		case 2: return this->yMIN; break;
		case 3: return this->yMAX; break;
		default:
			assert(false);
			break;
		}
	};

	//Attributes and Calculations:
public:
	TP xMIN;
	TP xMAX;
	TP yMIN;
	TP yMAX;

	void operator  = (const TP v)
	{
		this->xMIN = v;
		this->xMAX = v;
		this->yMIN = v;
		this->yMAX = v;
	};

	const SSPN_Cmn_2DRect<TP>& operator += (const SSPN_Cmn_2DRect<TP>& Rct2D)
	{
		this->xMIN += Rct2D.xMIN;
		this->xMAX += Rct2D.xMAX;
		this->yMIN += Rct2D.yMIN;
		this->yMAX += Rct2D.yMAX;
		return *this;
	}

	const SSPN_Cmn_2DRect<TP>& operator -= (const SSPN_Cmn_2DRect<TP>& Rct2D)
	{
		this->xMIN -= Rct2D.xMIN;
		this->xMAX -= Rct2D.xMAX;
		this->yMIN -= Rct2D.yMIN;
		this->yMAX -= Rct2D.yMAX;
		return *this;
	}
	//const SSPN_Cmn_2DRect<TP>& operator += (const CSPN_Cmn_2DPoint<double>& P2D)
	//{
	//	this->xMIN += P2D.x();
	//	this->xMAX += P2D.x();
	//	this->yMIN += P2D.y();
	//	this->yMAX += P2D.y();
	//	return *this;
	//}
	//
	//const SSPN_Cmn_2DRect<TP>& operator -= (const CSPN_Cmn_2DPoint<double>& P2D)
	//{
	//	this->xMIN -= P2D.x();
	//	this->xMAX -= P2D.x();
	//	this->yMIN -= P2D.y();
	//	this->yMAX -= P2D.y();
	//	return *this;
	//}
	const SSPN_Cmn_2DRect<TP>& operator += (const CSPN_Cmn_2DPoint<TP>& P2D)
	{
		this->xMIN += P2D.x();
		this->xMAX += P2D.x();
		this->yMIN += P2D.y();
		this->yMAX += P2D.y();
		return *this;
	}

	const SSPN_Cmn_2DRect<TP>& operator -= (const CSPN_Cmn_2DPoint<TP>& P2D)
	{
		this->xMIN -= P2D.x();
		this->xMAX -= P2D.x();
		this->yMIN -= P2D.y();
		this->yMAX -= P2D.y();
		return *this;
	}

	const SSPN_Cmn_2DRect<TP>& operator *= (const SSPN_Cmn_2DRect<TP>& Rct2D)
	{
		this->xMIN *= Rct2D.xMIN;
		this->xMAX *= Rct2D.xMAX;
		this->yMIN *= Rct2D.yMIN;
		this->yMAX *= Rct2D.yMAX;
		return *this;
	}

	const SSPN_Cmn_2DRect<TP>& operator /= (const SSPN_Cmn_2DRect<TP>& Rct2D)
	{
		this->xMIN /= Rct2D.xMIN;
		this->xMAX /= Rct2D.xMAX;
		this->yMIN /= Rct2D.yMIN;
		this->yMAX /= Rct2D.yMAX;
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator += (TP v)
	{
		this->xMIN += v;
		this->xMAX += v;
		this->yMIN += v;
		this->yMAX += v;
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator -= (TP v)
	{
		this->xMIN -= v;
		this->xMAX -= v;
		this->yMIN -= v;
		this->yMAX -= v;
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator *= (double v)
	{
		this->xMIN *= v;
		this->xMAX *= v;
		this->yMIN *= v;
		this->yMAX *= v;
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator /= (double v)
	{
		this->xMIN /= v;
		this->xMAX /= v;
		this->yMIN /= v;
		this->yMAX /= v;
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator += (const SPnt2D_Flt& P2D_Ofst)
	{
		this->xMIN += P2D_Ofst[0];
		this->xMAX += P2D_Ofst[0];

		this->yMIN += P2D_Ofst[1];
		this->yMAX += P2D_Ofst[1];
		return *this;
	};

	const SSPN_Cmn_2DRect<TP>& operator -= (const SPnt2D_Flt& P2D_Ofst)
	{
		this->xMIN -= P2D_Ofst[0];
		this->xMAX -= P2D_Ofst[0];

		this->yMIN -= P2D_Ofst[1];
		this->yMAX -= P2D_Ofst[1];
		return *this;
	};

	void Inflate(TP dxMIN, TP dxMAX, TP dyMIN, TP dyMAX)// ����ֵ�ü�ΪdeflateЧ��!
	{
		Normalize();

		this->xMIN -= dxMIN;
		this->xMAX += dxMIN;

		this->yMIN -= dyMIN;
		this->yMAX += dyMAX;

		if (this->xMIN > this->xMAX)
		{
			TP xMid = (this->xMIN + this->xMAX) * 0.5f;
			this->xMIN = xMid;
			this->xMAX = xMid;
		}
		if (this->yMIN > this->yMAX)
		{
			TP yMid = (this->yMIN + this->yMAX) * 0.5f;
			this->yMIN = yMid;
			this->yMAX = yMid;
		}
	};

	TP Area() const;
	TP Width() const;
	TP Height() const;

	//[2_14 12:44:40 ]:
	CSPN_Cmn_2DSize<TP> Size()	const { return CSPN_Cmn_2DSize<TP>(Width(), Height()); };
	Sz2D_Dbl SizeDbl()			const { return Sz2D_Dbl(Width(), Height()); };
	Sz2D_Flt SizeFlt()			const { return Sz2D_Flt(Width(), Height()); };
	QSize	 qSize()			const { return QSize(Width(), Height()); };
	QSizeF	 qSizeF()			const { return QSizeF(Width(), Height()); };

	double GetRate_WtoH() const;
	double GetRate_HtoW() const;

	CSPN_Cmn_2DPoint<TP>	yMAX_xMIN() const;
	CSPN_Cmn_2DPoint<TP>	yMAX_xMAX() const;
	CSPN_Cmn_2DPoint<TP>	yMIN_xMIN() const;
	CSPN_Cmn_2DPoint<TP>	yMIN_xMAX() const;
	CSPN_Cmn_2DPoint<TP>	Center() const;

	CSPN_Cmn_2DPoint<TP>	GetPnt_xMIN_yMAX() const { return yMAX_xMIN(); };
	CSPN_Cmn_2DPoint<TP>	GetPnt_xMAX_yMAX() const { return yMAX_xMAX(); };
	CSPN_Cmn_2DPoint<TP>	GetPnt_xMIN_yMIN() const { return yMIN_xMIN(); };
	CSPN_Cmn_2DPoint<TP>	GetPnt_xMAX_yMIN() const { return yMIN_xMAX(); };
	CSPN_Cmn_2DPoint<TP>	GetPnt_Center() const { return Center(); };

	void AdjuctSameWidth_Chg_xMIN(CSPN_Cmn_2DPoint<TP>& RctDst) const;
	void AdjuctSameWidth_Chg_xMAX(CSPN_Cmn_2DPoint<TP>& RctDst) const;
	void AdjuctSameWidth_KeepCenter(CSPN_Cmn_2DPoint<TP>& RctDst) const;

	void AdjuctSameHeight_Chg_yMIN(CSPN_Cmn_2DPoint<TP>& RctDst) const;
	void AdjuctSameHeight_Chg_yMAX(CSPN_Cmn_2DPoint<TP>& RctDst) const;
	void AdjuctSameHeight_KeepCenter(CSPN_Cmn_2DPoint<TP>& RctDst) const;

	BOOL				IsNull() const;
	CRectInt			Get_CRect() const;
	BOOL				PtInRect(const CSPN_Cmn_2DPoint<TP>& P) const;

	BOOL				IsCoveredBy_Part(const SSPN_Cmn_2DRect<TP>& rect) const;
	BOOL				IsCoveredBy_Full(const SSPN_Cmn_2DRect<TP>& rect) const;

	SSPN_Cmn_2DRect<TP>	CoverRect(const SSPN_Cmn_2DRect<TP>& rect) const;
	double				CoverRate(const SSPN_Cmn_2DRect<TP>& rect) const;

	void				UnionRect(const SSPN_Cmn_2DRect<TP>& Rct);


	void				Move(const CSPN_Cmn_2DPoint<TP>& P);
	void				Move(const TP dx, const TP dy);

	void				SetRect_BoundOf(CSPN_Cmn_CArray<SSPN_Cmn_2DPoint<TP>, SSPN_Cmn_2DPoint<TP>&>& ArrP2D);

	/*=====================================================================================
		����ָ���߶��뱾���αߵĽ���.
		����: �������
				-1: ָ���߶γ���Ϊ0(�����غ�)
				 0: P2D_XPnt1��P2D_XPnt2����Ч;
				 1: P2D_XPnt2����Ч;
				 2: ����Ч, �� P2D_XPnt1->P2D_XPnt2 ʸ���� P2DLnEnd1->P2DLnEnd2 ʸ��������ͬ;
	=====================================================================================*/
	int     IntersectWithLineSect(const CSPN_Cmn_2DPoint<TP>& P2DLnEnd1,		//�߶ζ˵�1
								  const CSPN_Cmn_2DPoint<TP>& P2DLnEnd2,		//�߶ζ˵�2
								  CSPN_Cmn_2DPoint<TP>& P2D_XPnt1,				//����1
								  CSPN_Cmn_2DPoint<TP>& P2D_XPnt2,				//����2
								  float fTol = CONST_FLT_LINE_INTERSECT_TOL	//�����ݲ�
	) const;

	//member function:
public:
	//void	Serialize(CSPN_Cmn_Archive& ar);

	void    Normalize();
	bool    IsNormalized() const;

	//{{----------���Ƶ���(�����������ʹ֮�뱾��������)----------
	void AdjustPos_Center(SSPN_Cmn_2DRect<TP>& Rct) const;
	void AdjustPos_Center(CRectInt& Rct) const;

	void AdjuctWidth_Chg_xMIN(TP vW);
	void AdjuctWidth_Chg_xMAX(TP vW);
	void AdjuctWidth_KeepCenterX(TP vW);

	void AdjuctHeight_Chg_yMIN(TP vH);
	void AdjuctHeight_Chg_yMAX(TP vH);
	void AdjuctHeight_KeepCenterY(TP vH);

	void AdjustWHRate_NewL(SSPN_Cmn_2DRect<TP>& Rct) const;
	void AdjustWHRate_NewR(SSPN_Cmn_2DRect<TP>& Rct) const;
	void AdjustWHRate_NewB(SSPN_Cmn_2DRect<TP>& Rct) const;
	void AdjustWHRate_NewT(SSPN_Cmn_2DRect<TP>& Rct) const;

	void AdjustWHRate_NewL(CRectInt& Rct) const;
	void AdjustWHRate_NewR(CRectInt& Rct) const;
	void AdjustWHRate_NewB(CRectInt& Rct) const;
	void AdjustWHRate_NewT(CRectInt& Rct) const;

	void AdjustWHRate_NewLB_Shorten(SSPN_Cmn_2DRect<TP>&	Rct) const;
	void AdjustWHRate_NewLB_Lengthen(SSPN_Cmn_2DRect<TP>&	Rct) const;
	void AdjustWHRate_NewRT_Shorten(SSPN_Cmn_2DRect<TP>&	Rct) const;
	void AdjustWHRate_NewRT_Lengthen(SSPN_Cmn_2DRect<TP>&	Rct) const;

	void AdjustWHRate_NewRB_Shorten(CRectInt&	Rct) const;
	void AdjustWHRate_NewRB_Lengthen(CRectInt&	Rct) const;
	void AdjustWHRate_NewLT_Lengthen(CRectInt&	Rct) const;
	void AdjustWHRate_NewLT_Shorten(CRectInt&	Rct) const;
	//}}----------���Ƶ���(�����������ʹ֮�뱾��������)----------

	//friend ::ofstream& operator<<(::ofstream &stream,SSPN_Cmn_2DRect<TP>& rect);
	//friend ::ifstream& operator>>(::ifstream &stream,SSPN_Cmn_2DRect<TP>& rect);

	//friend CSPN_Cmn_Archive& operator<<(CSPN_Cmn_Archive &Ar, SSPN_Cmn_2DRect<TP>& rect);
	//friend CSPN_Cmn_Archive& operator>>(CSPN_Cmn_Archive &Ar, SSPN_Cmn_2DRect<TP>& rect);
};
//------------------------------------------------------------------------------
template<class TP>
bool SSPN_Cmn_2DRect<TP>::IsNormalized() const
{
	return
		(this->xMAX >= this->xMIN && this->yMAX >= this->yMIN);
}
//------------------------------------------------------------------------------
template<class TP>
void SSPN_Cmn_2DRect<TP>::Normalize()
{
	if (this->xMIN > this->xMAX)
	{
		TP tpTmp = this->xMIN;
		this->xMIN = this->xMAX;
		this->xMAX = tpTmp;
	}

	if (this->yMIN > this->yMAX)
	{
		TP tpTmp = this->yMIN;
		this->yMIN = this->yMAX;
		this->yMAX = tpTmp;
	}
}
//------------------------------------------------------------------------------
template<class TP>
inline SSPN_Cmn_2DRect<TP>::SSPN_Cmn_2DRect(const SSPN_Cmn_2DRect<TP>& Rect)
{
	this->xMIN = Rect.xMIN;
	this->xMAX = Rect.xMAX;
	this->yMIN = Rect.yMIN;
	this->yMAX = Rect.yMAX;
}

template<class TP>
inline BOOL SSPN_Cmn_2DRect<TP>::PtInRect(const CSPN_Cmn_2DPoint<TP>& P) const
{
	assert(this->xMIN <= this->xMAX && this->yMIN <= this->yMAX);
	return (P.x() > this->xMIN && P.x() < this->xMAX &&
			P.y() > this->yMIN && P.y() < this->yMAX);
}
//------------------------------------------------------------------------------
template<class TP>
inline CRectInt SSPN_Cmn_2DRect<TP>::Get_CRect() const
{
	return CRectInt(this->xMIN, this->yMIN, this->xMAX, this->yMAX);
}
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::Move(const CSPN_Cmn_2DPoint<TP>& P)
{
	this->xMIN += P.x();
	this->xMAX += P.x();
	this->yMIN += P.y();
	this->yMAX += P.y();
}
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::Move(const TP dx, const TP dy)
{
	this->xMIN += dx;
	this->xMAX += dx;
	this->yMIN += dy;
	this->yMAX += dy;
}
//------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DRect<TP>::Center() const
{
	return CSPN_Cmn_2DPoint<TP>((this->xMIN + this->xMAX) / 2, (this->yMIN + this->yMAX) / 2);
}
//------------------------------------------------------------------------------
template<class TP>
inline const SSPN_Cmn_2DRect<TP>& SSPN_Cmn_2DRect<TP>::operator =(const SSPN_Cmn_2DRect<TP>& Rct2D)
{
	this->xMIN = Rct2D.xMIN;
	this->xMAX = Rct2D.xMAX;
	this->yMIN = Rct2D.yMIN;
	this->yMAX = Rct2D.yMAX;

	return *this;
};
//------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DRect<TP>::yMAX_xMIN() const
{
	return CSPN_Cmn_2DPoint<TP>(this->xMIN, this->yMAX);
}
//------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DRect<TP>::yMAX_xMAX() const
{
	return CSPN_Cmn_2DPoint<TP>(this->xMAX, this->yMAX);
}
//------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DRect<TP>::yMIN_xMIN() const
{
	return CSPN_Cmn_2DPoint<TP>(this->xMIN, this->yMIN);
}
//------------------------------------------------------------------------------
template<class TP>
inline CSPN_Cmn_2DPoint<TP> SSPN_Cmn_2DRect<TP>::yMIN_xMAX() const
{
	return CSPN_Cmn_2DPoint<TP>(this->xMAX, this->yMIN);
}
//------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DRect<TP>::Area() const
{
	return Width()*Height();
}
//------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DRect<TP>::Width() const
{
	return qAbs<TP>(this->xMAX - this->xMIN);
};
//------------------------------------------------------------------------------
template<class TP>
inline TP SSPN_Cmn_2DRect<TP>::Height() const
{
	return qAbs<TP>(this->yMAX - this->yMIN);
};
//------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DRect<TP>::IsNull() const
{
	if (FLT_EQ(0, Height()*Width()))
		return TRUE;
	else
		return FALSE;
};
//------------------------------------------------------------------------------
template<class TP>
//inline BOOL SSPN_Cmn_2DRect<TP>::IsCoveredBy(const SSPN_Cmn_2DRect<TP>& rect) const
inline BOOL SSPN_Cmn_2DRect<TP>::IsCoveredBy_Part(const SSPN_Cmn_2DRect<TP>& rect) const
{
	assert(this->IsNormalized());
	assert(rect.IsNormalized());

	return(
		((this->xMIN >= rect.xMIN && this->xMIN <= rect.xMAX) ||
		(this->xMAX >= rect.xMIN && this->xMAX <= rect.xMAX)) &&
		 ((this->yMIN >= rect.yMIN && this->yMIN <= rect.yMAX) ||
		(this->yMAX >= rect.yMIN && this->yMAX <= rect.yMAX)));
}
//------------------------------------------------------------------------------
template<class TP>
inline BOOL SSPN_Cmn_2DRect<TP>::IsCoveredBy_Full(const SSPN_Cmn_2DRect<TP>& rect) const
{
	assert(this->IsNormalized());
	assert(rect.IsNormalized());

	return(rect.xMIN <= this->xMIN &&
		   rect.xMAX >= this->xMAX &&
		   rect.yMIN <= this->yMIN &&
		   rect.yMAX >= this->yMAX);
}
//------------------------------------------------------------------------------
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewL(SSPN_Cmn_2DRect<TP>& Rct)  const { Rct.xMIN = Rct.xMAX - GetRate_WtoH()*Rct.Height(); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewR(SSPN_Cmn_2DRect<TP>& Rct)  const { Rct.xMAX = Rct.xMIN + GetRate_WtoH()*Rct.Height(); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewB(SSPN_Cmn_2DRect<TP>& Rct)  const { Rct.yMIN = Rct.yMAX - GetRate_HtoW()*Rct.Width(); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewT(SSPN_Cmn_2DRect<TP>& Rct)  const { Rct.yMAX = Rct.yMIN + GetRate_HtoW()*Rct.Width(); };

template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewL(CRectInt&	Rct)  const { Rct.left = ceil(Rct.right - GetRate_WtoH()*Rct.Height()); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewR(CRectInt&	Rct)  const { Rct.right = ceil(Rct.left + GetRate_WtoH()*Rct.Height()); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewB(CRectInt&	Rct)  const { Rct.bottom = ceil(Rct.top + GetRate_HtoW()*Rct.Width()); };
template<class TP> inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewT(CRectInt&	Rct)  const { Rct.top = ceil(Rct.bottom - GetRate_HtoW()*Rct.Width()); };
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustPos_Center(SSPN_Cmn_2DRect<TP>&	Rct) const
{
	Rct.Move((Width() - Rct.Width()) / 2.0f, (Height() - Rct.Height()) / 2.0f);
}
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustPos_Center(CRectInt  &	Rct) const
{
	Rct.OffsetRect((Width() - Rct.Width()) / 2.0f, (Height() - Rct.Height()) / 2.0f);
}
//------------------------------------------------------------------------------

template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctWidth_Chg_xMIN(TP vW)
{
	this->xMIN = this->xMAX - vW;
}
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctWidth_Chg_xMAX(TP vW)
{
	this->xMAX = this->xMIN + vW;
}
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctWidth_KeepCenterX(TP vW)
{
	this->xMIN = (this->xMIN + this->xMAX - vW) / 2;
	this->xMAX = this->xMIN + vW;
}
//------------------------------------------------------------------------------

template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctHeight_Chg_yMIN(TP vH)
{
	this->yMIN = this->yMAX - vH;
}
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctHeight_Chg_yMAX(TP vH)
{
	this->yMAX = this->yMIN + vH;
}
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjuctHeight_KeepCenterY(TP vH)
{
	this->yMIN = (this->yMIN + this->yMAX - vH) / 2;
	this->yMAX = this->yMIN + vH;
}
//------------------------------------------------------------------------------
template<class TP>
inline double SSPN_Cmn_2DRect<TP>::GetRate_WtoH()  const
{
	assert(!FLT_EQ(Height(), 0.0f));
	return float(Width()) / Height();
};
template<class TP>
inline double SSPN_Cmn_2DRect<TP>::GetRate_HtoW()  const
{
	assert(!FLT_EQ(Width(), 0.0f));
	return float(Height()) / Width();
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewLB_Shorten(SSPN_Cmn_2DRect<TP>& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW > fRateH)
		Rct.xMIN = Rct.xMAX - GetRate_WtoH()*Rct.Height();
	else
		Rct.yMIN = Rct.yMAX - GetRate_HtoW()*Rct.Width();
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewRT_Shorten(SSPN_Cmn_2DRect<TP>& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW > fRateH)
		Rct.xMAX = Rct.xMIN + GetRate_WtoH()*Rct.Height();
	else
		Rct.yMAX = Rct.yMIN + GetRate_HtoW()*Rct.Width();
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewLB_Lengthen(SSPN_Cmn_2DRect<TP>& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW < fRateH)
		Rct.xMIN = Rct.xMAX - GetRate_WtoH()*Rct.Height();
	else
		Rct.yMIN = Rct.yMAX - GetRate_HtoW()*Rct.Width();
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewRT_Lengthen(SSPN_Cmn_2DRect<TP>& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW < fRateH)
		Rct.xMAX = Rct.xMIN + GetRate_WtoH()*Rct.Height();
	else
		Rct.yMAX = Rct.yMIN + GetRate_HtoW()*Rct.Width();
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewLT_Shorten(CRectInt& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW > fRateH)
		Rct.left = ceil(Rct.right - GetRate_WtoH()*Rct.Height());
	else
		Rct.top = ceil(Rct.bottom - GetRate_HtoW()*Rct.Width());
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewRB_Shorten(CRectInt& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW > fRateH)
		Rct.right = ceil(Rct.left + GetRate_WtoH()*Rct.Height());
	else
		Rct.bottom = ceil(Rct.top + GetRate_HtoW()*Rct.Width());
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewLT_Lengthen(CRectInt& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW < fRateH)
		Rct.left = ceil(Rct.right - GetRate_WtoH()*Rct.Height());
	else
		Rct.top = ceil(Rct.bottom - GetRate_HtoW()*Rct.Width());
};
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::AdjustWHRate_NewRB_Lengthen(CRectInt& Rct) const
{
	assert(!FLT_EQ(Width(), 0.0f));
	assert(!FLT_EQ(Height(), 0.0f));

	float fRateW = float(Rct.Width()) / Width();
	float fRateH = float(Rct.Height()) / Height();

	if (fRateW < fRateH)
		Rct.right = ceil(Rct.left + GetRate_WtoH()*Rct.Height());
	else
		Rct.bottom = ceil(Rct.top + GetRate_HtoW()*Rct.Width());
};
//------------------------------------------------------------------------------
template<class TP>
SSPN_Cmn_2DRect<TP>::SSPN_Cmn_2DRect()
{
	this->xMIN = 0.0f;
	this->xMAX = 0.0f;
	this->yMIN = 0.0f;
	this->yMAX = 0.0f;
}
//------------------------------------------------------------------------------
template<class TP>
SSPN_Cmn_2DRect<TP>::SSPN_Cmn_2DRect(const CRectInt& rect)
{
	CRectInt Rct = rect;
	Rct.NormalizeRect();

	this->xMIN = Rct.left;
	this->xMAX = Rct.right;
	this->yMIN = Rct.top;
	this->yMAX = Rct.bottom;
}
template<class TP>
void SSPN_Cmn_2DRect<TP>::SetRect(const CRectInt& rect)
{
	CRectInt Rct = rect;
	Rct.NormalizeRect();

	this->xMIN = Rct.left;
	this->xMAX = Rct.right;
	this->yMIN = Rct.top;
	this->yMAX = Rct.bottom;
}
//------------------------------------------------------------------------------
template<class TP>
SSPN_Cmn_2DRect<TP>::SSPN_Cmn_2DRect(const TP x1, const TP x2, const TP y1, const TP y2)
{
	this->xMIN = __min(x1, x2);
	this->xMAX = __max(x1, x2);
	this->yMIN = __min(y1, y2);
	this->yMAX = __max(y1, y2);
}
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::SetRect(const TP x1, const TP x2, const TP y1, const TP y2)
{
	this->xMIN = __min(x1, x2);
	this->xMAX = __max(x1, x2);
	this->yMIN = __min(y1, y2);
	this->yMAX = __max(y1, y2);
}
//------------------------------------------------------------------------------
template<class TP>
SSPN_Cmn_2DRect<TP>::SSPN_Cmn_2DRect(const CSPN_Cmn_2DPoint<TP>& point1, const CSPN_Cmn_2DPoint<TP>& point2)
{
	this->xMIN = __min(point1.x(), point2.x());
	this->xMAX = __max(point1.x(), point2.x());
	this->yMIN = __min(point1.y(), point2.y());
	this->yMAX = __max(point1.y(), point2.y());
}
//------------------------------------------------------------------------------
//
// Comment : Get the rect common to this and the input rect.
//
//------------------------------------------------------------------------------
template<class TP>
inline SSPN_Cmn_2DRect<TP> SSPN_Cmn_2DRect<TP>::CoverRect(const SSPN_Cmn_2DRect<TP>& rect) const
{
	SSPN_Cmn_2DRect<TP> rectCovered;

	rectCovered.xMIN = __max(this->xMIN, rect.xMIN);
	rectCovered.xMAX = __min(this->xMAX, rect.xMAX);
	rectCovered.yMIN = __max(this->yMIN, rect.yMIN);
	rectCovered.yMAX = __min(this->yMAX, rect.yMAX);
	rectCovered.Normalize();

	return rectCovered;
}
//------------------------------------------------------------------------------
//
// Comment : Get the union rect common to this and the input rect.
//
//------------------------------------------------------------------------------
template<class TP>
inline void SSPN_Cmn_2DRect<TP>::UnionRect(const SSPN_Cmn_2DRect<TP>& Rct)
{
	assert(this->xMIN <= this->xMAX);
	assert(this->yMIN <= this->yMAX);

	assert(Rct.xMIN <= Rct.xMAX);
	assert(Rct.yMIN <= Rct.yMAX);

	this->xMIN = std::min<TP>(this->xMIN, Rct.xMIN);
	this->xMAX = std::max<TP>(this->xMAX, Rct.xMAX);
	this->yMIN = std::min<TP>(this->yMIN, Rct.yMIN);
	this->yMAX = std::max<TP>(this->yMAX, Rct.yMAX);
}
//------------------------------------------------------------------------------
//
// Comment : Get the covered rate of this by the input rect.
//
//------------------------------------------------------------------------------
template<class TP>
inline double SSPN_Cmn_2DRect<TP>::CoverRate(const SSPN_Cmn_2DRect<TP>& rect) const
{
	if (!IsNull())
		return double(CoverRect(rect).Area()) / Area();
	else
		return 0;
}
//------------------------------------------------------------------------------
//template<class TP>
//inline void SSPN_Cmn_2DRect<TP>::Serialize(CSPN_Cmn_Archive& ar)
//{
//	if (ar.IsStoring())
//	{
//		ar << this->xMIN;
//		ar << this->xMAX;
//		ar << this->yMIN;
//		ar << this->yMAX;
//	}
//	else
//	{
//		ar >> this->xMIN;
//		ar >> this->xMAX;
//		ar >> this->yMIN;
//		ar >> this->yMAX;
//	}
//}
//------------------------------------------------------------------------------
//template<class TP> 
//::ifstream& operator>>(::ifstream &stream, SSPN_Cmn_2DRect<TP>& rect)
//{
//	stream>>rect.xMIN>>rect.xMAX>>rect.yMIN>>rect.yMAX;
//	return stream;
//}
////------------------------------------------------------------------------------
//template<class TP> 
//::ofstream& operator<<(::ofstream &stream, SSPN_Cmn_2DRect<TP>& rect)
//{
//	stream<<rect.xMIN<<rect.xMAX<<rect.yMIN<<rect.yMAX;
//	return stream;
//}
//------------------------------------------------------------------------------
//template<class TP>
//CSPN_Cmn_Archive& operator<<(CSPN_Cmn_Archive &Ar, SSPN_Cmn_2DRect<TP>& rect)
//{
//	Ar << rect.xMIN << rect.xMAX << rect.yMIN << rect.yMAX;
//	return Ar;
//}
////------------------------------------------------------------------------------
//template<class TP>
//CSPN_Cmn_Archive& operator>>(CSPN_Cmn_Archive &Ar, SSPN_Cmn_2DRect<TP>& rect)
//{
//	Ar >> rect.xMIN >> rect.xMAX >> rect.yMIN >> rect.yMAX;
//	return Ar;
//}

template<class TP>
void SSPN_Cmn_2DRect<TP>::SetRect_BoundOf(CSPN_Cmn_CArray<SSPN_Cmn_2DPoint<TP>, SSPN_Cmn_2DPoint<TP>&>& ArrP2D)
{
	if (ArrP2D.GetSize() == 0)
	{
		return;
	}

	this->xMIN = ArrP2D[0].x();
	this->xMAX = this->xMIN;

	this->yMIN = ArrP2D[0].y();
	this->yMAX = this->yMIN;

	for (int i = 1; i < ArrP2D.GetSize(); i++)
	{
		SSPN_Cmn_2DPoint<TP>& P = ArrP2D[i];

		if (P.x() < this->xMIN)
		{
			this->xMIN = P.x();
		}
		else if (P.x() > this->xMAX)
		{
			this->xMAX = P.x();
		}

		if (P.y() < this->yMIN)
		{
			this->yMIN = P.y();
		}
		else if (P.y() > this->yMAX)
		{
			this->yMAX = P.y();
		}
	}
}

template<class TP>
int SSPN_Cmn_2DRect<TP>::IntersectWithLineSect(const CSPN_Cmn_2DPoint<TP>& P2DLnEnd1,		//�����߶ζ˵�1
											  const CSPN_Cmn_2DPoint<TP>& P2DLnEnd2,		//�����߶ζ˵�2
											  CSPN_Cmn_2DPoint<TP>& P2D_XPnt1,				//�������1
											  CSPN_Cmn_2DPoint<TP>& P2D_XPnt2,				//�������2
											  float fTol/* = CONST_FLT_LINE_INTERSECT_TOL*/	//��������ݲ�
) const
{
	typedef CSPN_Cmn_2DPoint<TP> P2DTp;

	if (FLT_EQ(0, P2DLnEnd1.GetDistTo(P2DLnEnd2)))
	{
		return -1;
	}

	if (FLT_EQ(0, Width()) && FLT_EQ(0, Height()))
	{
		return 0;
	}

	assert(Width() > 0 || Height() > 0);

	CSPN_Cmn_2DPoint<TP> arrP2DCorner[4];
	arrP2DCorner[0] = (this->yMAX_xMIN());
	arrP2DCorner[1] = (this->yMAX_xMAX());
	arrP2DCorner[2] = (this->yMIN_xMAX());
	arrP2DCorner[3] = (this->yMIN_xMIN());

	CSPN_Cmn_2DPoint<TP>* arrpP2D_XP[2];
	arrpP2D_XP[0] = &P2D_XPnt1;
	arrpP2D_XP[1] = &P2D_XPnt2;

	int iXP = 0;
	for (int i = 0; i < 4; i++)
	{
		if (CSPN_Cmn_2DLine<TP>::Intersect2D_SectionAndSection(P2DLnEnd1, P2DLnEnd2, arrP2DCorner[i], arrP2DCorner[i + 1], *arrpP2D_XP[iXP], fTol) < 1)
			continue;

		if (2 == ++iXP)
		{
			if (P2DLnEnd1.GetDistTo_Sq(*arrpP2D_XP[1]) < P2DLnEnd1.GetDistTo_Sq(*arrpP2D_XP[0]))
			{
				ExchangeValue<P2DTp>(*arrpP2D_XP[0], *arrpP2D_XP[1]);
			}
			break;
		}
	}

	return iXP;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator*(TPNum vNum, const SSPN_Cmn_2DRect<TPRect>& Rect)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst *= vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator*(const SSPN_Cmn_2DRect<TPRect>& Rect, TPNum vNum)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst *= vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator/(const SSPN_Cmn_2DRect<TPRect>& Rect, TPNum vNum)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst /= vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator+(const SSPN_Cmn_2DRect<TPRect>& Rect, TPNum vNum)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst += vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator+(TPNum vNum, const SSPN_Cmn_2DRect<TPRect>& Rect)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst += vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator-(const SSPN_Cmn_2DRect<TPRect>& Rect, TPNum vNum)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst -= vNum;
	return RectDst;
};

template<typename TPNum, typename TPRect>
inline SSPN_Cmn_2DRect<TPRect> operator-(TPNum vNum, const SSPN_Cmn_2DRect<TPRect>& Rect)
{
	SSPN_Cmn_2DRect<TPRect> RectDst(Rect);
	RectDst *= -1;
	RectDst -= vNum;
	return RectDst;
};


typedef SSPN_Cmn_2DRect<int>				SRct2D_Int;
typedef SSPN_Cmn_2DRect<unsigned int>	SRct2D_UInt;

typedef SSPN_Cmn_2DRect<short>			SRct2D_Sht;
typedef SSPN_Cmn_2DRect<unsigned short>	SRct2D_USht;

typedef SSPN_Cmn_2DRect<char>			SRct2D_Char;
typedef SSPN_Cmn_2DRect<unsigned char>	SRct2D_UChar;

typedef SSPN_Cmn_2DRect<float>			SRct2D_Flt;
//#define Rct2D_Flt SSPN_Cmn_2DRect<float>
typedef SSPN_Cmn_2DRect<double>			SRct2D_Dbl;

typedef SSPN_Cmn_2DRect<int>				SRct2D_Idx;

//*********************************************************************************************************
//*********************************************************************************************************

template<class TP>
class CSPN_Cmn_2DRect : public SSPN_Cmn_2DRect<TP>
{
public:
	CSPN_Cmn_2DRect() { this->xMIN = 0; this->xMAX = 0; this->yMIN = 0; this->yMAX = 0; };
	CSPN_Cmn_2DRect(const TP xMin, const TP xMax, const TP yMin, const TP yMax) { this->SetRect(xMin, xMax, yMin, yMax); };
	CSPN_Cmn_2DRect(const CSPN_Cmn_2DPoint<TP>& P1, const CSPN_Cmn_2DPoint<TP>& P2) { this->SetRect(P1.x(), P2.x(), P1.y(), P2.y()); };
	CSPN_Cmn_2DRect(const CRectInt& Rct) { this->SetRect(Rct.left, Rct.right, Rct.top, Rct.bottom); };
	CSPN_Cmn_2DRect(const CSPN_Cmn_2DRect<TP>& Rct) { this->SetRect(Rct.xMIN, Rct.xMAX, Rct.yMIN, Rct.yMAX); };
	CSPN_Cmn_2DRect(const SSPN_Cmn_2DRect<TP>& Rct) { this->SetRect(Rct.xMIN, Rct.xMAX, Rct.yMIN, Rct.yMAX); };

	explicit CSPN_Cmn_2DRect(const QRect&  Rct) { this->SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); };
	explicit CSPN_Cmn_2DRect(const QRectF& Rct) { this->SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); };

public:
	inline SSPN_Cmn_2DRect<TP>& operator			= (const QRect&  Rct) { this->SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); return *this; };
	inline const CSPN_Cmn_2DRect<TP>& operator	= (const QRectF& Rct) { this->SetRect(Rct.left(), Rct.right(), Rct.top(), Rct.bottom()); return *this; };
	inline const CSPN_Cmn_2DRect<TP>& operator	= (const CSPN_Cmn_2DRect<TP>& Rct) { this->SetRect(Rct.xMIN, Rct.xMAX, Rct.yMIN, Rct.yMAX); return *this; };
	//inline const CSPN_Cmn_2DRect<TP>& operator	= (const SSPN_Cmn_2DRect<TP>& Rct) { this->SetRect(Rct.xMIN, Rct.xMAX, Rct.yMIN, Rct.yMAX); return *this; };
};

typedef CSPN_Cmn_2DRect<int>				Rct2D_Int;
typedef CSPN_Cmn_2DRect<unsigned int>	Rct2D_UInt;

typedef CSPN_Cmn_2DRect<short>			Rct2D_Sht;
typedef CSPN_Cmn_2DRect<unsigned short>	Rct2D_USht;

typedef CSPN_Cmn_2DRect<char>			Rct2D_Char;
typedef CSPN_Cmn_2DRect<unsigned char>	Rct2D_UChar;

typedef CSPN_Cmn_2DRect<float>			Rct2D_Flt;
//#define Rct2D_Flt CSPN_Cmn_2DRect<float>
typedef CSPN_Cmn_2DRect<double>			Rct2D_Dbl;

typedef CSPN_Cmn_2DRect<int>				Rct2D_Idx;


#endif //  // !defined(SPN_Cmn_2DRECT_H__INCLUDED_
