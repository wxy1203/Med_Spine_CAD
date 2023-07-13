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
	|����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
	|-----------------------------------------------------------------------------
	|��;:	����ֱ�����߶μ�Ľ��㣬 ����ʽ�����û�н��㣬���ؽ���ֵ��Ч���߶�(ֱ
	|		��)����Ϊ0�����������ͬ����-1���߶��غϷ���2��PLine1xΪֱ�߶˵�
	*=============================================================================*/
	static int Intersect2D_LineAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	ֱ�߶˵�
										  const CSPN_Cmn_2DPoint<TP>& PLine12,	//	ֱ�߶˵�
										  const CSPN_Cmn_2DPoint<TP>& PLine21,	//	�߶ζ˵�
										  const CSPN_Cmn_2DPoint<TP>& PLine22,	//	�߶ζ˵�
										  CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
										  TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

  /*=============================================================================*
  |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
  |-----------------------------------------------------------------------------
  |��;:	����ֱ�����߶μ�Ľ��㣬 ��бʽ�����û�н��㣬���ؽ���ֵ��Ч���߶γ�
  |		��Ϊ0����-1���߶��غϷ���2����бʽ������б�����������룻k1��d1Ϊֱ
  |		�߲���
  *=============================================================================*/
	static int Intersect2D_LineAndSection(TP k1,							//	ֱ��б��
										  TP d1,							//	ֱ��	y = k * x + d
										  TP k2,							//	�߶�б��
										  TP d2,							//	�߶�	y = k * x + d
										  TP fSectionBegin,				//	�߶η�Χx
										  TP fSectionEnd,					//	�߶η�Χx
										  CSPN_Cmn_2DPoint<TP>& PIntersect,	//	����
										  TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  ������ȱȽ�ʱ�����ݲ�

  /*=============================================================================*
  |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
  |-----------------------------------------------------------------------------
  |��;:	�����߶μ�Ľ��㣬 ��бʽ�����û�н��㣬���ؽ���ֵ��Ч���߶γ�
  |		��Ϊ0����-1���߶��غϷ���2����бʽ������б������������
  *=============================================================================*/
	static int Intersect2D_SectionAndSection(TP k1,								//	��һ���߶�б��
											 TP d1,								//	��һ���߶�	y = k * x + d
											 TP k2,								//	�ڶ����߶�б��
											 TP d2,								//	�ڶ����߶�	y = k * x + d
											 TP fSection1Begin, TP fSection1End,	//	��һ���߶η�Χx
											 TP fSection2Begin, TP fSection2End,	//	�ڶ����߶η�Χx
											 CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
											 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

 /*=============================================================================*
 |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
 |-----------------------------------------------------------------------------
 |��;:	�����߶μ�Ľ��㣬 ����ʽ�����û�н��㣬���ؽ���ֵ��Ч���߶γ�
 |		��Ϊ0��������˵���ͬ����-1���߶��غϷ���2
 |		y = ((y2 - y1 )/(x2 - x1)) * x + ((x1 * y2 - x2 * y1)/(x1 - x2))
 *=============================================================================*/
	static int Intersect2D_SectionAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	��һ���߶ζ˵�
											 const CSPN_Cmn_2DPoint<TP>& PLine12,	//	��һ���߶ζ˵�
											 const CSPN_Cmn_2DPoint<TP>& PLine21,	//	�ڶ����߶ζ˵�
											 const CSPN_Cmn_2DPoint<TP>& PLine22,	//	�ڶ����߶ζ˵�
											 CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
											 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

 /*=============================================================================*
 |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
 |-----------------------------------------------------------------------------
 |��;:	����ֱ�߼�Ľ��㣬 ��бʽ�����û�н��㣬���ؽ���ֵ��Ч���߶��غϷ���2����
 |		бʽ������б������������
 *=============================================================================*/
	static int Intersect2D_LineAndLine(TP k1,							//	��һ��ֱ��б��
									   TP d1,							//	��һ��ֱ��	y = k * x + d
									   TP k2,							//	�ڶ���ֱ��б��
									   TP d2,							//	�ڶ���ֱ��	y = k * x + d
									   CSPN_Cmn_2DPoint<TP>& PIntersect,	//	����
									   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);				//  ������ȱȽ�ʱ�����ݲ�

   /*=============================================================================*
   |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
   |-----------------------------------------------------------------------------
   |��;:	����ֱ�߼�Ľ��㣬����ʽ�����û�н��㣬���ؽ���ֵ��Ч��������˵���ͬ
   |		����-1���߶��غϷ���2
   |		y = ((y2 - y1 )/(x2 - x1)) * x + ((x1 * y2 - x2 * y1)/(x1 - x2))
   *=============================================================================*/
	static int Intersect2D_LineAndLine(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	��һ��ֱ��
									   const CSPN_Cmn_2DPoint<TP>& PLine12,	//	��һ��ֱ��
									   const CSPN_Cmn_2DPoint<TP>& PLine21,	//	�ڶ���ֱ��
									   const CSPN_Cmn_2DPoint<TP>& PLine22,	//	�ڶ���ֱ��
									   CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
									   TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

/*=============================================================================*
|����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
|-----------------------------------------------------------------------------
|��;:	����Բ��ֱ�߽��㣬 ��бʽ��Բ�뾶С�ڵ���0��ֱ�������غϷ���-1�����û
|		�н��㣬����ֵ��Ч����ֻ��һ�����㣬�򽻵�1��Ч��������������㣬������
|		��ֵ��Ч����бʽ������б������������
*=============================================================================*/
	static int Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
										 TP fRadius,							//	Բ�뾶
										 TP k,								//	б��
										 TP d,								//	y = k * x + d
										 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	����1
										 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	����2
										 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

 /*=============================================================================*
 |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
 |-----------------------------------------------------------------------------
 |��;:	����Բ��ֱ�߽��㣬 ����ʽ��Բ�뾶С�ڵ���0��ֱ�������غϷ���-1�����û
 |		�н��㣬����ֵ��Ч����ֻ��һ�����㣬�򽻵�1��Ч��������������㣬������
 |		��ֵ��Ч��
 *=============================================================================*/
	static int Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
										 TP fRadius,							//	Բ�뾶
										 const CSPN_Cmn_2DPoint<TP>& PLine1,	//	ֱ�ߵ�1
										 const CSPN_Cmn_2DPoint<TP>& PLine2,	//	ֱ�ߵ�2
										 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	����1
										 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	����2
										 TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

 /*=============================================================================*
 |����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
 |-----------------------------------------------------------------------------
 |��;:	����Բ���߶ν��㣬 ��бʽ��Բ�뾶С�ڵ���0���߶γ���Ϊ0����-1�����û��
 |		���㣬����ֵ��Ч����ֻ��һ�����㣬�򽻵�1��Ч��������������㣬��������
 |		ֵ��Ч����бʽ������б������������
 *=============================================================================*/
	static int Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
											TP fRadius,							//	Բ�뾶
											TP k,								//	б��
											TP d,								//	y = k * x + d
											TP fSectionBegin, TP fSectionEnd,	//	�߶η�Χx
											CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	����1
											CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	����2
											TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�

	/*=============================================================================*
	|����: |����: int              |ȡֵ             |����  ����ֵ�ǽ������
	|-----------------------------------------------------------------------------
	|��;:	����Բ���߶ν��㣬����ʽ��Բ�뾶С�ڵ���0���߶����˵��غϷ���-1�����û
	|		�н��㣬����ֵ��Ч����ֻ��һ�����㣬�򽻵�1��Ч��������������㣬������
	|		��ֵ��Ч
	*=============================================================================*/
	static int Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
											TP fRadius,							//	Բ�뾶
											const CSPN_Cmn_2DPoint<TP>& PLine1,	//	�߶ζ˵�1
											const CSPN_Cmn_2DPoint<TP>& PLine2,	//	�߶ζ˵�2
											CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	����1
											CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	����2
											TP fTol = CONST_FLT_LINE_INTERSECT_TOL);					//  ������ȱȽ�ʱ�����ݲ�


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
 * �ú��������߶�PA-PB��Բ�ܵĽ���; ��Բ�ٶ���ԭ��(0,0)ΪԲ��, RΪ�뾶.
 * ���: ���޽���, PRslt1 �� PRslt2��ֵ��������;
 *       ����һ������, ����PRslt1; PRslt2��ֵ������;
 *       ������������, �ֱ����PRslt1 �� PRslt2, ��PRslt1����PA, ��PRslt2����PB;
 *       ����ֵ: �������;
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
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
													 TP fRadius,							//	Բ�뾶
													 const CSPN_Cmn_2DPoint<TP>& PLine1,	//	�߶ε�1
													 const CSPN_Cmn_2DPoint<TP>& PLine2,	//	�߶ε�2
													 CSPN_Cmn_2DPoint<TP>& PIntersect1,		//	����1
													 CSPN_Cmn_2DPoint<TP>& PIntersect2,		//	����2
													 TP fTol)							//  ������ȱȽ�ʱ�����ݲ�
{
	if (FLT_EQ_TOL(PLine1.x(), PLine2.x(), fTol) && FLT_EQ_TOL(PLine1.y(), PLine2.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}

	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0)	//	Բ�뾶С�ڵ���0
	{
		return -1;
	}

	int nIntersection = Intersect2D_CircleAndLine(PCenter, fRadius, PLine1, PLine2, PIntersect1, PIntersect2, fTol);

	assert((nIntersection > -1) && (nIntersection < 3));

	//	�߶����˵�����
	TP x1 = PLine1.x();
	TP y1 = PLine1.y();
	TP x2 = PLine2.x();
	TP y2 = PLine2.y();

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(x1, x2, fTol))	//	��Y��ƽ��
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
	else	//	������Y��ƽ��
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

	return nIntersectCount;	//	���ؽ������
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndSection(const CSPN_Cmn_2DPoint<TP>& PCenter,		//	Բ������
													 TP fRadius,								//	Բ�뾶
													 TP k,									//	б��
													 TP d,									//	y = k * x + d
													 TP fSectionBegin, TP fSectionEnd,		//	�߶η�Χx
													 CSPN_Cmn_2DPoint<TP>& PIntersect1,			//	����1
													 CSPN_Cmn_2DPoint<TP>& PIntersect2,			//	����2
													 TP fTol)								//  ������ȱȽ�ʱ�����ݲ�
{
	if (FLT_EQ_TOL(fSectionBegin, fSectionEnd, fTol))	//	�߶��߶γ���Ϊ0����-1
	{
		return -1;
	}

	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0)	//	Բ�뾶С�ڵ���0
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

	return nIntersectCount;	//	���ؽ������
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
												  TP fRadius,						//	Բ�뾶
												  TP k,								//	б��
												  TP d,								//	y = k * x + d
												  CSPN_Cmn_2DPoint<TP>& PIntersect1,	//	����1
												  CSPN_Cmn_2DPoint<TP>& PIntersect2,	//	����2
												  TP fTol							//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(fRadius, 0.0f, fTol) || fRadius < 0.0f)	//	Բ�뾶С�ڵ���0
	{
		return -1;
	}

	//	Բ������
	TP x0 = PCenter.x();
	TP y0 = PCenter.y();

	//	һԪ���η���ϵ��
	TP a = 1 + k * k;
	TP b = 2 * (k * d - x0 - y0 * k);
	TP c = x0 * x0 + d * d - 2 * y0 * d + y0 * y0 - fRadius * fRadius;

	TP delta = b * b - 4 * a * c;

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(delta, 0.0f, fTol))	//	1�����㡣����֧����ǰ�棬��Ϊ�˷�ֹ����ֵ�ӽ�ʱ��������Ϊ������ֵ��������д�С֮��
	{
		PIntersect1.x((-1) * b / (2 * a));
		PIntersect1.y(k * PIntersect1.x() + d);

		nIntersectCount = 1;
	}
	else
	{
		if (delta > 0)	//	2������
		{
			PIntersect1.x(((-1) * b + sqrt(delta)) / (2 * a));
			PIntersect1.y(k * PIntersect1.x() + d);

			PIntersect2.x(((-1) * b - sqrt(delta)) / (2 * a));
			PIntersect2.y(k * PIntersect2.x() + d);

			nIntersectCount = 2;
		}
	}

	return nIntersectCount;	//	���ؽ������
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_CircleAndLine(const CSPN_Cmn_2DPoint<TP>& PCenter,	//	Բ������
												  TP fRadius,						//	Բ�뾶
												  const CSPN_Cmn_2DPoint<TP>& PLine1,	//	ֱ�ߵ�1
												  const CSPN_Cmn_2DPoint<TP>& PLine2,	//	ֱ�ߵ�2
												  CSPN_Cmn_2DPoint<TP>& PIntersect1,	//	����1
												  CSPN_Cmn_2DPoint<TP>& PIntersect2,	//	����2
												  TP fTol							//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(PLine1.x(), PLine2.x(), fTol) && FLT_EQ_TOL(PLine1.y(), PLine2.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}

	if (FLT_EQ_TOL<double>(fRadius, 0.0, fTol) || fRadius < 0.0)	//	Բ�뾶С�ڵ���0
	{
		return -1;
	}

	//	Բ������
	TP x0 = PCenter.x();
	TP y0 = PCenter.y();

	//	ֱ������
	TP x1 = PLine1.x();
	TP y1 = PLine1.y();
	TP x2 = PLine2.x();
	TP y2 = PLine2.y();

	int nIntersectCount = 0;

	if (FLT_EQ_TOL(x1, x2, fTol))	//	��Y��ƽ��
	{
		if (FLT_EQ_TOL(abs(x0 - x1), fRadius, fTol))	//	1�����㡣����֧����ǰ�棬��Ϊ�˷�ֹ����ֵ�ӽ�ʱ��������Ϊ������ֵ��������д�С֮��
		{
			PIntersect1.x(x1);
			PIntersect1.y(y0);

			nIntersectCount = 1;
		}
		else
		{
			if (abs(x0 - x1) < fRadius)	//	2������
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
		//	��бʽ
		TP k = (PLine2.y() - PLine1.y()) / (PLine2.x() - PLine1.x());
		TP d = (PLine1.x() * PLine2.y() - PLine2.x() * PLine1.y()) / (PLine1.x() - PLine2.x());

		nIntersectCount = Intersect2D_CircleAndLine(PCenter, fRadius, k, d, PIntersect1, PIntersect2, fTol);
	}

	return nIntersectCount;	//	���ؽ������
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndLine(const CSPN_Cmn_2DPoint<TP>& PLine11,	//	��һ��ֱ��
												const CSPN_Cmn_2DPoint<TP>& PLine12,	//	��һ��ֱ��
												const CSPN_Cmn_2DPoint<TP>& PLine21,	//	�ڶ���ֱ��
												const CSPN_Cmn_2DPoint<TP>& PLine22,	//	�ڶ���ֱ��
												CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
												TP fTol								//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}

	//	������Y��ƽ��
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine11.x(), PLine21.x(), fTol))	//	��Y��ƽ���غ�
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	//	һ����Y��ƽ��1
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	ˮƽ��2
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

	//	һ����Y��ƽ��2
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
	{
		if (FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	ˮƽ��1
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

	//	����ֱ�߶�ʽб��ʱ��k1��k2��d1��d2�ֱ�������ֵ�ߵ�б�ʺ�d
	TP k1 = (PLine12.y() - PLine11.y()) / (PLine12.x() - PLine11.x());
	TP k2 = (PLine22.y() - PLine21.y()) / (PLine22.x() - PLine21.x());
	TP d1 = (PLine11.x() * PLine12.y() - PLine12.x() * PLine11.y()) / (PLine11.x() - PLine12.x());
	TP d2 = (PLine21.x() * PLine22.y() - PLine22.x() * PLine21.y()) / (PLine21.x() - PLine22.x());

	//	��һ������
	int nIntersect = Intersect2D_LineAndLine(k1, d1, k2, d2, PIntersect, fTol);

	return nIntersect;
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndLine(TP k1,							//	��һ��ֱ��б��
												TP d1,							//	��һ��ֱ��	y = k * x + d
												TP k2,							//	�ڶ���ֱ��б��
												TP d2,							//	�ڶ���ֱ��	y = k * x + d
												CSPN_Cmn_2DPoint<TP>& PIntersect,	//	����
												TP fTol								//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(k1, k2, fTol) && FLT_EQ_TOL(d1, d2, fTol))	//	�غ�
	{
		return 2;
	}

	if (FLT_EQ_TOL(k1, k2, fTol))	//	ƽ���ߣ��޽���
	{
		return 0;
	}

	//	��һ������
	TP x = (d2 - d1) / (k1 - k2);
	TP y = k1 * x + d1;
	PIntersect.x(x);
	PIntersect.y(y);

	return 1;
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_SectionAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,		//	��һ���߶ζ˵�
													  const CSPN_Cmn_2DPoint<TP>& PLine12,		//	��һ���߶ζ˵�
													  const CSPN_Cmn_2DPoint<TP>& PLine21,		//	�ڶ����߶ζ˵�
													  const CSPN_Cmn_2DPoint<TP>& PLine22,		//	�ڶ����߶ζ˵�
													  CSPN_Cmn_2DPoint<TP>& PIntersect,			//	����
													  TP fTol								//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}

	int nIntersect = Intersect2D_LineAndLine(PLine11, PLine12, PLine21, PLine22, PIntersect, fTol);

	if (nIntersect == 1)
	{
		//	��Y��ƽ�еĻ���xֵ���Ϊ0
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
		else	//	�������ӳ�����
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

			//	������Y��ƽ��
			if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
			{


				if (FLT_EQ_TOL(PMax1.y(), PMin2.y(), fTol))	//	�˵���ȣ��н���
				{
					PIntersect.x(PMax1.x());
					PIntersect.y(PMax1.y());
					return 1;
				}

				if (FLT_EQ_TOL(PMin1.y(), PMax2.y(), fTol))	//	�˵���ȣ��н���
				{
					PIntersect.x(PMin1.x());
					PIntersect.y(PMin1.y());
					return 1;
				}

				if ((PMax1.y() < PMin2.y()) || (PMin1.y() > PMax2.y()))	//	�˵���룬û�н���
				{
					return 0;
				}

				return 2;	//	�߶��غ�
			}
			else
			{
				if (FLT_EQ_TOL(PMax1.x(), PMin2.x(), fTol))	//	�˵���ȣ��н���
				{
					PIntersect.x(PMax1.x());
					PIntersect.y(PMax1.y());
					return 1;
				}

				if (FLT_EQ_TOL(PMin1.x(), PMax2.x(), fTol))	//	�˵���ȣ��н���
				{
					PIntersect.x(PMin1.x());
					PIntersect.y(PMin1.y());
					return 1;
				}

				if ((PMax1.x() < PMin2.x()) || (PMin1.x() > PMax2.x()))	//	�˵���룬û�н���
				{
					return 0;
				}

				return 2;	//	�߶��غ�
			}
		}
		else
		{
			return 0;	//	ƽ�����޽���
		}
	}
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_SectionAndSection(TP k1,									//	��һ���߶�б��
													  TP d1,									//	��һ���߶�	y = k * x + d
													  TP k2,									//	�ڶ����߶�б��
													  TP d2,									//	�ڶ����߶�	y = k * x + d
													  TP fSection1Begin, TP fSection1End,	//	��һ���߶η�Χx
													  TP fSection2Begin, TP fSection2End,	//	�ڶ����߶η�Χx
													  CSPN_Cmn_2DPoint<TP>& PIntersect,			//	����
													  TP fTol								//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(fSection1Begin, fSection1End, fTol)
		|| FLT_EQ_TOL(fSection2Begin, fSection2End, fTol))	//	�߶γ���Ϊ0
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
		else	//	�������ӳ�����
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

			if (FLT_EQ_TOL(PMax1.x(), PMin2.x(), fTol))	//	�˵���ȣ��н���
			{
				PIntersect.x(PMax1.x());
				PIntersect.y(PMax1.y());
				return 1;
			}

			if (FLT_EQ_TOL(PMin1.x(), PMax2.x(), fTol))	//	�˵���ȣ��н���
			{
				PIntersect.x(PMin1.x());
				PIntersect.y(PMin1.y());
				return 1;
			}

			if ((PMax1.x() < PMin2.x()) || (PMin1.x() > PMax2.x()))	//	�˵���룬û�н���
			{
				return 0;
			}

			return 2;	//	�߶��غ�
		}
		else
		{
			return 0;	//	ƽ�����޽���
		}
	}
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndSection(TP k1,							//	ֱ��б��
												   TP d1,								//	ֱ��	y = k * x + d
												   TP k2,							//	�߶�б��
												   TP d2,							//	�߶�	y = k * x + d
												   TP fSectionBegin,					//	�߶η�Χx
												   TP fSectionEnd,					//	�߶η�Χx
												   CSPN_Cmn_2DPoint<TP>& PIntersect,	//	����
												   TP fTol							//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(fSectionBegin, fSectionEnd, fTol))	//	�߶γ���Ϊ0
	{
		return -1;
	}

	int nIntersectCount = Intersect2D_LineAndLine(k1, d1, k2, d2, PIntersect, fTol);

	if (nIntersectCount == 1)
	{
		if ((PIntersect.x() - fSectionBegin) * (PIntersect.x() - fSectionEnd) > 0)	//	�������ӳ�����
		{
			nIntersectCount = 0;
		}
	}

	return nIntersectCount;	//	���ؽ������
}

template<class TP>
int CSPN_Cmn_2DLine<TP>::Intersect2D_LineAndSection(const CSPN_Cmn_2DPoint<TP>& PLine11,		//	ֱ�߶˵�
												   const CSPN_Cmn_2DPoint<TP>& PLine12,		//	ֱ�߶˵�
												   const CSPN_Cmn_2DPoint<TP>& PLine21,		//	�߶ζ˵�
												   const CSPN_Cmn_2DPoint<TP>& PLine22,		//	�߶ζ˵�
												   CSPN_Cmn_2DPoint<TP>& PIntersect,		//	����
												   TP fTol								//  ������ȱȽ�ʱ�����ݲ�
)
{
	if (FLT_EQ_TOL(PLine11.x(), PLine12.x(), fTol) && FLT_EQ_TOL(PLine11.y(), PLine12.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}
	if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol) && FLT_EQ_TOL(PLine21.y(), PLine22.y(), fTol))	//	����������ͬ���޷�ȷ��ֱ�߻��߶�
	{
		return -1;
	}

	int nIntersectCount = Intersect2D_LineAndLine(PLine11, PLine12, PLine21, PLine22, PIntersect, fTol);

	if (nIntersectCount == 1)
	{
		//	��Y��ƽ�еĻ���xֵ���Ϊ0
		if (FLT_EQ_TOL(PLine21.x(), PLine22.x(), fTol))
		{
			if ((PIntersect.y() - PLine21.y()) * (PIntersect.y() - PLine22.y()) > 0)
			{
				nIntersectCount = 0;
			}
		}
		else
		{
			if ((PIntersect.x() - PLine21.x()) * (PIntersect.x() - PLine22.x()) > 0)	//	�������ӳ�����
			{
				nIntersectCount = 0;
			}
		}

	}

	return nIntersectCount;	//	���ؽ������
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
