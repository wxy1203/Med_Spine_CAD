// SPN_Cmn_2DLine.h: interface for the CSPN_Cmn_2DLine<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_2DLine_H__INCLUDED_
#define SPN_Cmn_2DLine_H__INCLUDED_

#	pragma once

#include "SPN_Cmn_2DPoint.h"

template<class TP>
class CSPN_Cmn_2DLine
{
	//Constructor/destructor:
public:
	CSPN_Cmn_2DLine()
	{
	};
	CSPN_Cmn_2DLine(CSPN_Cmn_2DPoint<TP> P1, CSPN_Cmn_2DPoint<TP> P2)
	{
		Construct(P1, P2);
	};
	CSPN_Cmn_2DLine(const CSPN_Cmn_2DLine<TP>& Ln2D)
	{
		*this = Ln2D;
	};
	const CSPN_Cmn_2DLine<TP>&  operator=(const CSPN_Cmn_2DLine<TP>& Ln2D)
	{
		m_P1 = Ln2D.m_P1;
		m_P2 = Ln2D.m_P2;
	};

	void Construct(CSPN_Cmn_2DPoint<TP> P1, CSPN_Cmn_2DPoint<TP> P2)
	{
		m_P1 = P1;
		m_P2 = P2;
	};

	//Attritutes:
public:
	static inline int	GetCount_SubDim()
	{
		return 4;
	};
	inline TP& operator[](int i)
	{
		switch (i)
		{
		case 0: return m_P1[0]; break;
		case 1: return m_P1[1]; break;
		case 2: return m_P2[0]; break;
		case 3: return m_P2[1]; break;
		default:
			assert(false);
			break;
		}
	};
	const TP& operator[](int i) const
	{
		switch (i)
		{
		case 0: return m_P1[0]; break;
		case 1: return m_P1[1]; break;
		case 2: return m_P2[0]; break;
		case 3: return m_P2[1]; break;
		default:
			assert(false);
			break;
		}
	};

	TP GetVectLength() const
	{
		return m_P1.GetDistTo(m_P2);
	};
	TP GetVectLengthSq() const
	{
		return m_P1.GetDistTo_Sq(m_P2);
	};

	BOOL IsPointNearLine(const CSPN_Cmn_2DPoint<TP>& P, const TP fTol) const;

	bool GetPoint_onLine_byX(CSPN_Cmn_2DPoint<TP>& PDst)const;
	bool GetPoint_onLine_byY(CSPN_Cmn_2DPoint<TP>& PDst)const;

	//Calculations:
public:
	void operator  = (const TP v)
	{
		m_P1 = v;
		m_P2 = v;
	};
	void operator += (const CSPN_Cmn_2DPoint<TP>& P)
	{
		m_P1 += P;
		m_P2 += P;
	};
	void operator -= (const CSPN_Cmn_2DPoint<TP>& P)
	{
		m_P1 -= P;
		m_P2 -= P;
	};
	void operator *= (double fK)
	{
		m_P1 *= fK;
		m_P2 *= fK;
	};
	void operator /= (double fK)
	{
		m_P1 /= fK;
		m_P2 /= fK;
	};

	void Flip_X(TP fAx_X)
	{
		m_P1[0] = fAx_X + (fAx_X - m_P1[0]);
		m_P2[0] = fAx_X + (fAx_X - m_P2[0]);
	};
	void Flip_Y(TP fAx_Y)
	{
		m_P1[1] = fAx_Y + (fAx_Y - m_P1[1]);
		m_P2[1] = fAx_Y + (fAx_Y - m_P2[1]);
	};

	BOOL operator==(const CSPN_Cmn_2DLine<TP>& Ln) const
	{
		bool bEq = true;
		bEq &= (m_P1 == Ln.m_P1);
		bEq &= (m_P2 == Ln.m_P2);
		return bEq;
	};
	BOOL operator!=(const CSPN_Cmn_2DPoint<TP>& Ln) const
	{
		return !((*this) == Ln);
	};

	//member function:
public:
	//void Serialize(CSPN_Cmn_Archive& ar);

	//static:
public:
	static void InsertPoint(CSPN_Cmn_2DPoint<TP>& pointBgn,
							CSPN_Cmn_2DPoint<TP>& pointEnd,
							CSPN_Cmn_CArray<CSPN_Cmn_2DPoint<TP>, CSPN_Cmn_2DPoint<TP>&>& ArrPoint,
							int nSect,
							TP  dx,
							TP  dy);

	static int IntersectLineAndCircle(TP  R,
									  const CSPN_Cmn_2DPoint<TP>& PA,
									  const CSPN_Cmn_2DPoint<TP>& PB,
									  CSPN_Cmn_2DPoint<TP>& PRslt1,
									  CSPN_Cmn_2DPoint<TP>& PRslt2);
	/*=============================================================================*
	|-----------------------------------------------------------------------------
	|返回: |类型: int              |取值             |意义  返回值是交点个数
	|-----------------------------------------------------------------------------
	|用途:	计算直线与线段间的交点， 两点式。如果没有交点，返回交点值无效；线段(直
	|		线)长度为0或两输入点相同返回-1；线段重合返回2；PLine1x为直线端点
	*=============================================================================*/
	static int Intersect2D_LineAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	直线端点
										  const CSPN_Cmn_2DPoint<TP>& PLine12,	//	直线端点
										  const CSPN_Cmn_2DPoint<TP>& PLine21,	//	线段端点
										  const CSPN_Cmn_2DPoint<TP>& PLine22,	//	线段端点
										  CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
										  TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

  /*=============================================================================*
  |返回: |类型: int              |取值             |意义  返回值是交点个数
  |-----------------------------------------------------------------------------
  |用途:	计算直线与线段间的交点， 点斜式。如果没有交点，返回交点值无效；线段长
  |		度为0返回-1；线段重合返回2；点斜式不存在斜率无穷大的输入；k1、d1为直
  |		线参数
  *=============================================================================*/
	static int Intersect2D_LineAndSection(TP k1,							//	直线斜率
										  TP d1,							//	直线	y = k * x + d
										  TP k2,							//	线段斜率
										  TP d2,							//	线段	y = k * x + d
										  TP fSectionBegin,				//	线段范围x
										  TP fSectionEnd,					//	线段范围x
										  CSPN_Cmn_2DPoint<TP>& PIntersect,	//	交点
										  TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  浮点相等比较时所用容差

  /*=============================================================================*
  |返回: |类型: int              |取值             |意义  返回值是交点个数
  |-----------------------------------------------------------------------------
  |用途:	计算线段间的交点， 点斜式。如果没有交点，返回交点值无效；线段长
  |		度为0返回-1；线段重合返回2；点斜式不存在斜率无穷大的输入
  *=============================================================================*/
	static int Intersect2D_SectionAndSection(TP k1,								//	第一条线段斜率
											 TP d1,								//	第一条线段	y = k * x + d
											 TP k2,								//	第二条线段斜率
											 TP d2,								//	第二条线段	y = k * x + d
											 TP fSection1Begin, TP fSection1End,	//	第一条线段范围x
											 TP fSection2Begin, TP fSection2End,	//	第二条线段范围x
											 CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
											 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

 /*=============================================================================*
 |返回: |类型: int              |取值             |意义  返回值是交点个数
 |-----------------------------------------------------------------------------
 |用途:	计算线段间的交点， 两点式。如果没有交点，返回交点值无效；线段长
 |		度为0或两输入端点相同返回-1；线段重合返回2
 |		y = ((y2 - y1 )/(x2 - x1)) * x + ((x1 * y2 - x2 * y1)/(x1 - x2))
 *=============================================================================*/
	static int Intersect2D_SectionAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	第一条线段端点
											 const CSPN_Cmn_2DPoint<TP>& PLine12,	//	第一条线段端点
											 const CSPN_Cmn_2DPoint<TP>& PLine21,	//	第二条线段端点
											 const CSPN_Cmn_2DPoint<TP>& PLine22,	//	第二条线段端点
											 CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
											 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

 /*=============================================================================*
 |返回: |类型: int              |取值             |意义  返回值是交点个数
 |-----------------------------------------------------------------------------
 |用途:	计算直线间的交点， 点斜式。如果没有交点，返回交点值无效；线段重合返回2；点
 |		斜式不存在斜率无穷大的输入
 *=============================================================================*/
	static int Intersect2D_LineAndLine(TP k1,							//	第一条直线斜率
									   TP d1,							//	第一条直线	y = k * x + d
									   TP k2,							//	第二条直线斜率
									   TP d2,							//	第二条直线	y = k * x + d
									   CSPN_Cmn_2DPoint<TP>& PIntersect,	//	交点
									   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  浮点相等比较时所用容差

   /*=============================================================================*
   |返回: |类型: int              |取值             |意义  返回值是交点个数
   |-----------------------------------------------------------------------------
   |用途:	计算直线间的交点，两点式。如果没有交点，返回交点值无效；两输入端点相同
   |		返回-1；线段重合返回2
   |		y = ((y2 - y1 )/(x2 - x1)) * x + ((x1 * y2 - x2 * y1)/(x1 - x2))
   *=============================================================================*/
	static int Intersect2D_LineAndLine(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	第一条直线
									   const CSPN_Cmn_2DPoint<TP>& PLine12,	//	第一条直线
									   const CSPN_Cmn_2DPoint<TP>& PLine21,	//	第二条直线
									   const CSPN_Cmn_2DPoint<TP>& PLine22,	//	第二条直线
									   CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
									   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

/*=============================================================================*
|返回: |类型: int              |取值             |意义  返回值是交点个数
|-----------------------------------------------------------------------------
|用途:	计算圆与直线交点， 点斜式。圆半径小于等于0或直线两点重合返回-1；如果没
|		有交点，交点值无效；若只有一个交点，则交点1有效；如果有两个交点，两个返
|		回值有效；点斜式不存在斜率无穷大的输入
*=============================================================================*/
	static int Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
										 TP fRadius,							//	圆半径
										 TP k,								//	斜率
										 TP d,								//	y = k * x + d
										 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	交点1
										 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	交点2
										 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

 /*=============================================================================*
 |返回: |类型: int              |取值             |意义  返回值是交点个数
 |-----------------------------------------------------------------------------
 |用途:	计算圆与直线交点， 两点式。圆半径小于等于0或直线两点重合返回-1；如果没
 |		有交点，交点值无效；若只有一个交点，则交点1有效；如果有两个交点，两个返
 |		回值有效；
 *=============================================================================*/
	static int Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
										 TP fRadius,							//	圆半径
										 const CSPN_Cmn_2DPoint<TP>& PLine1,	//	直线点1
										 const CSPN_Cmn_2DPoint<TP>& PLine2,	//	直线点2
										 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	交点1
										 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	交点2
										 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

 /*=============================================================================*
 |返回: |类型: int              |取值             |意义  返回值是交点个数
 |-----------------------------------------------------------------------------
 |用途:	计算圆与线段交点， 点斜式。圆半径小于等于0或线段长度为0返回-1；如果没有
 |		交点，交点值无效；若只有一个交点，则交点1有效；如果有两个交点，两个返回
 |		值有效；点斜式不存在斜率无穷大的输入
 *=============================================================================*/
	static int Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
											TP fRadius,							//	圆半径
											TP k,								//	斜率
											TP d,								//	y = k * x + d
											TP fSectionBegin, TP fSectionEnd,	//	线段范围x
											CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	交点1
											CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	交点2
											TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差

	/*=============================================================================*
	|返回: |类型: int              |取值             |意义  返回值是交点个数
	|-----------------------------------------------------------------------------
	|用途:	计算圆与线段交点，两点式。圆半径小于等于0或线段两端点重合返回-1；如果没
	|		有交点，交点值无效；若只有一个交点，则交点1有效；如果有两个交点，两个返
	|		回值有效
	*=============================================================================*/
	static int Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
											TP fRadius,							//	圆半径
											const CSPN_Cmn_2DPoint<TP>& PLine1,	//	线段端点1
											const CSPN_Cmn_2DPoint<TP>& PLine2,	//	线段端点2
											CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	交点1
											CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	交点2
											TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  浮点相等比较时所用容差


	//data member:
public:
	CSPN_Cmn_2DPoint<TP> m_P1;
	CSPN_Cmn_2DPoint<TP> m_P2;
};
//**************************************************************************************************
//--------------------------------------------------------------------------------------------------
//template<class TP>
//inline void CSPN_Cmn_2DLine<TP>::Serialize(CSPN_Cmn_Archive& ar)
//{
//	if (ar.IsStoring())
//	{
//		m_P1.Serialize(ar);
//		m_P2.Serialize(ar);
//	}
//	else
//	{
//		m_P1.Serialize(ar);
//		m_P2.Serialize(ar);
//	}
//};
//------------------------------------------------------------------------------
//template<class TP>
//::ifstream& operator>>(::ifstream &stream, CSPN_Cmn_2DPoint<TP>& P)
//{
//	stream>>P.m_arrf2D[0]>>P.m_arrf2D[1];
//	return stream;
//}
////------------------------------------------------------------------------------
//template<class TP>
//::ofstream& operator<<(::ofstream &stream, const CSPN_Cmn_2DPoint<TP>& P)
//{
//	stream<<P.m_arrf2D[0]<<P.m_arrf2D[1];
//	return stream;
//}
//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template<class TP>
inline BOOL CSPN_Cmn_2DLine<TP>::IsPointNearLine(const CSPN_Cmn_2DPoint<TP>& P, const TP fTol) const
{
	TP fDistP1P2 = m_P1.GetDistTo(m_P2);
	TP fDistP1P = P.GetDistTo(m_P1);
	TP fDistP2P = P.GetDistTo(m_P2);

	return fabs(fDistP1P + fDistP2P - fDistP1P2) < fTol;
};
//--------------------------------------------------------------------------------------------------
template<class TP>
inline bool CSPN_Cmn_2DLine<TP>::GetPoint_onLine_byX(CSPN_Cmn_2DPoint<TP>& PDst) const
{
	TP fX = PDst[0];
	if (FLT_EQ(m_P1[1], m_P2[1]))
	{
		PDst[1] = m_P1[1];
		return true;
	}
	else if (FLT_EQ(m_P1[0], m_P2[0]))
	{
		return false;
	}
	else
	{
		float fK = (m_P2[1] - m_P1[1]) / (m_P2[0] - m_P1[0]);
		float fB = m_P2[1] - fK * (m_P2[0]);
		PDst[1] = fX * fK + fB;
		return true;
	}
};

template<class TP>
inline bool CSPN_Cmn_2DLine<TP>::GetPoint_onLine_byY(CSPN_Cmn_2DPoint<TP>& PDst) const
{
	TP fY = PDst[1];
	if (FLT_EQ(m_P1[0], m_P2[0]))
	{
		PDst[0] = m_P1[0];
		return true;
	}
	else if (FLT_EQ(m_P1[1], m_P2[1]))
	{
		return false;
	}
	else
	{
		float fK = (m_P2[0] - m_P1[0]) / (m_P2[1] - m_P1[1]);
		float fB = m_P2[0] - fK * (m_P2[1]);
		PDst[0] = fY * fK + fB;
		return true;
	}
};
//--------------------------------------------------------------------------------------------------
/**************************************************************************************
 *
 * 该函数计算线段PA-PB与圆周的交点; 该圆假定以原点(0,0)为圆心, R为半径.
 * 结果: 如无交点, PRslt1 和 PRslt2数值均无意义;
 *       如有一个交点, 存入PRslt1; PRslt2数值无意义;
 *       如有两个交点, 分别存入PRslt1 和 PRslt2, 且PRslt1靠近PA, 而PRslt2靠近PB;
 *       返回值: 交点个数;
 *
 *
 *************************************************************************************/

template<class TP>
inline int CSPN_Cmn_2DLine<TP>::IntersectLineAndCircle(TP  R,
													  const CSPN_Cmn_2DPoint<TP>& PA,
													  const CSPN_Cmn_2DPoint<TP>& PB,
													  CSPN_Cmn_2DPoint<TP>& PRslt1,
													  CSPN_Cmn_2DPoint<TP>& PRslt2)
{
	assert(R > 0.0f);

	CSPN_Cmn_2DPoint<TP> P1(0, 0);
	CSPN_Cmn_2DPoint<TP> P2(0, 0);

	CSPN_Cmn_2DPoint<TP>* arr_pPR[2];
	{
		arr_pPR[0] = &PRslt1;
		arr_pPR[1] = &PRslt2;
	}

	int nPRsltValid = 0;

	if (FLT_EQ(PA[0], PB[0]))
	{
		P1[0] = PA[0];
		P2[0] = PA[0];

		P1[1] = pow((R * R - PA[0] * PA[0]), 0.5);
		P2[1] = -P1[1];

		if (P1[1] <= std::max<TP>(PA[1], PB[1]) && P1[1] >= std::min<TP>(PA[1], PB[1]))
		{
			*(arr_pPR[nPRsltValid++]) = P1;
		}

		if (P2[1] <= __max(PA[1], PB[1]) && P2[1] >= __min(PA[1], PB[1]))
		{
			*(arr_pPR[nPRsltValid++]) = P2;
		}
	}
	else if (FLT_EQ(PA[1], PB[1]))
	{
		P1[1] = PA[1];
		P2[1] = PA[1];

		P1[0] = pow((R * R - PA[1] * PA[1]), 0.5);
		P2[0] = -P1[0];

		if (P1[0] <= __max(PA[0], PB[0]) && P1[0] >= __min(PA[0], PB[0]))
		{
			*(arr_pPR[nPRsltValid++]) = P1;
		}

		if (P2[0] <= __max(PA[0], PB[0]) && P2[0] >= __min(PA[0], PB[0]))
		{
			*(arr_pPR[nPRsltValid++]) = P2;
		}
	}
	else
	{
		TP k, b;//For Line equation;
		TP root;
		k = (PB[1] - PA[1]) / (PB[0] - PA[0]);
		b = PA[1] - PA[0] * k;

		root = pow(k * k * b * b - (k * k + 1) * (b * b - R * R), 0.5);
		P1[0] = (-k * b + root) / (k * k + 1);
		P2[0] = (-k * b - root) / (k * k + 1);
		P1[1] = k * P1[0] + b;
		P2[1] = k * P2[0] + b;

		if (P1[0] <= __max(PA[0], PB[0]) && P1[0] >= __min(PA[0], PB[0]))
		{
			*(arr_pPR[nPRsltValid++]) = P1;
		}

		if (P2[0] <= __max(PA[0], PB[0]) && P2[0] >= __min(PA[0], PB[0]))
		{
			*(arr_pPR[nPRsltValid++]) = P2;
		}
	}

	if (nPRsltValid == 2)
	{
		if (PRslt1.GetDistTo(PA) > PRslt2.GetDistTo(PA))
		{
			typedef CSPN_Cmn_2DPoint<TP> P2DTp;
			::ExchangeValue<P2DTp>(PRslt1, PRslt2);
		}
	}

	return  nPRsltValid;
};
//--------------------------------------------------------------------------------------------------
//#ifdef _DEBUG
//template<class TP>
//	void CSPN_Cmn_2DLine<TP>::AssertValid(CSPN_Cmn_2DPoint<TP>& P)
//	{
//		std::string S;
//		for(int i=0; i<2; i++)
//		{
//			S.Format("%f",P[i]);
//			std::string SzErr("#IND");
//			if(S.FindOneOf(SzErr)>=0)
//			{
//				std::string Stmp;
//				P.TraceFmt(Stmp);
//				::ShowMsg(Stmp);
//				abort();
//			}
//		}
//	};
//
//template<class TP>
//	void CSPN_Cmn_2DLine<TP>::TraceFmt(std::string& StrTrace) const
//	{
//		StrTrace.Format("%sPoint2D<%f,%f>", StrTrace, x(), y());
//	};
//#endif // 
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
													 TP fRadius,							//	圆半径
													 const CSPN_Cmn_2DPoint<TP>& PLine1,	//	线段点1
													 const CSPN_Cmn_2DPoint<TP>& PLine2,	//	线段点2
													 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	交点1
													 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	交点2
													 TP fTol)							//  浮点相等比较时所用容差
{
	if (FLT_EQ_TOL(PLine1.x(), PLine2.x(), fTol) && FLT_EQ_TOL(PLine1.y(), PLine2.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}

	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0)	//	圆半径小于等于0
	{
		return -1;
	}

	int nIntersection = Intersect2D_CircleAndLine(PCenter, fRadius, PLine1, PLine2, PIntersect1, PIntersect2, fTol);

	assert((nIntersection > -1) && (nIntersection < 3));

	//	线段两端点坐标
	TP x1 = PLine1.x();
	TP y1 = PLine1.y();
	TP x2 = PLine2.x();
	TP y2 = PLine2.y();

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(x1, x2, fTol))	//	与Y轴平行
	{
		if (nIntersection == 1)
		{
			nIntersectCount = (((PIntersect1.y() - y1) * (PIntersect1.y() - y2)) <= 0) ? 1 : 0;
		}
		else
		{
			if (nIntersection == 2)
			{
				if (((PIntersect1.y() - y1) * (PIntersect1.y() - y2)) <= 0)
				{
					nIntersectCount++;
				}

				if (((PIntersect2.y() - y1) * (PIntersect2.y() - y2)) <= 0)
				{
					if (nIntersectCount == 0)
					{
						PIntersect1.x(PIntersect2.x());
						PIntersect1.y(PIntersect2.y());
					}
					nIntersectCount++;
				}
			}
		}
	}
	else	//	不是与Y轴平行
	{
		if (nIntersection == 1)
		{
			nIntersectCount = (((PIntersect1.x() - x1) * (PIntersect1.x() - x2)) <= 0) ? 1 : 0;
		}

		if (nIntersection == 2)
		{
			if (((PIntersect1.x() - x1) * (PIntersect1.x() - x2)) <= 0)
			{
				nIntersectCount++;
			}

			if (((PIntersect2.x() - x1) * (PIntersect2.x() - x2)) <= 0)
			{
				if (nIntersectCount == 0)
				{
					PIntersect1.x(PIntersect2.x());
					PIntersect1.y(PIntersect2.y());
				}
				nIntersectCount++;
			}
		}
	}

	return nIntersectCount;	//	返回交点个数
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,		//	圆心坐标
													 TP fRadius,								//	圆半径
													 TP k,									//	斜率
													 TP d,									//	y = k * x + d
													 TP fSectionBegin, TP fSectionEnd,		//	线段范围x
													 CSPN_Cmn_2DPoint<TP>& PIntersect1,			//	交点1
													 CSPN_Cmn_2DPoint<TP>& PIntersect2,			//	交点2
													 TP fTol)								//  浮点相等比较时所用容差
{
	if (FLT_EQ_TOL(fSectionBegin, fSectionEnd, fTol))	//	线段线段长度为0返回-1
	{
		return -1;
	}

	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0)	//	圆半径小于等于0
	{
		return -1;
	}

	int nIntersection = Intersect2D_CircleAndLine(PCenter, fRadius, k, d, PIntersect1, PIntersect2, fTol);

	assert((nIntersection > -1) && (nIntersection < 3));

	int nIntersectCount = 0;

	if (nIntersection == 1)
	{
		nIntersectCount = (((PIntersect1.x() - fSectionBegin) * (PIntersect1.x() - fSectionEnd)) <= 0) ? 1 : 0;
	}
	else
	{
		if (nIntersection == 2)
		{
			if (((PIntersect1.x() - fSectionBegin) * (PIntersect1.x() - fSectionEnd)) <= 0)
			{
				nIntersectCount++;
			}

			if (((PIntersect2.x() - fSectionBegin) * (PIntersect2.x() - fSectionEnd)) <= 0)
			{
				if (nIntersectCount == 0)
				{
					PIntersect1.x(PIntersect2.x());
					PIntersect1.y(PIntersect2.y());
				}
				nIntersectCount++;
			}

		}
	}

	return nIntersectCount;	//	返回交点个数
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
												  TP fRadius,						//	圆半径
												  TP k,								//	斜率
												  TP d,								//	y = k * x + d
												  CSPN_Cmn_2DPoint<TP>& PIntersect1,	//	交点1
												  CSPN_Cmn_2DPoint<TP>& PIntersect2,	//	交点2
												  TP fTol							//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0f)	//	圆半径小于等于0
	{
		return -1;
	}

	//	圆心坐标
	TP x0 = PCenter.x();
	TP y0 = PCenter.y();

	//	一元二次方程系数
	TP a = 1 + k * k;
	TP b = 2 * (k * d - x0 - y0 * k);
	TP c = x0 * x0 + d * d - 2 * y0 * d + y0 * y0 - fRadius * fRadius;

	TP delta = b * b - 4 * a * c;

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(delta, 0.0f, fTol))	//	1个交点。本分支放在前面，是为了防止两个值接近时，电脑认为这两个值相近而且有大小之分
	{
		PIntersect1.x((-1) * b / (2 * a));
		PIntersect1.y(k * PIntersect1.x() + d);

		nIntersectCount = 1;
	}
	else
	{
		if (delta > 0)	//	2个交点
		{
			PIntersect1.x(((-1) * b + sqrt(delta)) / (2 * a));
			PIntersect1.y(k * PIntersect1.x() + d);

			PIntersect2.x(((-1) * b - sqrt(delta)) / (2 * a));
			PIntersect2.y(k * PIntersect2.x() + d);

			nIntersectCount = 2;
		}
	}

	return nIntersectCount;	//	返回交点个数
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	圆心坐标
												  TP fRadius,						//	圆半径
												  const CSPN_Cmn_2DPoint<TP>& PLine1,	//	直线点1
												  const CSPN_Cmn_2DPoint<TP>& PLine2,	//	直线点2
												  CSPN_Cmn_2DPoint<TP>& PIntersect1,	//	交点1
												  CSPN_Cmn_2DPoint<TP>& PIntersect2,	//	交点2
												  TP fTol							//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(PLine1.x(), PLine2.x(), fTol) && FLT_EQ_TOL(PLine1.y(), PLine2.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}

	if (FLT_EQ_TOL<double>(fRadius, 0.0, fTol) || fRadius < 0.0)	//	圆半径小于等于0
	{
		return -1;
	}

	//	圆心坐标
	TP x0 = PCenter.x();
	TP y0 = PCenter.y();

	//	直线坐标
	TP x1 = PLine1.x();
	TP y1 = PLine1.y();
	TP x2 = PLine2.x();
	TP y2 = PLine2.y();

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(x1, x2, fTol))	//	与Y轴平行
	{
		if (FLT_EQ_TOL(abs(x0 - x1), fRadius, fTol))	//	1个交点。本分支放在前面，是为了防止两个值接近时，电脑认为这两个值相近而且有大小之分
		{
			PIntersect1.x(x1);
			PIntersect1.y(y0);

			nIntersectCount = 1;
		}
		else
		{
			if (abs(x0 - x1) < fRadius)	//	2个交点
			{
				PIntersect1.x(x1);
				PIntersect2.x(x1);
				PIntersect1.y(y0 + sqrt(fRadius * fRadius - (x1 - x0) * (x1 - x0)));
				PIntersect2.y(y0 - sqrt(fRadius * fRadius - (x1 - x0) * (x1 - x0)));

				nIntersectCount = 2;
			}
		}
	}
	else
	{
		//	点斜式
		TP k = (PLine2.y() - PLine1.y()) / (PLine2.x() - PLine1.x());
		TP d = (PLine1.x() * PLine2.y() - PLine2.x() * PLine1.y()) / (PLine1.x() - PLine2.x());

		nIntersectCount = Intersect2D_CircleAndLine(PCenter, fRadius, k, d, PIntersect1, PIntersect2, fTol);
	}

	return nIntersectCount;	//	返回交点个数
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndLine(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	第一条直线
												const CSPN_Cmn_2DPoint<TP>& PLine12,	//	第一条直线
												const CSPN_Cmn_2DPoint<TP>& PLine21,	//	第二条直线
												const CSPN_Cmn_2DPoint<TP>& PLine22,	//	第二条直线
												CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
												TP fTol								//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}

	//	两条与Y轴平行
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine11.x(), PLine21.x(), fTol))	//	与Y轴平行重合
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	//	一条与Y轴平行1
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	水平线2
		{
			PIntersect.x(PLine11.x());
			PIntersect.y(PLine21.y());
			return 1;
		}
		else
		{
			PIntersect.x(PLine11.x());
			PIntersect.y((PLine11.x() - PLine21.x()) * (PLine22.y() - PLine21.y()) / (PLine22.x() - PLine21.x()) + PLine21.y());

			return 1;
		}
	}

	//	一条与Y轴平行2
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	水平线1
		{
			PIntersect.x(PLine21.x());
			PIntersect.y(PLine11.y());
			return 1;
		}
		else
		{
			PIntersect.x(PLine21.x());
			PIntersect.y((PLine21.x() - PLine11.x()) * (PLine12.y() - PLine11.y()) / (PLine12.x() - PLine11.x()) + PLine11.y());

			return 1;
		}
	}

	//	两条直线都式斜线时，k1，k2，d1，d2分别是两条值线的斜率和d
	TP k1 = (PLine12.y() - PLine11.y()) / (PLine12.x() - PLine11.x());
	TP k2 = (PLine22.y() - PLine21.y()) / (PLine22.x() - PLine21.x());
	TP d1 = (PLine11.x() * PLine12.y() - PLine12.x() * PLine11.y()) / (PLine11.x() - PLine12.x());
	TP d2 = (PLine21.x() * PLine22.y() - PLine22.x() * PLine21.y()) / (PLine21.x() - PLine22.x());

	//	有一个交点
	int nIntersect = Intersect2D_LineAndLine(k1, d1, k2, d2, PIntersect, fTol);

	return nIntersect;
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndLine(TP k1,							//	第一条直线斜率
												TP d1,							//	第一条直线	y = k * x + d
												TP k2,							//	第二条直线斜率
												TP d2,							//	第二条直线	y = k * x + d
												CSPN_Cmn_2DPoint<TP>& PIntersect,	//	交点
												TP fTol								//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(k1, k2, fTol) && FLT_EQ_TOL(d1, d2, fTol))	//	重合
	{
		return 2;
	}

	if (FLT_EQ_TOL(k1, k2, fTol))	//	平行线，无交点
	{
		return 0;
	}

	//	有一个交点
	TP x = (d2 - d1) / (k1 - k2);
	TP y = k1 * x + d1;
	PIntersect.x(x);
	PIntersect.y(y);

	return 1;
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_SectionAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,		//	第一条线段端点
													  const CSPN_Cmn_2DPoint<TP>& PLine12,		//	第一条线段端点
													  const CSPN_Cmn_2DPoint<TP>& PLine21,		//	第二条线段端点
													  const CSPN_Cmn_2DPoint<TP>& PLine22,		//	第二条线段端点
													  CSPN_Cmn_2DPoint<TP>& PIntersect,			//	交点
													  TP fTol								//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}

	int nIntersect = Intersect2D_LineAndLine(PLine11, PLine12, PLine21, PLine22, PIntersect, fTol);

	if (nIntersect == 1)
	{
		//	与Y轴平行的话，x值相减为0
		if (((PIntersect.x() - PLine11.x()) * (PIntersect.x() - PLine12.x()) <= 0) &&
			((PIntersect.x() - PLine21.x()) * (PIntersect.x() - PLine22.x()) <= 0))
		{
			//------------ While one or to section parallel axis Y begin ------------

			if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol))
			{
				if ((PIntersect.y() - PLine11.y()) * (PIntersect.y() - PLine12.y()) > 0)
				{
					return 0;
				}
			}

			if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
			{
				if ((PIntersect.y() - PLine21.y()) * (PIntersect.y() - PLine22.y()) > 0)
				{
					return 0;
				}
			}
			//------------- While one or to section parallel axis Y end -------------
			return 1;
		}
		else	//	交点在延长线上
		{
			return 0;
		}
	}
	else
	{
		if (nIntersect == 2)
		{
			const CSPN_Cmn_2DPoint<TP> PMax1 = CSPN_Cmn_2DPoint<TP>::Max2D_XFirst(PLine11, PLine12);
			const CSPN_Cmn_2DPoint<TP> PMin1 = CSPN_Cmn_2DPoint<TP>::Min2D_XFirst(PLine11, PLine12);
			const CSPN_Cmn_2DPoint<TP> PMax2 = CSPN_Cmn_2DPoint<TP>::Max2D_XFirst(PLine21, PLine22);
			const CSPN_Cmn_2DPoint<TP> PMin2 = CSPN_Cmn_2DPoint<TP>::Min2D_XFirst(PLine21, PLine22);

			//	两条与Y轴平行
			if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
			{


				if (FLT_EQ_TOL(PMax1.y(), PMin2.y(), fTol))	//	端点相等，有交点
				{
					PIntersect.x(PMax1.x());
					PIntersect.y(PMax1.y());
					return 1;
				}

				if (FLT_EQ_TOL(PMin1.y(), PMax2.y(), fTol))	//	端点相等，有交点
				{
					PIntersect.x(PMin1.x());
					PIntersect.y(PMin1.y());
					return 1;
				}

				if ((PMax1.y() < PMin2.y()) || (PMin1.y() > PMax2.y()))	//	端点分离，没有交点
				{
					return 0;
				}

				return 2;	//	线段重合
			}
			else
			{
				if (FLT_EQ_TOL(PMax1.x(), PMin2.x(), fTol))	//	端点相等，有交点
				{
					PIntersect.x(PMax1.x());
					PIntersect.y(PMax1.y());
					return 1;
				}

				if (FLT_EQ_TOL(PMin1.x(), PMax2.x(), fTol))	//	端点相等，有交点
				{
					PIntersect.x(PMin1.x());
					PIntersect.y(PMin1.y());
					return 1;
				}

				if ((PMax1.x() < PMin2.x()) || (PMin1.x() > PMax2.x()))	//	端点分离，没有交点
				{
					return 0;
				}

				return 2;	//	线段重合
			}
		}
		else
		{
			return 0;	//	平行线无交点
		}
	}
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_SectionAndSection(TP k1,									//	第一条线段斜率
													  TP d1,									//	第一条线段	y = k * x + d
													  TP k2,									//	第二条线段斜率
													  TP d2,									//	第二条线段	y = k * x + d
													  TP fSection1Begin, TP fSection1End,	//	第一条线段范围x
													  TP fSection2Begin, TP fSection2End,	//	第二条线段范围x
													  CSPN_Cmn_2DPoint<TP>& PIntersect,			//	交点
													  TP fTol								//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(fSection1Begin, fSection1End, fTol)
		|| FLT_EQ_TOL(fSection2Begin, fSection2End, fTol))	//	线段长度为0
	{
		return -1;
	}

	int nIntersect = Intersect2D_LineAndLine(k1, d1, k2, d2, PIntersect, fTol);

	if (nIntersect == 1)
	{
		if (((PIntersect.x() - fSection1Begin) * (PIntersect.x() - fSection1End) <= 0) &&
			((PIntersect.x() - fSection2Begin) * (PIntersect.x() - fSection2End) <= 0))
		{
			return 1;
		}
		else	//	交点在延长线上
		{
			return 0;
		}
	}
	else
	{
		if (nIntersect == 2)
		{
			CSPN_Cmn_2DPoint<TP> PLine11(fSection1Begin, k1 * fSection1Begin + d1);
			CSPN_Cmn_2DPoint<TP> PLine12(fSection1End, k1 * fSection1End + d1);
			CSPN_Cmn_2DPoint<TP> PLine21(fSection2Begin, k2 * fSection2Begin + d2);
			CSPN_Cmn_2DPoint<TP> PLine22(fSection2End, k2 * fSection2End + d2);

			const CSPN_Cmn_2DPoint<TP> PMax1 = Max2D_XFirst(PLine11, PLine12);
			const CSPN_Cmn_2DPoint<TP> PMin1 = Min2D_XFirst(PLine11, PLine12);
			const CSPN_Cmn_2DPoint<TP> PMax2 = Max2D_XFirst(PLine21, PLine22);
			const CSPN_Cmn_2DPoint<TP> PMin2 = Min2D_XFirst(PLine21, PLine22);

			if (FLT_EQ_TOL(PMax1.x(), PMin2.x(), fTol))	//	端点相等，有交点
			{
				PIntersect.x(PMax1.x());
				PIntersect.y(PMax1.y());
				return 1;
			}

			if (FLT_EQ_TOL(PMin1.x(), PMax2.x(), fTol))	//	端点相等，有交点
			{
				PIntersect.x(PMin1.x());
				PIntersect.y(PMin1.y());
				return 1;
			}

			if ((PMax1.x() < PMin2.x()) || (PMin1.x() > PMax2.x()))	//	端点分离，没有交点
			{
				return 0;
			}

			return 2;	//	线段重合
		}
		else
		{
			return 0;	//	平行线无交点
		}
	}
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndSection(TP k1,							//	直线斜率
												   TP d1,								//	直线	y = k * x + d
												   TP k2,							//	线段斜率
												   TP d2,							//	线段	y = k * x + d
												   TP fSectionBegin,					//	线段范围x
												   TP fSectionEnd,					//	线段范围x
												   CSPN_Cmn_2DPoint<TP>& PIntersect,	//	交点
												   TP fTol							//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(fSectionBegin, fSectionEnd, fTol))	//	线段长度为0
	{
		return -1;
	}

	int nIntersectCount = Intersect2D_LineAndLine(k1, d1, k2, d2, PIntersect, fTol);

	if (nIntersectCount == 1)
	{
		if ((PIntersect.x() - fSectionBegin) * (PIntersect.x() - fSectionEnd) > 0)	//	交点在延长线上
		{
			nIntersectCount = 0;
		}
	}

	return nIntersectCount;	//	返回交点个数
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,		//	直线端点
												   const CSPN_Cmn_2DPoint<TP>& PLine12,		//	直线端点
												   const CSPN_Cmn_2DPoint<TP>& PLine21,		//	线段端点
												   const CSPN_Cmn_2DPoint<TP>& PLine22,		//	线段端点
												   CSPN_Cmn_2DPoint<TP>& PIntersect,		//	交点
												   TP fTol								//  浮点相等比较时所用容差
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	输入两点相同，无法确定直线或线段
	{
		return -1;
	}

	int nIntersectCount = Intersect2D_LineAndLine(PLine11, PLine12, PLine21, PLine22, PIntersect, fTol);

	if (nIntersectCount == 1)
	{
		//	与Y轴平行的话，x值相减为0
		if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
		{
			if ((PIntersect.y() - PLine21.y()) * (PIntersect.y() - PLine22.y()) > 0)
			{
				nIntersectCount = 0;
			}
		}
		else
		{
			if ((PIntersect.x() - PLine21.x()) * (PIntersect.x() - PLine22.x()) > 0)	//	交点在延长线上
			{
				nIntersectCount = 0;
			}
		}

	}

	return nIntersectCount;	//	返回交点个数
}


typedef CSPN_Cmn_2DLine<int>				Ln2D_Int;
typedef CSPN_Cmn_2DLine<unsigned int>	Ln2D_UInt;

typedef CSPN_Cmn_2DLine<short>			Ln2D_Sht;
typedef CSPN_Cmn_2DLine<unsigned short>	Ln2D_USht;

typedef CSPN_Cmn_2DLine<char>			Ln2D_Char;
typedef CSPN_Cmn_2DLine<unsigned char>	Ln2D_UChar;

typedef CSPN_Cmn_2DLine<float>			Ln2D_Flt;
typedef CSPN_Cmn_2DLine<double>			Ln2D_Dbl;

typedef CSPN_Cmn_2DLine<int>				Ln2D_Idx;


#endif //  // !defined(SPN_Cmn_2DPoint_H__INCLUDED_
