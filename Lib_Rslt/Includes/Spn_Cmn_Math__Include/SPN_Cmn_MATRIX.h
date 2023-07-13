// SPN_Cmn_Matrix<TP>.h: interface for the SPN_Cmn_Matrix<TP> class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPN_Cmn_Matrix_H__INCLUDED_
#define SPN_Cmn_Matrix_H__INCLUDED_

#include <vector>
#include "stdio.h"
//#include "afx.h"
//[9_17 16:11:39 ]:#include "TCHAR.h"
//[9_17 16:11:27 ]:#include "CTYPE.H"
//#include <afxcoll.h>
#include "_From_MFC_afxtempl.h"//#include <From_MFC_afxtempl.h>
//#include <fstream.h>

#include "SPN_Cmn_Science.h"
#include "SPN_Cmn_CArray.h"

#if _MSC_VER >= 1000
#	pragma once
#endif //  // _MSC_VER >= 1000

template<class TP>
class SPN_Cmn_Matrix/*: public CObject*/
{
public:
	SPN_Cmn_Matrix();
	SPN_Cmn_Matrix(const SPN_Cmn_Matrix<TP>&);
	SPN_Cmn_Matrix(int m, int n);
	virtual ~SPN_Cmn_Matrix();

	//data member:
public:

	typedef CSPN_Cmn_CArray<TP, TP&>	TPArr;

	CSPN_Cmn_CArray<TPArr*, TPArr*>	m_M;

	static int						m_nHeadStr;
	//static std::string				m_PrintHeadStr;

public:
	//overloaded operator:
	void operator=	(TPArr& arr);
	void operator=	(const SPN_Cmn_Matrix<TP>&);
	void operator=	(std::vector<TP>&);

	void operator+=	(const SPN_Cmn_Matrix<TP>&);
	void operator-=	(const SPN_Cmn_Matrix<TP>&);

	void operator*=	(TP& k);
	void operator*=	(const SPN_Cmn_Matrix<TP>&);

	void operator/=	(TP& k);

	CSPN_Cmn_CArray<TP, TP&>& operator[](int i) { return *m_M[i]; };

	const CSPN_Cmn_CArray<TP, TP&>& operator[](int i) const { return *m_M[i]; };

	//member function:
public:
	void				FlipVert();
	void				FlipHorz();

	void				MakeNewSpace(int m, int n);
	void				MemCopy(TP* pMem, const int nSzElemCount);
	void				Negative();

	void				T();

	void				SetAt(int i, int j, TP& val);
	void				SetAllMem(TP k);
	void				ZeroAllMem();

	SPN_Cmn_Matrix<TP>	Inverse() const;
	SPN_Cmn_Matrix<TP>   Inverse_2() const;
	TP                  MatrixDetValue() const;
	SPN_Cmn_Matrix<TP>	MakeUnitM() const;
	void				RemoveAll();

	void				SetSize(int m, int n);
	int					GetSizeM() const;
	int					GetSizeN() const;

	void				Smooth();
	void				Inflate(int nThick, TP v);
	//void				Deflate			(int nThick, TP v);
	void				StretchFrom(const SPN_Cmn_Matrix<TP>& M);
	void				Exponent(const DBLFLT fFloor);
	void				FindMinMax(TP& vMin, TP& vMax);
	void				FillRgn(TP& vMin, TP& vMax, const TP& vFill);

	//void				SerializeObject(CSPN_Cmn_Archive& Ar);
	//void				SerializePointer(CSPN_Cmn_Archive& Ar);

	//friend ::ofstream &operator<<(::ofstream &stream,const SPN_Cmn_Matrix<TP>& mtx);
	//friend ::ifstream &operator>>(::ifstream &stream,const SPN_Cmn_Matrix<TP>& mtx);

	//static void			SetPrintHeadCh	(const std::string& HeadStr,int n)
	//{
	//	m_nHeadStr=n;
	//	//m_PrintHeadStr=HeadStr;
	//};


	void GetDump_Mtx_to_Buf(TP* pBufDst, size_t nElemDst) const
	{
		TP* pElem = pBufDst;
		int nE = 0;
		bool bContinue = true;
		for (int j = 0; j < (*this).GetSizeM() && bContinue; j++)
		{
			for (int i = 0; i < (*this).GetSizeN(); i++, pElem++)
			{
				pElem[nE++] = (*this)[j][i];
				if (nE >= nElemDst)
				{
					bContinue = false;
					break;
				}
			}
		}
	};

	//{{用“抛雪球”方式设置矩阵元素：//*****************************************************************
public:
	void UseSnowBallFunction(const int iSnowBallSize);
	inline void SetElem_SnowBall(const int& iBgn, const int& jBgn, const TP& V)
	{
		(*m_pFun_SetElem_SnowBall)(*this, iBgn, jBgn, V);
	};

protected:
	void(*m_pFun_SetElem_SnowBall)(SPN_Cmn_Matrix<TP>&, int, int, const TP&);

	static void SetElem_SnowBall_01(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V);
	static void SetElem_SnowBall_02(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V);
	static void SetElem_SnowBall_03(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V);
	static void SetElem_SnowBall_04(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V);
	static void SetElem_SnowBall_06(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V);
	//{{用“抛雪球”方式设置矩阵元素!//*****************************************************************
#ifdef _DEBUG
	//void				TRACE_DBLFLT();
#endif // 
};
//*************************************************************
template<class T>
int SPN_Cmn_Matrix<T>::m_nHeadStr = 0;
//*************************************************************

//template<class T>
//std::string SPN_Cmn_Matrix<T>::m_PrintHeadStr=' ';
//*************************************************************

template<class TP>
SPN_Cmn_Matrix<TP>::~SPN_Cmn_Matrix()
{
	for (int i = 0; i < GetSizeM(); i++)
		delete m_M[i];
	m_M.RemoveAll();
}

template<class TP>
SPN_Cmn_Matrix<TP>::SPN_Cmn_Matrix()
{
	m_pFun_SetElem_SnowBall = SetElem_SnowBall_01;
	MakeNewSpace(1, 0);
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP>::SPN_Cmn_Matrix(const SPN_Cmn_Matrix<TP>	&mtx)
{
	MakeNewSpace(mtx.GetSizeM(), mtx.GetSizeN());
	for (int i = 0; i < GetSizeM(); i++)
		m_M[i]->Copy(mtx[i]);

	m_pFun_SetElem_SnowBall = mtx.m_pFun_SetElem_SnowBall;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP>::SPN_Cmn_Matrix(int m, int n)
{
	assert(m >= 1);
	MakeNewSpace(m, n);
	m_pFun_SetElem_SnowBall = SetElem_SnowBall_01;
}
#ifdef _DEBUG
//template<class TP> 
//inline void SPN_Cmn_Matrix<TP>::TRACE_DBLFLT()
//{
//	//TRACE("\nSPN_Cmn_Matrix TRACE:\n");
//	for(int i=0; i<GetSizeM(); i++)
//	{
//		//TRACE("[");
//		for(int j=0; j<GetSizeN(); j++)
//		{
//			//TRACE("%f", (*this)[i][j]);
//			if(j<GetSizeN()-1)
//				//TRACE(",");
//		}
//		//TRACE("]\n");
//	}
//
//}
#endif // 
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::MakeNewSpace(int m, int n)
{
	if (m != GetSizeM() ||
		n != GetSizeN())
	{
		assert(m >= 1);
		RemoveAll();
		m_M.SetSize(m);
		for (int i = 0; i < m; i++)
		{
			TPArr* pArrTmp = new TPArr;
			pArrTmp->SetSize(n);
			m_M[i] = pArrTmp;
		}
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::RemoveAll()
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		delete m_M[i];
	}
	m_M.RemoveAll();
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> SPN_Cmn_Matrix<TP>::MakeUnitM() const
{
	assert(GetSizeM() == GetSizeN());
	SPN_Cmn_Matrix M(GetSizeM(), GetSizeM());
	M.SetAllMem(TP(0));
	for (int i = 0; i < GetSizeM(); i++)
		M[i][i] = TP(1);
	return M;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> SPN_Cmn_Matrix<TP>::Inverse() const
{
	int i, j, k, N = GetSizeN();
	assert(GetSizeM() == N);

	SPN_Cmn_Matrix<TP> M0 = *this;
	SPN_Cmn_Matrix<TP> MI(N, N);
	MI = MI.MakeUnitM();
	TP f;

	for (int j = 0; j < N - 1; j++)
	{
		for (int i = j + 1; i < N; i++)
		{
			f = -M0[i][j] / M0[j][j];
			for (k = 0; k < N; k++)
				MI[i][k] += f * MI[j][k];
			for (k = j; k < N; k++)
				M0[i][k] += f * M0[j][k];
		}
	}
	for (int j = N - 1; j > 0; j--)
	{
		for (int i = j - 1; i > -1; i--)
		{
			f = -M0[i][j] / M0[j][j];
			for (k = 0; k < N; k++)
				MI[i][k] += f * MI[j][k];
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			MI[i][j] /= M0[i][i];
	return MI;
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::MemCopy(TP* pMem, const int nSzElemCount)
{
	assert(nSzElemCount >= GetSizeM()*GetSizeN());
	TP* pMemTmp = pMem;
	for (int i = 0; i < GetSizeM(); i++, pMemTmp += GetSizeN())
	{
		memcpy((*this)[i].GetData(), pMemTmp, GetSizeN() * sizeof(TP));
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetAt(int i, int j, TP& val)
{
	(*this)[i][j] = val;
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::ZeroAllMem()
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		::memset((*this)[i].GetData(), 0, sizeof(TP)*GetSizeN());
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetAllMem(TP k)
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ = k;
		}
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetSize(int m, int n)
{
	MakeNewSpace(m, n);
}
//*****************************************************************
template<class TP>
inline int SPN_Cmn_Matrix<TP>::GetSizeM() const
{
	return m_M.GetSize();
}
//*****************************************************************
template<class TP>
inline int SPN_Cmn_Matrix<TP>::GetSizeN() const
{
	return m_M[0]->GetSize();
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator=(const SPN_Cmn_Matrix<TP>& mtx)
{
	if (GetSizeM() != mtx.GetSizeM() || GetSizeN() != mtx.GetSizeN())
		MakeNewSpace(mtx.GetSizeM(), mtx.GetSizeN());
	for (int i = 0; i < GetSizeM(); i++)
		(*this)[i].Copy(mtx[i]);
	m_pFun_SetElem_SnowBall = mtx.m_pFun_SetElem_SnowBall;
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator=(TPArr& arr)//把数组回绕式填充到矩阵中
{
	assert(GetSizeM()*GetSizeN() == arr.GetSize());
	TP* pTPArr = arr.GetData();
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ = *pTPArr++;
		}
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator=(std::vector<TP>& vct)
{
	assert(GetSizeM()*GetSizeN() == vct.size());
	int k = 0;
	for (int i = 0; i < GetSizeM(); i++)
	{
		for (int j = 0; j < GetSizeN(); j++)
		{
			(*this)[i][j] = vct[k++];
		}
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::T()
{
	SPN_Cmn_Matrix<TP> mtx(GetSizeN(), GetSizeM());
	for (int i = 0; i < GetSizeN(); i++)
	{
		for (int j = 0; j < GetSizeM(); j++)
		{
			mtx[i][j] = (*this)[j][i];
		}
	}
	(*this) = mtx;
}

template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator+=(const SPN_Cmn_Matrix<TP>& mtx2)
{
	assert(GetSizeM() == mtx2.GetSizeM() && GetSizeN() == mtx2.GetSizeN());
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		const TP* pTP2 = mtx2[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ += *pTP2++;
		}
	}
}
//*******************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator-=(const SPN_Cmn_Matrix<TP>& mtx2)
{
	assert(GetSizeM() == mtx2.GetSizeM() && GetSizeN() == mtx2.GetSizeN());
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		TP* pTP2 = mtx2[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ -= *pTP2++;
		}
	}
}
//*******************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::Negative()
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		for (int j = 0; j < GetSizeN(); j++, pTP++)
		{
			*pTP = -(*pTP);
		}
	}
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator*=(TP& k)
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ *= k;
		}
	}
}
//*******************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator*=(const SPN_Cmn_Matrix<TP>& mtx2)
{
	assert(GetSizeN() == mtx2.GetSizeM());

	SPN_Cmn_Matrix<TP> tmp(GetSizeM(), mtx2.GetSizeN());
	tmp.SetAllMem(TP(0));
	for (int i = 0; i < tmp.GetSizeM(); i++)
	{
		TP* pTP = tmp[i].GetData();
		for (int j = 0; j < tmp.GetSizeN(); j++, pTP++)
		{
			for (int k = 0; k < GetSizeN(); k++)
			{
				*pTP += ((*this)[i][k] * mtx2[k][j]);
			}
		}
	}
	*this = tmp;
}
//*****************************************************************
template<class TP>
inline void SPN_Cmn_Matrix<TP>::operator/=(TP& k)
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		TP* pTP = (*this)[i].GetData();
		for (int j = 0; j < GetSizeN(); j++)
		{
			*pTP++ /= k;
		}
	}
};
//*******************************************************************
//*******************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator+(const SPN_Cmn_Matrix<TP>& mtx1, const SPN_Cmn_Matrix<TP>& mtx2)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp += mtx2;
	return MTmp;
}
//*******************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator-(const SPN_Cmn_Matrix<TP>& mtx1, const SPN_Cmn_Matrix<TP>& mtx2)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp -= mtx2;
	return MTmp;
}
//*******************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator-(const SPN_Cmn_Matrix<TP>& mtx1)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	for (int i = 0; i < mtx1.GetSizeM(); i++)
	{
		TP* pTP = MTmp[i].GetData();
		for (int j = 0; j < mtx1.GetSizeN(); j++, pTP++)
		{
			*pTP = -(*pTP);
		}
	}
	return MTmp;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator*(const SPN_Cmn_Matrix<TP>& mtx1, TP k)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp *= k;
	return MTmp;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator*(TP k, const SPN_Cmn_Matrix<TP>& mtx1)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp *= k;
	return MTmp;
}
//*******************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator*(const SPN_Cmn_Matrix<TP>& mtx1, const SPN_Cmn_Matrix<TP>& mtx2)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp *= mtx2;
	return MTmp;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> operator/(const SPN_Cmn_Matrix<TP>& mtx1, TP k)
{
	SPN_Cmn_Matrix<TP> MTmp(mtx1);
	MTmp /= k;
	return MTmp;
}
//*****************************************************************
//*****************************************************************
/*
template<class TP>
void SPN_Cmn_Matrix<TP>::SerializeObject(CSPN_Cmn_Archive& Ar)
{
	int i,j;
	if(Ar.IsStoring())
	{
		Ar<<GetSizeM();
		Ar<<GetSizeN();
		for(int i=0;i<GetSizeM();i++)
		{
			for(int j =0;j<GetSizeN();j++)
			{
				(*this)[i][j].Serialize(Ar);
			}
		}
	}
	else
	{
		int m,n;
		Ar>>m;
		Ar>>n;
		MakeNewSpace(m, n);
		for(int i=0;i<GetSizeM();i++)
		{
			for(int j =0;j<GetSizeN();j++)
			{
				(*this)[i][j].Serialize(Ar);
			}
		}
	}
}
*/
//template<class TP>
//void SPN_Cmn_Matrix<TP>::SerializePointer(CSPN_Cmn_Archive& Ar)
//{
//	int i, j;
//	if (Ar.IsStoring())
//	{
//		Ar << GetSizeM();
//		Ar << GetSizeN();
//		for (int i = 0; i < GetSizeM(); i++)
//		{
//			for (int j = 0; j < GetSizeN(); j++)
//			{
//				Ar << (*this)[i][j];
//			}
//		}
//	}
//	else
//	{
//		int m, n;
//		Ar >> m;
//		Ar >> n;
//		MakeNewSpace(m, n);
//		for (int i = 0; i < GetSizeM(); i++)
//		{
//			for (int j = 0; j < GetSizeN(); j++)
//			{
//				Ar >> (*this)[i][j];
//			}
//		}
//	}
//}
//*****************************************************************
//*****************************************************************
//template<class T>
//inline ::ofstream &operator<<(::ofstream &stream,SPN_Cmn_Matrix<T>& mtx)
//{
//	int m=mtx.GetSizeM();
//	int n=mtx.GetSizeN();
//	stream<<"*"<<m<<","<<n<<endl;
//	for(int i=0;i<m;i++)
//	{
//		for(int h=0;h<mtx.m_nHeadStr;h++)
//			stream<<mtx.m_PrintHeadStr;
//		for(int j=0;j<n;j++)
//		{
//			stream<<mtx[i][j]<<" ";
//		}
//		stream<<endl;
//	}
//	return stream;
//};
////*************************************************************
//
//template<class T>
//inline ::ifstream  &operator>>(::ifstream &stream,SPN_Cmn_Matrix<T>& mtx)
//{
//	int m,n;
//	char c;
//	stream>>c>>m>>c>>n;
//	mtx.MakeNewSpace(m,n);
//	for(int i=0;i<m;i++)
//	{
//		for(int j=0;j<n;j++)
//		{
//			stream>>mtx[i][j];
//		}
//	}
//	return stream;
//};

//template<class T>
//void operator<<(CSPN_Cmn_Archive& Ar, SPN_Cmn_Matrix<T>& M)
//{
//	Ar << M.GetSizeM();
//	Ar << M.GetSizeN();
//	for (int i = 0; i < M.GetSizeM(); i++)
//	{
//		for (int j = 0; j < M.GetSizeN(); j++)
//		{
//			Ar << M[i][j];
//		}
//	}
//}
//
//template<class T>
//void operator>>(CSPN_Cmn_Archive& Ar, SPN_Cmn_Matrix<T>& M)
//{
//	int m, n;
//	Ar >> m;
//	Ar >> n;
//	M.MakeNewSpace(m, n);
//	for (int i = 0; i < M.GetSizeM(); i++)
//	{
//		for (int j = 0; j < M.GetSizeN(); j++)
//		{
//			Ar >> M[i][j];
//		}
//	}
//}
//*****************************************************************
template<class TP>
void SPN_Cmn_Matrix<TP>::UseSnowBallFunction(const int iSnowBallSize)
{
	switch (iSnowBallSize)
	{
	case 2:  m_pFun_SetElem_SnowBall = SetElem_SnowBall_02; break;
	case 3:  m_pFun_SetElem_SnowBall = SetElem_SnowBall_03; break;
	case 4:  m_pFun_SetElem_SnowBall = SetElem_SnowBall_04; break;
	case 6:  m_pFun_SetElem_SnowBall = SetElem_SnowBall_06; break;
	default: m_pFun_SetElem_SnowBall = SetElem_SnowBall_01;
	}
}

/*//-----------------“雪球抛溅”系数分布:
	1
*///-----------------
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetElem_SnowBall_01(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V)
{
	M[iBgn][jBgn] = V;
}

/*//-----------------“雪球抛溅”系数分布:
	1 2 1
	2 4 2
	1 2 1
*///-----------------
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetElem_SnowBall_02(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V)
{
	//靠调用函数保证无越界出现：
	DBLFLT V2 = V / 2.0f;
	DBLFLT V4 = V / 4.0f;

	DBLFLT *pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V4;
	*pV++ += V2;
	*pV++ += V4;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V2;
	*pV++ += V;//--“雪球”中心元素--
	*pV++ += V2;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V4;
	*pV++ += V2;
	*pV++ += V4;
}

/*//-----------------“雪球抛溅”系数分布:
	1 1 3 1 1
	1 6 6 6 1
	3 6 9 6 3
	1 6 6 6 1
	1 1 3 1 1
*///-----------------
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetElem_SnowBall_03(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V)
{
	//靠调用函数保证无越界出现：
	DBLFLT V1 = V / 9.0f;
	DBLFLT V3 = V1 * 3.0f;
	DBLFLT V6 = V1 * 6.0f;

	DBLFLT *pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V1;
	*pV++ += V1;
	*pV++ += V3;
	*pV++ += V1;
	*pV++ += V1;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V1;
	*pV++ += V6;
	*pV++ += V6;
	*pV++ += V6;
	*pV++ += V1;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V3;
	*pV++ += V6;
	*pV++ += V;//--“雪球”中心元素--
	*pV++ += V6;
	*pV++ += V3;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V1;
	*pV++ += V6;
	*pV++ += V6;
	*pV++ += V6;
	*pV++ += V1;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V1;
	*pV++ += V1;
	*pV++ += V3;
	*pV++ += V1;
	*pV++ += V1;
}

/*//-----------------“雪球抛溅”系数分布:
	0  4  6  9  6  4  0
	4  9 14 18 14  9  4
	6 14 24 27 24 14  6
	9 18 27 36 27 18  9
	6 14 24 27 24 14  6
	4  9 14 18 14  9  4
	0  4  6  9  6  4  0
*///-----------------
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetElem_SnowBall_04(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V)
{
	//靠调用函数保证无越界出现：
	DBLFLT V01 = V / 36.0;
	DBLFLT V04 = V01 * 4;
	DBLFLT V06 = V01 * 6;
	DBLFLT V09 = V01 * 9;
	DBLFLT V14 = V01 * 14;
	DBLFLT V18 = V01 * 18;
	DBLFLT V24 = V01 * 24;
	DBLFLT V27 = V01 * 27;
	DBLFLT V30 = V01 * 30;

	DBLFLT *pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++ += V04;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V04;
	*pV++;//+= V00;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V04;
	*pV++ += V09;
	*pV++ += V14;
	*pV++ += V18;
	*pV++ += V14;
	*pV++ += V09;
	*pV++ += V04;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V14;
	*pV++ += V24;
	*pV++ += V27;
	*pV++ += V24;
	*pV++ += V14;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V09;
	*pV++ += V18;
	*pV++ += V27;
	*pV++ += V;//--“雪球”中心元素--
	*pV++ += V27;
	*pV++ += V18;
	*pV++ += V09;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V14;
	*pV++ += V24;
	*pV++ += V27;
	*pV++ += V24;
	*pV++ += V14;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V04;
	*pV++ += V09;
	*pV++ += V14;
	*pV++ += V18;
	*pV++ += V14;
	*pV++ += V09;
	*pV++ += V04;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++ += V04;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V04;
	*pV++;//+= V00;
}

/*//-----------------“雪球抛溅”系数分布:
	0  0  3  6  6  7  6  6  3  0  0
	0  3  6  9 12 12 12  9  6  3  0
	3  6  9 12 15 18 15 12  9  6  3
	6  9 12 15 18 24 18 15 12  9  6
	6 12 15 18 24 29 24 18 15 12  6
	7 12 18 24 29 36 29 24 18 12  7
	6 12 15 18 24 29 24 18 15 12  6
	6  9 12 15 18 24 18 15 12  9  6
	3  6  9 12 15 18 15 12  9  6  3
	0  3  6  9 12 12 12  9  6  3  0
	0  0  3  6  6  7  6  6  3  0  0

*///-----------------
template<class TP>
inline void SPN_Cmn_Matrix<TP>::SetElem_SnowBall_06(SPN_Cmn_Matrix<TP>& M, int iBgn, int jBgn, const TP& V)
{
	//靠调用函数保证无越界出现：
	DBLFLT V01 = V / 36.0;
	DBLFLT V03 = V01 * 3;
	DBLFLT V06 = V01 * 6;
	DBLFLT V07 = V01 * 7;
	DBLFLT V09 = V01 * 9;
	DBLFLT V12 = V01 * 12;
	DBLFLT V15 = V01 * 15;
	DBLFLT V18 = V01 * 18;
	DBLFLT V24 = V01 * 24;
	DBLFLT V29 = V01 * 29;

	DBLFLT *pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++;//+= V00;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V06;
	*pV++ += V07;
	*pV++ += V06;
	*pV++ += V06;
	*pV++ += V03;
	*pV++;//+= V00;
	*pV++;//+= V00;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V12;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V03;
	*pV++;//+= V00;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V03;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V24;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V24;
	*pV++ += V29;
	*pV++ += V24;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V07;
	*pV++ += V12;
	*pV++ += V18;
	*pV++ += V24;
	*pV++ += V29;
	*pV++ += V;//--“雪球”中心元素--
	*pV++ += V29;
	*pV++ += V24;
	*pV++ += V18;
	*pV++ += V12;
	*pV++ += V07;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V24;
	*pV++ += V29;
	*pV++ += V24;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V24;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V15;
	*pV++ += V18;
	*pV++ += V15;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V03;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V09;
	*pV++ += V12;
	*pV++ += V12;
	*pV++ += V12;
	*pV++ += V09;
	*pV++ += V06;
	*pV++ += V03;
	*pV++;//+= V00;

	pV = M[iBgn++].GetData() + jBgn;
	*pV++;//+= V00;
	*pV++;//+= V00;
	*pV++ += V03;
	*pV++ += V06;
	*pV++ += V06;
	*pV++ += V07;
	*pV++ += V06;
	*pV++ += V06;
	*pV++ += V03;
	*pV++;//+= V00;
	*pV++;//+= V00;
}
//*****************************************************************

template<class TP>
void SPN_Cmn_Matrix<TP>::Smooth()
{
	SPN_Cmn_Matrix<TP> TmpPane;
	TmpPane.MakeNewSpace(GetSizeM(), GetSizeN());

	TmpPane = (*this);//边缘地带

	for (int i0 = 0, i1 = 1, i2 = 2; i2 < GetSizeM(); i0++, i1++, i2++)
	{
		TP* pArrSrci0 = (*this)[i0].GetData();
		TP* pArrSrci1 = (*this)[i1].GetData();
		TP* pArrSrci2 = (*this)[i2].GetData();
		TP* pArrTgt = TmpPane[i1].GetData() + 1;//[1][1]
		for (int j2 = 2; j2 < GetSizeN(); j2++, pArrSrci0++, pArrSrci1++, pArrSrci2++, pArrTgt++)
		{
			*pArrTgt = 0;
			*pArrTgt += *(pArrSrci0 - 1);
			*pArrTgt += *(pArrSrci0);
			*pArrTgt += *(pArrSrci0 + 1);

			*pArrTgt += *(pArrSrci1 - 1);
			*pArrTgt += *(pArrSrci1);
			*pArrTgt += *(pArrSrci1 + 1);

			*pArrTgt += *(pArrSrci2 - 1);
			*pArrTgt += *(pArrSrci2);
			*pArrTgt += *(pArrSrci2 + 1);
			*pArrTgt /= 9.0f;
		}
	}
	(*this) = TmpPane;
}

//指数变换：
template<class TP>
void SPN_Cmn_Matrix<TP>::Exponent(const DBLFLT fFloor)
{
	assert(fFloor > FLT_MIN);
	for (int i = 0; i < GetSizeM(); i++)
	{
		for (int j = 0; j < GetSizeN(); j++)
		{
			TP& Mij = (*this)[i][j];
			Mij = pow(fFloor, -Mij);
		}
	}
}

//膨胀算法
//对于二值矩阵，对一种象素进行膨胀就是对另一种象素的腐蚀：
template<class TP>
void SPN_Cmn_Matrix<TP>::Inflate(int nThick, TP v)//(膨胀厚度,被膨胀的元素种类值)
{
	SPN_Cmn_Matrix<TP> M(*this);

	SPN_Cmn_Matrix<TP>* pMSrc = this;
	SPN_Cmn_Matrix<TP>* pMTgt = &M;

	for (int k = 0; k < nThick; k++)
	{
		int iMin = 1;
		int iMax = GetSizeM() - 1;

		int jMin = 1;
		int jMax = GetSizeN() - 1;

		for (int i = iMin; i < iMax; i++)
		{
			for (int j = jMin; j < jMax; j++)
			{
				TP& Vij = (*pMTgt)[i][j];
				if (Vij == v)
					continue;
				if ((*pMSrc)[i - 1][j - 1] == v) { Vij = v; continue; }
				if ((*pMSrc)[i - 1][j] == v) { Vij = v; continue; }
				if ((*pMSrc)[i - 1][j + 1] == v) { Vij = v; continue; }
				if ((*pMSrc)[i][j - 1] == v) { Vij = v; continue; }
				if ((*pMSrc)[i][j + 1] == v) { Vij = v; continue; }
				if ((*pMSrc)[i + 1][j - 1] == v) { Vij = v; continue; }
				if ((*pMSrc)[i + 1][j] == v) { Vij = v; continue; }
				if ((*pMSrc)[i + 1][j + 1] == v) { Vij = v; continue; }
			}
		}

		{//交换指针：
			SPN_Cmn_Matrix<TP>* pMTmp = pMSrc;
			pMSrc = pMTgt;
			pMTgt = pMTmp;
		}
	}

	//如最后结果不在(*this)则需要进行拷贝：
	if (nThick % 2 == 1)
		(*this) = M;
}
//*****************************************************************
template<class TP>
void SPN_Cmn_Matrix<TP>::FlipVert()
{
	SPN_Cmn_Matrix<TP> TmpPane;
	TmpPane.MakeNewSpace(GetSizeM(), GetSizeN());
	for (int iSrc = 0, iTgt = TmpPane.GetSizeM() - 1; iSrc < (*this).GetSizeM(); iSrc++, iTgt--)
	{
		TmpPane[iTgt].Copy((*this)[iSrc]);
	}
	(*this) = TmpPane;
}

template<class TP>
void SPN_Cmn_Matrix<TP>::FlipHorz()
{
	int nNSemi = GetSizeN() / 2;
	for (int i = 0; i < GetSizeM(); i++)
	{
		int jDst = GetSizeN() - 1;
		for (int j = 0; j < nNSemi; j++, jDst--)
		{
			TP tpTmp = (*this)[i][jDst];
			(*this)[i][jDst] = (*this)[i][j];
			(*this)[i][j] = tpTmp;
		}
	}
}
//*****************************************************************
template<class TP>
void SPN_Cmn_Matrix<TP>::StretchFrom(const SPN_Cmn_Matrix<TP>& M)
{
	assert(GetSizeM() > 0 && GetSizeN() > 0);
	assert(M.GetSizeM() > 0 && M.GetSizeN() > 0);

	DBLFLT fDiSrc = (DBLFLT)M.GetSizeM() / (DBLFLT)GetSizeM();
	DBLFLT fDjSrc = (DBLFLT)M.GetSizeN() / (DBLFLT)GetSizeN();

	DBLFLT fiSrc = 0.0f;
	for (int i = 0; i < GetSizeM(); i++, fiSrc += fDiSrc)
	{
		DBLFLT fjSrc = 0.0f;
		for (int j = 0; j < GetSizeN(); j++, fjSrc += fDjSrc)
		{
			(*this)[i][j] = M[fiSrc][fjSrc];
		}
	}
}
//*****************************************************************
template<class TP>
void SPN_Cmn_Matrix<TP>::FindMinMax(TP& vMin, TP& vMax)
{
	vMin = (*this)[0][0];
	vMax = vMin;
	for (int i = 0; i < GetSizeM(); i++)
	{
		for (int j = 0; j < GetSizeN(); j++)
		{
			TP& Vij = (*this)[i][j];

			if (Vij > vMax) vMax = Vij;
			else if (Vij < vMin) vMin = Vij;
		}
	}
}
//*****************************************************************
template<class TP>
void SPN_Cmn_Matrix<TP>::FillRgn(TP& vMin, TP& vMax, const TP& vFill)
{
	for (int i = 0; i < GetSizeM(); i++)
	{
		for (int j = 0; j < GetSizeN(); j++)
		{
			TP& Vij = (*this)[i][j];

			if (Vij<vMax && Vij>vMin)
				Vij = vFill;
		}
	}
}
//*****************************************************************
template<class TP>
inline TP SPN_Cmn_Matrix<TP>::MatrixDetValue() const
{
	assert(GetSizeM() == GetSizeN());

	int  z, j, k;
	TP r;
	TP DetValue = 0;

	int n = GetSizeN();
	SPN_Cmn_Matrix<TP>  TempMatrix(n - 1, n - 1); /*b[N][N]用于存放，在矩阵s[N][N]中元素s[0]的余子式*/
	if (n > 2)
	{
		for (z = 0; z < n; z++)
		{
			if ((*this)[0][z] != 0)
			{
				for (int j = 0; j < n - 1; j++)
				{
					for (k = 0; k < n - 1; k++)
					{
						if (k >= z)
						{
							TempMatrix[j][k] = (*this)[j + 1][k + 1];
						}
						else
						{
							TempMatrix[j][k] = (*this)[j + 1][k];
						}
					}
				}

				if (z % 2 == 0)
				{
					r = (*this)[0][z] * TempMatrix.MatrixDetValue();  /*递归调用*/
				}
				else
				{
					r = (-1)*(*this)[0][z] * TempMatrix.MatrixDetValue();
				}
				DetValue = DetValue + r;
			} //if
		} // for
	} // if

	else if (n == 2)
	{
		DetValue = (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
	}
	return DetValue;
}
//*****************************************************************
template<class TP>
inline SPN_Cmn_Matrix<TP> SPN_Cmn_Matrix<TP>::Inverse_2() const
{
	TP DetValue = (*this).MatrixDetValue();
	assert(DetValue != 0);              //行列式值不等于零时有逆矩阵
	assert(GetSizeM() == GetSizeN());   //必须要是方阵
	int z, j, k, g;
	int n = GetSizeN();
	SPN_Cmn_Matrix<TP> TempMatrix(n - 1, n - 1);
	SPN_Cmn_Matrix<TP> YZMatrix(n, n);
	SPN_Cmn_Matrix<TP> InverseMatrix(n, n);

	for (z = 0; z < n; z++)
	{
		for (int j = 0; j < n; j++)
		{
			for (k = 0; k < n - 1; k++)
			{
				for (g = 0; g < n - 1; g++)
				{
					if (k < z&&g >= j) TempMatrix[k][g] = (*this)[k][g + 1];         //第一象限
					else if (k >= z && g < j)  TempMatrix[k][g] = (*this)[k + 1][g];   //第三象限
					else if (k >= z && g >= j) TempMatrix[k][g] = (*this)[k + 1][g + 1]; //第四象限
					else TempMatrix[k][g] = (*this)[k][g];                    //第二象限
				}
			}

			if ((z + j) % 2 == 0)
			{
				YZMatrix[z][j] = TempMatrix.MatrixDetValue();
			}
			else
			{
				YZMatrix[z][j] = -TempMatrix.MatrixDetValue();
			}
		}
	}

	YZMatrix.T();
	InverseMatrix = YZMatrix / DetValue;

	return InverseMatrix;
}
//*****************************************************************

#endif //  // !defined(SPN_Cmn_Matrix<TP>_H__INCLUDED_
//*****************************************************************
