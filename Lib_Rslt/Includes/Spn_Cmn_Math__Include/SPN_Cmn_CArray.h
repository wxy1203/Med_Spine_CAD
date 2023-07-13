
#ifndef AFX_CSPN_Cmn_CArray_H__INCLUDED_
#define AFX_CSPN_Cmn_CArray_H__INCLUDED_


#	pragma once


#include "_From_MFC_afxtempl.h"

/*
 * Template Class:	CSPN_Cmn_CArray
 * Author:			Russell Robinson
 * Purpose:
 *		To provide a generic array class like CArrayT without the problems.
 *		CSPN_Cmn_CArray takes one parameter - TYPE.  Unlike CArrayT, CSPN_Cmn_CArray always
 *		returns references and expects references as parameters.
 */
template <class TYPE, class ARG_TYPE = TYPE & > class CSPN_Cmn_CArray : public CArrayT<TYPE, ARG_TYPE>
{
public:
	inline void CopyFromVector(const std::vector<TYPE>& Vct)//[20210716_09:29:58 ]:
	{
		this->SetSize(Vct.size());
		if (Vct.size() > 0)
		{
			const TYPE& E0 = Vct[0];
			::memcpy((*this).GetData(), &(E0), sizeof(TYPE)*Vct.size());
		}
	};
	inline void CopyToVector(std::vector<TYPE>& Vct) const//[20210716_09:30:03 ]:
	{
		Vct.resize((*this).GetSize());
		if ((*this).GetSize() > 0)
		{
			::memcpy(&(Vct[0]), (*this).GetData(), sizeof(TYPE)*Vct.size());
		}
	};

public:
	/*
	 * Method:		CSPN_Cmn_CArray::operator[] const
	 * Parameters:	i_index			the array index to access
	 * Returns:		const TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for const access.
	 */
	inline const TYPE&	operator[](int i_index) const
	{
		assert(0 <= i_index && i_index < (*this).GetSize());
		return ((*this).m_pData[i_index]);
	};

	/*
	 * Method:		CSPN_Cmn_CArray::this->GetAt
	 * Parameters:	i_index			the array index to access
	 * Returns:		const TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for const access.
	 */
	inline const TYPE&	GetAt(int i_index) const
	{
		assert(0 <= i_index && i_index < (*this).GetSize());
		return ((*this).m_pData[i_index]);
	};

	/*
	 * Method:		CSPN_Cmn_CArray::operator[]
	 * Parameters:	i_index		the array index to access
	 * Returns:		TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for possible modification.
	 *		This method is needed because the compiler loses the base class's method.
	 */
	inline TYPE& operator[](int i_index)
	{
		assert(0 <= i_index && i_index < (*this).GetSize());
		return ((*this).m_pData[i_index]);
	};

	//*************************************************************************************
	//����Ϊ���ú�����չ
	TYPE GetMin(int* pIdxMin = nullptr) const;
	TYPE GetMax(int* pIdxMax = nullptr) const;
	TYPE GetMin_inRgn(int iB, int iE, int* pIdxMin = nullptr) const;
	TYPE GetMax_inRgn(int iB, int iE, int* pIdxMax = nullptr) const;
	TYPE GetMax_Abs(int* pIdxMax = nullptr) const
	{
		int iMax = -1;
		TYPE vMaxAbs = qAbs<TYPE>(GetMax(&iMax));

		int iMin = -1;
		TYPE vMinAbs = qAbs<TYPE>(GetMin(&iMin));

		if (vMaxAbs > vMinAbs)
		{
			if (pIdxMax)
			{
				*pIdxMax = iMax;
			}
			return vMaxAbs;
		}
		else
		{
			if (pIdxMax)
			{
				*pIdxMax = iMin;
			}
			return vMinAbs;
		}
	};
	TYPE GetMin_Abs(int* pIdxMin = nullptr) const
	{
		int iMax = -1;
		TYPE vMaxAbs = qAbs<TYPE>(GetMax(&iMax));

		int iMin = -1;
		TYPE vMinAbs = qAbs<TYPE>(GetMin(&iMin));

		if (vMaxAbs < vMinAbs)
		{
			if (pIdxMin)
			{
				*pIdxMin = iMax;
			}
			return vMaxAbs;
		}
		else
		{
			if (pIdxMin)
			{
				*pIdxMin = iMin;
			}
			return vMinAbs;
		}
	};

	void GetMinMax(TYPE& vMin, TYPE& vMax) const;
	TYPE GetWaveBandWidth() const;
	void SetAllMember(TYPE vIni)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] = vIni;
		}
	};

	TYPE SumAll()
	{
		TYPE vSumAll = 0;
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			vSumAll += (*this).m_pData[i];
		}
		return vSumAll;
	};

	TYPE& GetFirst() { return (*this)[0]; };
	TYPE& GetLast() { return (*this)[(*this).GetUpperBound()]; };
	void FlipBgn2End()
	{
		int iMax = (*this).GetUpperBound();
		int iMid = (*this).GetSize() / 2;
#pragma omp parallel for
		for (int i = 0; i < iMid; i++)
		{
			TYPE vTmp = (*this).m_pData[i];
			(*this).m_pData[i] = (*this).m_pData[iMax - i];
			(*this).m_pData[iMax - i] = vTmp;
		}
	}

	template<typename TPOther>
	void operator+=(TPOther fV)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] += fV;
		}
	};
	template<typename TPOther, typename TPOtherRef = TPOther>
	void operator+=(const CSPN_Cmn_CArray<TPOther, TPOtherRef>& Arr)
	{
		assert((*this).GetSize() == Arr.GetSize());
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] += Arr[i];
		}
	};
	template<typename TPOther>
	void operator+=(TPOther* pDatBuf)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] += pDatBuf[i];
		}
	};

	template<typename TPOther>
	void operator-=(TPOther fV)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] -= fV;
		}
	};

	template<typename TPOther, typename TPOtherRef = TPOther>
	void operator-=(const CSPN_Cmn_CArray<TPOther, TPOtherRef>& Arr)
	{
		assert((*this).GetSize() == Arr.GetSize());
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] -= Arr[i];
		}
	};
	template<typename TPOther>
	void operator-=(TPOther* pDatBuf)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] -= pDatBuf[i];
		}
	};

	template<typename TPOther>
	void operator*=(TPOther fV)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] *= fV;
		}
	};
	template<typename TPOther, typename TPOtherRef = TPOther>
	void operator*=(const CSPN_Cmn_CArray<TPOther, TPOtherRef>& Arr)
	{
		assert((*this).GetSize() == Arr.GetSize());
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] *= Arr[i];
		}
	};
	template<typename TPOther>
	void operator*=(TPOther* pDatBuf)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] *= pDatBuf[i];
		}
	};

	template<typename TPOther>
	void operator/=(TPOther fV)
	{
		assert(fV > 0 || fV < 0);
		double fV_Invrs = 1.0 / fV;
		(*this) *= fV_Invrs;
	};

	template<typename TPOther, typename TPOtherRef = TPOther>
	void operator/=(const CSPN_Cmn_CArray<TPOther, TPOtherRef&>& Arr)
	{
		assert((*this).GetSize() == Arr.GetSize());
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] /= Arr[i];
		}
	};
	template<typename TPOther>
	void operator/=(TPOther* pDatBuf)
	{
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this).m_pData[i] /= pDatBuf[i];
		}
	};

	template<typename TPOther>
	void CopyMember(TPOther* pElemSrc, int n)
	{
		(*this).SetSize(n);
		TYPE* pDst = (*this).m_pData;
		TPOther* pSrc = pElemSrc;
		for (int i = 0; i < n; i++)
		{
			*pDst++ = *pSrc++;
		}
	};

	bool Offset_AllElem_by_SomeElemAvgTo(int* pIdxSomeElemToAvg, int nElemAvg, float fAvgTgt)
	{
		float fAvgOld = 0.f;
		//[20210415_19:46:35 ]:int nElemAvgUse = std::min<int>(nElemAvg, (*this).GetSize());
		if (nElemAvg <= 0 || nElemAvg >= (*this).GetSize())
		{
			return false;
		}

		for (int iA = 0; iA < nElemAvg; iA++)
		{
			fAvgOld += (*this).m_pData[pIdxSomeElemToAvg[iA]];
		}
		fAvgOld /= nElemAvg;

		float fOfst = fAvgTgt - fAvgOld;
		TYPE vOfst = CSPN_TypeValue<TYPE, float>::TransformValue(fOfst);

		(*this) += vOfst;

		return true;
	};

	float GetAvg()
	{
		if ((*this).GetSize() <= 0)
		{
			return FLT_MAX;
		}

		float fAvg = 0.f;
		for (int iA = 0; iA < (*this).GetSize(); iA++)
		{
			fAvg += (*this)[iA];
		}
		fAvg /= (*this).GetSize();

		return fAvg;
	};

	float GetAvg_by_SomeElem(int* pIdxSomeElemToAvg, int nElemAvg)
	{
		float fAvg = 0.f;
		//[20210415_19:46:35 ]:int nElemAvgUse = std::min<int>(nElemAvg, (*this).GetSize());
		if (nElemAvg <= 0 || nElemAvg >= (*this).GetSize())
		{
			return false;
		}

		for (int iA = 0; iA < nElemAvg; iA++)
		{
			fAvg += (*this).m_pData[pIdxSomeElemToAvg[iA]];
		}
		fAvg /= nElemAvg;

		return fAvg;
	};

	void NomalizeSumTo(float fNormTgt)//[5_23 17:42:43 ]:
	{
		float fSum = 0.f;
		for (int i = 0; i < (*this).GetSize(); i++)
		{
			fSum += this->GetAt(i);
		}

		float fK = (FLT_EQ(0.f, fSum) ?
			(0)
					:
					(fNormTgt / fSum));

		for (int i = 0; i < (*this).GetSize(); i++)
		{
			(*this)[i] *= fK;
		}
	};

	//inline bool WriteStream(std::fstream& FStream)
	//{
	//	bool bOK = false;
	//	if (FStream.is_open())
	//	{
	//		static int iVer = 1;
	//		FStream.write((char*)&iVer, sizeof(int));
	//
	//		int nElem = (*this).GetSize();
	//		FStream.write((char*)&nElem, sizeof(int));
	//		FStream.write((char*)(*this).GetData(), sizeof(TYPE) * nElem);
	//		bOK = true;
	//	}
	//	else
	//	{
	//		bOK = false;
	//	}
	//	return bOK;
	//};
	//
	//inline bool ReadStream(std::fstream& FStream)
	//{
	//	bool bOK = false;
	//
	//	int iVer = 0;
	//	FStream.read((char*)&iVer, sizeof(int));
	//
	//	switch (iVer)
	//	{
	//	case 1:
	//	{
	//		int nElem = 0;
	//		FStream.read((char*)&nElem, sizeof(int));
	//
	//		this->SetSize(nElem);
	//		FStream.read((char*)(*this).GetData(), sizeof(TYPE) * nElem);
	//		bOK = true;
	//	}
	//	break;
	//	default:
	//		;//::ShowMsg (/*_T*/("�����޷�ʶ���CSPN_Cmn_3DMtx����汾!!!"));
	//		bOK = false;
	//	}
	//
	//	return bOK;
	//};
};

template<typename TPDst, typename TPSrc>
void CopyMemberSet_into_Arr(CSPN_Cmn_CArray<TPDst, TPDst>& ArrDst, TPSrc* pElemSrc, int n)
{
	ArrDst.SetSize(n);
	TPDst* pDst = ArrDst.GetData();
	TPSrc* pSrc = pElemSrc;
	for (int i = 0; i < n; i++)
	{
		*pDst++ = *pSrc++;
	}
};

template<typename TPDst, typename TPSrc>
void CopyMemberSet_into_Arr(CSPN_Cmn_CArray<TPDst, TPDst&>& ArrDst, TPSrc* pElemSrc, int n)
{
	ArrDst.SetSize(n);
	TPDst* pDst = ArrDst.GetData();
	TPSrc* pSrc = pElemSrc;
	for (int i = 0; i < n; i++)
	{
		*pDst++ = *pSrc++;
	}
};

template<typename TPDst, typename TPSrc>
void CopyArr_into_MemberSet(TPDst* pElemDst, int n, CSPN_Cmn_CArray<TPSrc, TPSrc>& ArrSrc)
{
	assert(n <= ArrSrc.GetSize());
	TPDst* pDst = pElemDst;
	TPSrc* pSrc = ArrSrc.GetData();
	for (int i = 0; i < n; i++)
	{
		*pDst++ = *pSrc++;
	}
};

template<typename TPDst, typename TPSrc>
void CopyArr_into_MemberSet(TPDst* pElemDst, int n, CSPN_Cmn_CArray<TPSrc, TPSrc&>& ArrSrc)
{
	assert(n <= ArrSrc.GetSize());
	TPDst* pDst = pElemDst;
	TPSrc* pSrc = ArrSrc.GetData();
	for (int i = 0; i < n; i++)
	{
		*pDst++ = *pSrc++;
	}
};

//----------------------------------------------------------------------------------
typedef CSPN_Cmn_CArray<BYTE, BYTE>		ArrBYTE_TP;
typedef CSPN_Cmn_CArray<short, short>	ArrShort_TP;
typedef CSPN_Cmn_CArray<long, long>		ArrLong_TP;
typedef CSPN_Cmn_CArray<UINT, UINT>		ArrUINT_TP;
typedef CSPN_Cmn_CArray<int, int>		ArrInt_TP;
typedef CSPN_Cmn_CArray<bool, bool>		ArrBool_TP;

typedef CSPN_Cmn_CArray<float, float>	ArrFlt_TP;
typedef CSPN_Cmn_CArray<double, double>	ArrDbl_TP;

typedef CSPN_Cmn_CArray<void*, void*>	ArrPtr_TP;

template<class TYPE, class ARG_TYPE>
TYPE CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetMin(int* pIdxMin/* = nullptr*/) const
{
	if ((*this).GetSize() == 0)
		return 0;

	int iIdxMin = -1;

	TYPE vMin = this->GetAt(0);
	iIdxMin = 0;

	int iElem = (*this).GetSize();
	while (iElem--)
	{
		TYPE vTmp = this->GetAt(iElem);
		if (vTmp < vMin)
		{
			vMin = vTmp;
			iIdxMin = iElem;
		}
	}

	if (pIdxMin)
	{
		*pIdxMin = iIdxMin;
	}

	return vMin;
};

//----------------------------------------------------------------------------------

template<class TYPE, class ARG_TYPE>
TYPE CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetMax(int* pIdxMax/* = nullptr*/) const
{
	if ((*this).GetSize() == 0)
		return 0;

	int iIdxMax = -1;

	TYPE vMax = this->GetAt(0);
	iIdxMax = 0;

	int iElem = (*this).GetSize();
	while (iElem--)
	{
		TYPE vTmp = this->GetAt(iElem);
		if (vTmp > vMax)
		{
			vMax = vTmp;
			iIdxMax = iElem;
		}
	}

	if (pIdxMax)
	{
		*pIdxMax = iIdxMax;
	}

	return vMax;
};

//----------------------------------------------------------------------------------
template<class TYPE, class ARG_TYPE>
TYPE CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetMin_inRgn(int iB, int iE, int* pIdxMin/* = nullptr*/) const
{
	assert(iB >= 0 && iB <= iE && iE < (*this).GetSize());

	TYPE vR = this->GetAt(iB);
	int	 iR = iB;
	const TYPE* pD = (*this).GetData() + iB + 1;
	for (int i = iB + 1; i <= iE; i++, pD++)
	{
		if (*pD < vR)
		{
			vR = *pD;
			iR = i;
		}
	}

	if (pIdxMin)
	{
		*pIdxMin = iR;
	}

	return vR;
}
//----------------------------------------------------------------------------------
template<class TYPE, class ARG_TYPE>
TYPE CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetMax_inRgn(int iB, int iE, int* pIdxMax/* = nullptr*/) const
{
	assert(iB >= 0 && iB <= iE && iE < (*this).GetSize());

	TYPE vR = this->GetAt(iB);
	int	 iR = iB;
	const TYPE* pD = (*this).GetData() + iB + 1;
	for (int i = iB + 1; i <= iE; i++, pD++)
	{
		if (*pD > vR)
		{
			vR = *pD;
			iR = i;
		}
	}

	if (pIdxMax)
	{
		*pIdxMax = iR;
	}

	return vR;
}
//----------------------------------------------------------------------------------
template<class TYPE, class ARG_TYPE>
void CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetMinMax(TYPE& vMin, TYPE& vMax) const
{
	if ((*this).GetSize() == 0)
		return;

	vMin = this->GetAt(0);
	vMax = this->GetAt(0);

	int iElem = (*this).GetSize();
	while (iElem--)
	{
		TYPE vTmp = this->GetAt(iElem);

		if (vTmp < vMin)
		{
			vMin = vTmp;
		}
		else if (vTmp > vMax)
		{
			vMax = vTmp;
		}
	}
};

//----------------------------------------------------------------------------------


template<class TYPE, class ARG_TYPE>
TYPE CSPN_Cmn_CArray<TYPE, ARG_TYPE>::GetWaveBandWidth() const
{
	TYPE vMin = 0;
	TYPE vMax = 0;

	GetMinMax(vMin, vMax);

	assert(vMax >= vMin);

	return vMax - vMin;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- 
typedef CSPN_Cmn_CArray<int, int>						Arr_Int;
typedef CSPN_Cmn_CArray<unsigned int, unsigned int>		Arr_UInt;

typedef CSPN_Cmn_CArray<short, short>						Arr_Sht;
typedef CSPN_Cmn_CArray<unsigned short, unsigned short>	Arr_USht;

typedef CSPN_Cmn_CArray<char, char>						Arr_Char;
typedef CSPN_Cmn_CArray<unsigned char, unsigned char>		Arr_UChar;

typedef CSPN_Cmn_CArray<float, float>						Arr_Flt;
typedef CSPN_Cmn_CArray<double, double>					Arr_Dbl;

typedef CSPN_Cmn_CArray<int, int>							Arr_Idx;

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

//template<typename TP, typename TP_ARG>
//void ShowMsg_Array_Dbg(const CSPN_Cmn_CArray<TP, TP_ARG>& ArrDat, std::string StrTitle)
//{
//	std::stringstream Strm;
//	{
//		Strm << StrTitle << ":";
//		for (int k = 0; k < ArrDat.GetSize(); k++)
//		{
//			const TP& vElem = ArrDat[k];
//			Strm << "\t[" << k << "]" << ArrDat[k];
//		}
//	}
//	ShowMsg(Strm.str());
//};

#endif //  // !defined(AFX_CSPN_Cmn_CArray_H__INCLUDED_
