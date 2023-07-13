#include "pch.h"
#include "CSPN_Cmn_Mx_Demo_Animate.h"


class Spring
{
public:
	enum
	{
		E_C_nW_Img = 512,
		E_C_nH_Img = 512,
	};

public:
	S_Img2D* CalcImg(int iCx, int jCy, float fAPhase)
	{
		//1
		S_Img2D* pImg2D = new S_Img2D;
		S_Img2D& sImg = *pImg2D;
		{
			//1A
			sImg.Set_nXYZ(E_C_nW_Img, E_C_nH_Img, 1);

			//1B
			float fCx = iCx; //E_C_nW_Img * 0.5f;
			float fCy = jCy; //E_C_nH_Img * 0.5f;

#pragma omp parallel for
			for (int j = 0; j < sImg.GetSize_Y(); j++)
			{
				float fRy2 = (j - fCy); fRy2 *= fRy2;

				for (int i = 0; i < sImg.GetSize_X(); i++)
				{
					float fRx2 = (i - fCx); fRx2 *= fRx2;
					float fR = sqrt(fRx2 + fRy2);

					//*(sImg.m_pfImgBuf + j * sImg.m_nW + i) = fPix;
					//<==>
					sImg.GetVox(i, j, 0) = sin(fR*0.1f + fAPhase) / (1 + pow(fR, 0.7)) * 2000;
					//<==>
					//sImg.m_pfImgBuf[iPx++] = fPix;
				}
			}
		}

		return pImg2D;
	}

public:

	static void CalcSumImg(S_Img2D& sImgSum, const std::vector<Spring*>& rArr_pSping, float fAPhase)
	{
		int iCx[3] = { 100, 200, 400 };
		int jCy[3] = { 400, 200, 300 };

		for (int i = 0; i < rArr_pSping.size(); i++)
		{
			S_Img2D* pImg = rArr_pSping[i]->CalcImg(iCx[i], jCy[i], fAPhase + i * 1.5);

			sImgSum += *pImg;

			delete pImg;
			pImg = nullptr;
		}
	}
};



//---------------------------------------------------------------------


CSPN_Cmn_Mx_Demo_Animate::CSPN_Cmn_Mx_Demo_Animate()
{
	m_iTimerID = QObject::startTimer(33);

	const int C_nSpring = 3;
	m_Arr_pSping.resize(C_nSpring);
	{
		for (int i = 0; i < m_Arr_pSping.size(); i++)
		{
			m_Arr_pSping[i] = new Spring;
		}
	}

	//connect(&(m_pPanePic->m_Timer), &MyTimer::myTimeOut, this, &SPN_Cmn_Dlg_DbgImg::StepNewCalc);

}

CSPN_Cmn_Mx_Demo_Animate::~CSPN_Cmn_Mx_Demo_Animate()
{
	QObject::killTimer(m_iTimerID);
	m_Arr_pSping;
	{
		for (int i = 0; i < m_Arr_pSping.size(); i++)
		{
			if (m_Arr_pSping[i])
			{
				delete m_Arr_pSping[i];
				m_Arr_pSping[i] = nullptr;
			}
		}
	}
}

void CSPN_Cmn_Mx_Demo_Animate:: timerEvent(QTimerEvent *event)
{
	StepNewCalc();
}


void CSPN_Cmn_Mx_Demo_Animate::StepNewCalc()
{
	m_nStepClc++;
	m_fAPhase = -float(m_nStepClc) / 12.f;

	ShowImg2D();
}


//void SPN_Cmn_Dlg_DbgImg::OnListenTm()
//{
//	m_nStepClc++;
//	m_fAPhase = -float(m_nStepClc) / 12.f;
//
//	Test_ShowImg2D();
//}

void CSPN_Cmn_Mx_Demo_Animate::ShowImg2D()
{
	//1
	S_Img2D* pImgSum = new S_Img2D;
	{
		pImgSum->Set_nXYZ(Spring::E_C_nW_Img, Spring::E_C_nH_Img, 1);
		pImgSum->SetVox_All(0);
	}

	//2
	Spring::CalcSumImg(*pImgSum, m_Arr_pSping, m_fAPhase);

////3
	emit Sn_ShowImg2D(pImgSum,0);
	//m_pPanePic->ShowImg2D(*pImgSum);
}

