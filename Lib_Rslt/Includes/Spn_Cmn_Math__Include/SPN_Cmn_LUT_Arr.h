// SPN_Cmn_LUT_Arr.h: interface for the CSPN_Cmn_LUT_Arr class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_LUT_ARR_H__INCLUDED_
#define SPN_Cmn_LUT_ARR_H__INCLUDED_


#	pragma once



#include "SPN_Cmn_CArray.h"
#include "SPN_Cmn_Science.h"

const float FLT_MIN_2 = FLT_MIN * 2;

template<class TPVar, class TPFun>
class CSPN_Cmn_LUT_Arr : public CSPN_Cmn_CArray<TPFun, TPFun>
{
public:
	CSPN_Cmn_LUT_Arr();
	virtual ~CSPN_Cmn_LUT_Arr();

public:
	inline TPFun LUT_AtDst_FromStart(const TPVar tpVarDst)	const;//���վ������������ȡ��ֵ
	inline TPFun LUT_AtPos(const TPVar tpVarPos)	const;//����λ�ü���������ȡ��ֵ

	inline TPVar GetPos(const int i) const { return m_tpVarStart + i * m_tpVarSpacing; };//����������λ��

	//ȡ�����������:
	inline int GetIdx_AtPos_Near(const TPVar tpVarPos) const
	{
		//[12_8 15:59:28 ]:int i = (tpVarPos - m_tpVarStart) / m_tpVarSpacing + 0.5f; 
		int i = (tpVarPos - m_tpVarStart) * m_tpVarSpcInvrs + 0.5f;
		i = __max(i, 0);
		i = __min(i, (*this).GetUpperBound());
		return i;
	};

	//ȡ��ǰ���ٽ�������:
	inline int GetIdx_AtPos_Floor(const TPVar tpVarPos) const
	{
		//[12_8 15:59:33 ]:int i = floor((tpVarPos - m_tpVarStart) / m_tpVarSpacing); 
		int i = floor((tpVarPos - m_tpVarStart)  * m_tpVarSpcInvrs);
		i = __max(i, 0);
		i = __min(i, (*this).GetUpperBound());
		return i;
	};

	//ȡ�ú����ٽ�������:
	inline int GetIdx_AtPos_Ceil(const TPVar tpVarPos) const
	{
		//[12_8 15:59:58 ]:int i = ceil((tpVarPos - m_tpVarStart) / m_tpVarSpacing); 
		int i = ceil((tpVarPos - m_tpVarStart)  * m_tpVarSpcInvrs);
		i = __max(i, 0);
		i = __min(i, (*this).GetUpperBound());
		return i;
	};

	inline void GetValidPosRange(TPVar& tpVarPosMin, TPVar& tpVarPosMax) const
	{
		tpVarPosMin = m_tpVarStart;
		tpVarPosMax = m_tpVarStart + (*this).GetUpperBound()*m_tpVarSpacing;
		if (tpVarPosMin > tpVarPosMax)
		{
			ExchangeValue<TPVar>(tpVarPosMin, tpVarPosMax);
		}
	}

	inline TPVar GetP3D_Spc() const { return m_tpVarSpacing; };
	inline void  SetSpacing(const TPVar tpVarSpc) { m_tpVarSpacing = tpVarSpc; };

	inline TPVar GetStart() const { return m_tpVarStart; };
	inline void  SetStart(const TPVar tpVarStart) { m_tpVarStart = tpVarStart; };

	inline void Copy(const CSPN_Cmn_LUT_Arr& LUTSrc)
	{
		SetStart(LUTSrc.GetStart());
		SetSpacing(LUTSrc.GetP3D_Spc());
		CSPN_Cmn_CArray<TPFun, TPFun>::Copy(LUTSrc);
	};

	inline void Construct(const CArrayT<TPFun, TPFun>& ArrFunValue, const TPVar tpVarStart, const TPVar tpVarSpacing)
	{
		CSPN_Cmn_CArray<TPFun, TPFun>::Copy(ArrFunValue);
		m_tpVarStart = tpVarStart;
		m_tpVarSpacing = tpVarSpacing;

		if (FLT_EQ(m_tpVarSpacing, 0))//[12_8 15:58:06 ]:
		{
			m_tpVarSpcInvrs = 0;
		}
		else
		{
			m_tpVarSpcInvrs = 1.0 / m_tpVarSpacing;
		}
	};

	inline BOOL IsValidPos(TPVar vVar) const
	{
		//[12_8 16:00:24 ]:int iPos = fRound((vVar - m_tpVarStart) / m_tpVarSpacing);
		int iPos = fRound((vVar - m_tpVarStart)  * m_tpVarSpcInvrs);
		return (iPos >= 0 && iPos < this->GetSize());
	};

	//virtual void Serialize(CSPN_Cmn_Archive& Ar);

protected:
	TPVar m_tpVarStart = 0;
	TPVar m_tpVarSpacing = 1;
	TPVar m_tpVarSpcInvrs = 1; //[12_8 15:58:17 ]: Ϊ������������ٶ�
};
//-----------------------------------------------------------------------------

template<class TPVar, class TPFun>
CSPN_Cmn_LUT_Arr<TPVar, TPFun>::~CSPN_Cmn_LUT_Arr() {};

//-----------------------------------------------------------------------------

template<class TPVar, class TPFun>
CSPN_Cmn_LUT_Arr<TPVar, TPFun>::CSPN_Cmn_LUT_Arr()
{
	m_tpVarStart = 0;
	m_tpVarSpacing = 1;
};

//-----------------------------------------------------------------------------

//template<class TPVar, class TPFun>
//void CSPN_Cmn_LUT_Arr<TPVar, TPFun>::Serialize(CSPN_Cmn_Archive& Ar)
//{
//	if (Ar.IsStoring())
//	{
//		int iVer = 1;
//		Ar << iVer;
//
//		Ar << this->GetSize();
//		for (int i = 0; i < this->GetSize(); i++)
//		{
//			Ar << (*this)[i];
//		}
//
//		Ar << m_tpVarStart;
//		Ar << m_tpVarSpacing;
//	}
//	else
//	{
//		int iVer = 0;
//		Ar >> iVer;
//		int i = 0;
//		int nSize = 0;
//		switch (iVer)
//		{
//		case 1:
//			Ar >> nSize;
//			(*this).SetSize(nSize);
//			for (int i = 0; i < this->GetSize(); i++)
//			{
//				Ar >> (*this)[i];
//			}
//
//			Ar >> m_tpVarStart;
//			Ar >> m_tpVarSpacing;
//			if (FLT_EQ(m_tpVarSpacing, 0))//[12_8 15:58:06 ]:
//			{
//				m_tpVarSpcInvrs = 0;
//			}
//			else
//			{
//				m_tpVarSpcInvrs = 1.0 / m_tpVarSpacing;
//			}
//
//			break;
//		default:
//			::ShowMsg("�����޷�ʶ��Ķ���汾: CSPN_Cmn_LUT_Arr!!!");
//		}
//	}
//}

//-----------------------------------------------------------------------------

template<class TPVar, class TPFun>
inline TPFun CSPN_Cmn_LUT_Arr<TPVar, TPFun>::LUT_AtDst_FromStart(const TPVar tpVarDst) const
{
	//assert(fRound(tpVarDst / m_tpVarSpacing) >= 0);
	//assert(fRound(tpVarDst / m_tpVarSpacing) < this->GetSize());
	assert(fRound(tpVarDst * m_tpVarSpcInvrs) >= 0);
	assert(fRound(tpVarDst * m_tpVarSpcInvrs) < this->GetSize());

	//[12_8 16:01:12 ]:return this->GetAt( fRound(tpVarDst / m_tpVarSpacing) );
	return this->GetAt(fRound(tpVarDst  * m_tpVarSpcInvrs));
}

//-----------------------------------------------------------------------------

template<class TPVar, class TPFun>
inline TPFun CSPN_Cmn_LUT_Arr<TPVar, TPFun>::LUT_AtPos(const TPVar tpVarPos) const
{
	assert(IsValidPos(tpVarPos));

	//[12_8 16:01:37 ]:return GetAt(fRound((tpVarPos - m_tpVarStart) / m_tpVarSpacing));
	return this->GetAt(fRound((tpVarPos - m_tpVarStart)  * m_tpVarSpcInvrs));
}

//-----------------------------------------------------------------------------

#endif //  // !defined(SPN_Cmn_LUT_ARR_H__INCLUDED_
