#include "pch.h"
#include "CSPN_Cmn_Mx_Demo_3DMtx.h"
#include "SPN_Cmn_Dlg_DbgImg.h"
#include "CSPN_Cmn_MD_ItkDcm_Dir3D.h"
#include <math.h>

CSPN_Cmn_Mx_Demo_3DMtx::CSPN_Cmn_Mx_Demo_3DMtx()
{
	Construct_3DMtx();
	//m_iTimerId=QObject::startTimer(33);
}

int CSPN_Cmn_Mx_Demo_3DMtx::ReadDcmDir(std::string Str_DirPath)
{
	//1.读取dcm文件集
	CSPN_Cmn_MD_ItkDcm_Dir3D DirDcm3D;
	int nDcmRd= DirDcm3D.Load_Construct(Str_DirPath);
	if (0 == nDcmRd)
	{
		return 0;
	}

	//2.构造3D图像空间
	int nW = -1;
	int nH = -1;
	void* pBuf = DirDcm3D.Get_pImgBuf(nW,nH,0);
	assert(pBuf && nW > 0 && nH > 0);
	m_Mtx3D.Set_nXYZ(nW, nH, nDcmRd);
	m_Mtx3D.SetP3D_Bgn(DirDcm3D.GetSlcPos());
	m_Mtx3D.SetP3D_Spc(DirDcm3D.GetSpcXYZ());

	//3.导入图像像素
	int nWk = -1;
	int nHk = -1;
	for(int k=0;k< nDcmRd;k++)
	{
		void* pDst = m_Mtx3D.GetSliceBuf(k);
		void* pSrc = DirDcm3D.Get_pImgBuf(nWk, nHk, k);
		assert(nWk == nW && nHk == nH && pSrc!=nullptr);
		memcpy(pDst, pSrc, nWk*nHk * sizeof(short));
	}
	return nDcmRd;
}

void CSPN_Cmn_Mx_Demo_3DMtx::Construct_3DMtx()
{
	const int C_nX = 512;
	const int C_nY = 512;
	const int C_nZ = 300;

	const Pnt3D_Flt P3f_Bgn(0, 0, 0);
	const Pnt3D_Flt P3f_Spc(0.5, 0.5, 1.0);

	m_Mtx3D.Set_nXYZ(C_nX, C_nY, C_nZ);
	m_Mtx3D.SetP3D_Bgn(P3f_Bgn);
	m_Mtx3D.SetP3D_Spc(P3f_Spc);

	m_Mtx3D.SetVox_All(0);

	Pnt3D_Flt P3f_Cntr(m_Mtx3D.GetSize_X() / 2, m_Mtx3D.GetSize_Y() / 2, m_Mtx3D.GetSize_Z() / 2);

	for (int k = 0; k < m_Mtx3D.GetSize_Z(); k++)
	{
#pragma omp parallel for
		for (int j = 0; j < m_Mtx3D.GetSize_Y(); j++)
		{
			short* pVox_inRow = m_Mtx3D.GetSliceRowBuf(k, j);
			for (int i = 0; i < m_Mtx3D.GetSize_X(); i++)
			{
				Pnt3D_Flt P3f_Cur(i, j, k);
				float fR = P3f_Cur.GetDistTo(P3f_Cntr);
				float fLight = 1.f / (fR + 0.1) * 3000;

				*pVox_inRow++ = fLight;
			}

		}
	}
}

CSPN_Cmn_Mx_Demo_3DMtx::~CSPN_Cmn_Mx_Demo_3DMtx()
{
	QObject::killTimer(m_iTimerId);
	if (this->m_pImgSum_AxDRR) { delete m_pImgSum_AxDRR; m_pImgSum_AxDRR = nullptr; };
	if (this->m_pImgSum_CoDRR) { delete m_pImgSum_CoDRR; m_pImgSum_CoDRR = nullptr; };
	if (this->m_pImgSum_SaDRR) { delete m_pImgSum_SaDRR; m_pImgSum_SaDRR = nullptr; };

	if (this->m_pImgSum_AxMaxIP) { delete m_pImgSum_AxMaxIP; m_pImgSum_AxMaxIP = nullptr; }
	if (this->m_pImgSum_CoMaxIP) { delete m_pImgSum_CoMaxIP; m_pImgSum_CoMaxIP = nullptr; }
	if (this->m_pImgSum_SaMaxIP) { delete m_pImgSum_SaMaxIP; m_pImgSum_SaMaxIP = nullptr; }
}

void CSPN_Cmn_Mx_Demo_3DMtx::timerEvent(QTimerEvent *event)
{
	StepNewCalc();
}

void CSPN_Cmn_Mx_Demo_3DMtx::StepNewCalc()
{
	m_nStepClc++;

	int kSlcShow = m_nStepClc % m_Mtx3D.GetSize_Z();
	ShowImg_Slc_Ax(kSlcShow);

	int jSlcShow = m_nStepClc % m_Mtx3D.GetSize_Y();
	ShowImg_Slc_Co(jSlcShow);

	int iSlcShow = m_nStepClc % m_Mtx3D.GetSize_X();
	ShowImg_Slc_Sa(iSlcShow);

	//ShowImg_Slc_Slash();
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_Slc_Slash(int iPn_0X1Y2Z, const SSPN_Cmn_3DPoint<float>& P3G1, const SSPN_Cmn_3DPoint<float>& P3G2)
{
	//1
	S_Img2D* pImgSlash = new S_Img2D;

	switch (iPn_0X1Y2Z)
	{
	case 0:m_Mtx3D.GetSliceRandomParallelX(*pImgSlash, P3G1, P3G2); break;
	case 1:m_Mtx3D.GetSliceRandomParallelY(*pImgSlash, P3G1, P3G2); break;
	case 2:m_Mtx3D.GetSliceRandomParallelZ(*pImgSlash, P3G1, P3G2); break;

		//emit Sn_ShowImgSlc_Slash(pImgSlash);

	}
	//m_Mtx3D.GetSlc
	//{
	//	int nW = m_Mtx3D.GetSize_XYZ[iPn_0X1Y2Z];
	//	int nH=sqrt()
	//	//pImgSum->Set_nXYZ(m_Mtx3D.GetSize_ ? (), m_Mtx3D.GetSize_ ? (), 1);
	//	//pImgSum->SetVox_All(0);
	//}
//
	////2
	//int ? SlcShow = m_nStepClc % m_Mtx3D.GetSize_ ? ();
	//m_Mtx3D.GetSlice_ ? _ ? ? ? ? _3D(*pImgSum, 0, ? SlcShow);

	////3
	emit Sn_ShowImgSlc_Slash(pImgSlash, -1);
	//m_pPanePic->ShowImg2D(*pImgSum);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_Slc_Ax(int kSlcShow)
{
	if (kSlcShow < 0)
	{
		return;
	}
	//1
	S_Img2D* pImgSum = new S_Img2D;
	{
		pImgSum->Set_nXYZ(m_Mtx3D.GetSize_X(), m_Mtx3D.GetSize_Y(), 1);
		pImgSum->SetVox_All(0);
	}

	//2
	m_Mtx3D.GetSlice_Z_XpYp_3D(*pImgSum, 0, kSlcShow);

	////3
	emit Sn_ShowImgSlc_Ax(pImgSum,kSlcShow);
	//m_pPanePic->ShowImg2D(*pImgSum);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_Slc_Co(int jSlcShow)
{
	if (jSlcShow < 0)
	{
		return;
	}
	//1
	S_Img2D* pImgSum = new S_Img2D;
	{
		pImgSum->Set_nXYZ(m_Mtx3D.GetSize_X(), m_Mtx3D.GetSize_Z(), 1);
		pImgSum->SetVox_All(0);
	}

	//2
	m_Mtx3D.GetSlice_Y_XpZp_3D(*pImgSum, 0, jSlcShow);//*******************

//#define my_DEBUG
#ifdef my_DEBUG
	static SPN_Cmn_Dlg_DbgImg* pDbgImg=nullptr;
	if (pDbgImg)
	{
		return;
	}
	pDbgImg = new SPN_Cmn_Dlg_DbgImg;
	pDbgImg->ShowImg2D(pImgSum);
	pDbgImg->exec();
	delete pDbgImg; pDbgImg = nullptr;
	pImgSum = nullptr;
#endif
	////3
	if (pImgSum)
	{
		emit Sn_ShowImgSlc_Co(pImgSum,jSlcShow);
	}
	//emit Sn_ShowImgSlc_Co(pImgSum);
	//m_pPanePic->ShowImg2D(*pImgSum);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_Slc_Sa (int iSlcShow)
{
	if (iSlcShow < 0)
	{
		return;
	}
	//1
	S_Img2D* pImgSum = new S_Img2D;
	{
		pImgSum->Set_nXYZ(m_Mtx3D.GetSize_Y(), m_Mtx3D.GetSize_Z(), 1);
		pImgSum->SetVox_All(0);
	}

	//2
	m_Mtx3D.GetSlice_X_YpZp_3D(*pImgSum, 0, iSlcShow);

	//3
	emit Sn_ShowImgSlc_Sa (pImgSum,iSlcShow);
	//m_pPanePic->ShowImg2D(*pImgSum);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_DRR_Ax()
{
	//1
	if (nullptr == m_pImgSum_AxDRR)
	{
		m_pImgSum_AxDRR = new S_Img2D;
		m_Mtx3D.GetDRR_Ax(*m_pImgSum_AxDRR);
	}

	//2
	emit Sn_ShowImgSlc_Ax(m_pImgSum_AxDRR, -1);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_DRR_Co()
{
	//1
	if (nullptr == m_pImgSum_CoDRR)
	{
		m_pImgSum_CoDRR = new S_Img2D;
		m_Mtx3D.GetDRR_Co(*m_pImgSum_CoDRR);
	}

	//2
	emit Sn_ShowImgSlc_Co(m_pImgSum_CoDRR, -1);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_DRR_Sa()
{
	//1
	if (nullptr == m_pImgSum_SaDRR)
	{
		m_pImgSum_SaDRR = new S_Img2D;
		m_Mtx3D.GetDRR_Sa(*m_pImgSum_SaDRR);
	}

	//2
	emit Sn_ShowImgSlc_Sa(m_pImgSum_SaDRR, -1);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_MaxIP_Ax()
{
	//1
	if (nullptr == m_pImgSum_AxMaxIP)
	{
		m_pImgSum_AxMaxIP = new S_Img2D;
		m_Mtx3D.GetMaxIP_Ax(*m_pImgSum_AxMaxIP);
	}

	//2
	emit Sn_ShowImgSlc_Ax(m_pImgSum_AxMaxIP, -1);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_MaxIp_Co()
{
	//1
	if (nullptr == m_pImgSum_CoMaxIP)
	{
		m_pImgSum_CoMaxIP = new S_Img2D;
		m_Mtx3D.GetMaxIP_Co(*m_pImgSum_CoMaxIP);
	}

	//2
	emit Sn_ShowImgSlc_Co(m_pImgSum_CoMaxIP, -1);
}

void CSPN_Cmn_Mx_Demo_3DMtx::ShowImg_MaxIP_Sa()
{
	//1
	if (nullptr == m_pImgSum_SaMaxIP)
	{
		m_pImgSum_SaMaxIP = new S_Img2D;
		m_Mtx3D.GetMaxIP_Sa(*m_pImgSum_SaMaxIP);
	}

	//2
	emit Sn_ShowImgSlc_Sa(m_pImgSum_SaMaxIP, -1);
}


void CSPN_Cmn_Mx_Demo_3DMtx::OnFocChg_MPR(int iS_0X1Y2Z,QPointF P2FocL, SSPN_Cmn_3DPoint<float>& sP3_G,int iSelImgTp_0MPR_1DRR_2MaxIP)
{
	emit Sn_FocChg(sP3_G, iS_0X1Y2Z);

	if(0== iSelImgTp_0MPR_1DRR_2MaxIP)
	{
		ShowImg_Slc_Ax(sP3_G[2]);
		ShowImg_Slc_Co(sP3_G[1]);
		ShowImg_Slc_Sa(sP3_G[0]);
	}

	m_P3fFoc_MPR = sP3_G;
}

void CSPN_Cmn_Mx_Demo_3DMtx::onSlashChg(int iPnSlashing,
										const SSPN_Cmn_3DPoint<float>& P3G1,
										const SSPN_Cmn_3DPoint<float>& P3G2)
{
	ShowImg_Slc_Slash(iPnSlashing,P3G1, P3G2);
}

void CSPN_Cmn_Mx_Demo_3DMtx::onImgTp_SelChg(int iSel_Tp)
{
	switch (iSel_Tp)
	{
	case 0 : 	
		ShowImg_Slc_Ax(m_P3fFoc_MPR[2]);
		ShowImg_Slc_Co(m_P3fFoc_MPR[1]);
		ShowImg_Slc_Sa(m_P3fFoc_MPR[0]);
		break;
	case 1:
		ShowImg_DRR_Ax();
		ShowImg_DRR_Co();
		ShowImg_DRR_Sa();
		break;
	case 2:
		ShowImg_MaxIP_Ax();
		ShowImg_MaxIp_Co();
		ShowImg_MaxIP_Sa();
		break;
	default:;
	}
}


void CSPN_Cmn_Mx_Demo_3DMtx::InitPaint()
{
	ShowImg_Slc_Ax(this->m_Mtx3D.GetSize_Z() / 2);
	ShowImg_Slc_Co(this->m_Mtx3D.GetSize_Y() / 2);
	ShowImg_Slc_Sa(this->m_Mtx3D.GetSize_X() / 2);

}
