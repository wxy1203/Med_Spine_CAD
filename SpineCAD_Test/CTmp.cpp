#include "pch.h"
#include "CTmp.h"


/*
template<typename TP>
class CSmartPtr
{
public:
	CSmartPtr()
	{
		m_nCountObj++;
	}

	CSmartPtr(TP* pObj)
	{
		m_nCountObj++;
	}

	TP&  operator->(...);

	TP&  operator *(...)

		~CSmartPtr()
	{
		m_nCountObj--;
		if (0 == m_nCountObj)
		{
			free(m_pObj);// delete m_pObj;
			m_pObj = nullptr;
		}
	}


	CSmartptr<TP> NewObj()
	{
		TP* pObj = malloc(sizeof(TP));// new TP;

		//pObj->TP();
		//pObj->~TP();

		return pObj;
	}

protected:
	static int m_nCountObj;
	static TP* m_pObj;
};

template<typename TP> int CSmartPtr<TP>::m_nCountObj = 0;

template<typename TP> int CSmartPtr<TP>::m_pObj = nullptr;
*/


class MtxSqrt_USht
{
	void CalcSqrt(CMtx Mtx)
	{
		for ()
		{
			Mtx[j][i] = ArrLut_ShtSqrt[Mtx[j][i]];
			
		}
	}

protected:
	static float ArrLut_ShtSqrt[65536];
};