
#include "pch.h"
#include "_SPN_Cmn_Math__inLib.h"

#include <QMatrix>

///////////////////////////////////////////////////////////////////////////
QMatrix g_GetMake_Mtx_RotScl(double fDA_Deg_Rot,
							 double fSclX,
							 double fSclY) //每个指针参数, 如NULL, 则不包含对应变换!
{
	QMatrix Mtx;
	Mtx.rotate(fDA_Deg_Rot);
	Mtx.scale(fSclX, fSclY);
	return Mtx;
};

QMatrix g_GetMake_Mtx_Rot(double fDA_Deg_Rot) //每个指针参数, 如NULL, 则不包含对应变换!
{
	QMatrix Mtx;
	Mtx.rotate(fDA_Deg_Rot);
	return Mtx;
};

template<typename TP>
void Rotate_Pnts_byDeg(Pnt2D_Dbl P2fRotCntr, double fDegRot, CSPN_Cmn_2DPoint<TP>* pP2fTgt, int nP = 1)
{
	QMatrix qMtx_Rot;
	{
		qMtx_Rot = g_GetMake_Mtx_Rot(fDegRot);
	}

	CSPN_Cmn_2DPoint<TP>* pPTmp = pP2fTgt;
	for (int i = 0; i < nP; i++, pPTmp++)
	{
#ifdef _DEBUG
		CSPN_Cmn_2DPoint<TP> PTmp = *pPTmp;
#endif // 
		QPointF qPSrc = pPTmp->To_QPointF();
		qPSrc -= P2fRotCntr.To_QPointF();
		QPointF qPDst = qMtx_Rot.map(qPSrc);

		*pPTmp = qPDst;
		*pPTmp += P2fRotCntr;
	}
}

template<typename TP>
void Rotate_Rcts_byDeg(Pnt2D_Dbl P2fRotCntr, double fDegRot, CSPN_Cmn_2DRect<TP>* pRctTgt, int nR = 1)
{
	double fDx, fDy, fDA_Deg_Rot, fSclX, fSclY;
	{
		fDx = 0;// -P2fRotCntr.x();经过测试验证, 此设置对旋转结果竟无影响!!!???
		fDy = 0;// -P2fRotCntr.y();经过测试验证, 此设置对旋转结果竟无影响!!!???

		fSclX = 1;
		fSclY = 1;
	}
	QMatrix qMtx_Rot;
	{
		//qMtx_Rot = g_GetMake_Mtx_MvRotScl(&fDx, &fDy, &fDegRot, &fSclX, &fSclY);
		qMtx_Rot = g_GetMake_Mtx_Rot(fDegRot);
	}

	CSPN_Cmn_2DRect<TP>* pRTmp = pRctTgt;
	for (int i = 0; i < nR; i++, pRTmp++)
	{
#ifdef _DEBUG
		CSPN_Cmn_2DRect<TP> RTmp = *pRTmp;
#endif // 
		QRectF qRctSrc = pRTmp->To_QRectF();
		QRectF qRctDst = qMtx_Rot.mapRect(qRctSrc);

		*pRTmp = qRctDst;

		//经过测试验证, 此设置对旋转结果竟无影响!!!? ? ?==>修正以保持中心: 
		//*pRTmp += P2fRotCntr;

		Pnt2D_Dbl PCntr_qt = pRTmp->Center().ToDouble();
		Pnt2D_Dbl PCntr_Mv = P2fRotCntr - PCntr_qt;

		*pRTmp += PCntr_Mv;
	}
}
///////////////////////////////////////////////////////////////////////////
Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Img_frm_Vw(Pnt2D_Dbl PVw, const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl PCntrVw = sPara.m_RctVw_inWnd.Center();
	Pnt2D_Dbl Dxy_Vw2Cntr = PVw - PCntrVw;
	Pnt2D_Dbl Dxy_Img2Cntr_RotPst = Dxy_Vw2Cntr * sPara.m_fK_Scale_PxSz_Vw2Img;
	Pnt2D_Dbl Dxy_Img2Cntr_RotPre = Dxy_Img2Cntr_RotPst;
	Rotate_Pnts_byDeg(Pnt2D_Dbl(0, 0), -sPara.m_fDeg_ImgRot, &Dxy_Img2Cntr_RotPre, 1);
	Pnt2D_Dbl PImg = sPara.m_PCnter_inImg + Dxy_Img2Cntr_RotPre;
	return PImg;
}

Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Vw_frm_Img(Pnt2D_Dbl PImg, const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl Dxy_Img2Cntr_RotPre = PImg - sPara.m_PCnter_inImg;	
	Pnt2D_Dbl Dxy_Img2Cntr_RotPst = Dxy_Img2Cntr_RotPre;
	Rotate_Pnts_byDeg(Pnt2D_Dbl(0, 0), sPara.m_fDeg_ImgRot, &Dxy_Img2Cntr_RotPst, 1);

	Pnt2D_Dbl Dxy_Vw = Dxy_Img2Cntr_RotPst / sPara.m_fK_Scale_PxSz_Vw2Img;
	Pnt2D_Dbl PCntrVw = sPara.m_RctVw_inWnd.Center();
	Pnt2D_Dbl PVw = PCntrVw + Dxy_Vw;
	return PVw;
}

Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Vw_frm_Wnd (Pnt2D_Dbl PWnd, const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl PVw = PWnd;
	PVw -= sPara.m_RctVw_inWnd.GetPnt_xMIN_yMIN();
	return PVw;
}
Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Wnd_frm_Vw (Pnt2D_Dbl PVw,  const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl PWnd = PVw;
	PWnd += sPara.m_RctVw_inWnd.GetPnt_xMIN_yMIN();
	return PWnd;
}

Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Img_frm_Wnd(Pnt2D_Dbl PWnd, const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl PVw  = GetPnt_Vw_frm_Wnd(PWnd, sPara);
	Pnt2D_Dbl PImg = GetPnt_Img_frm_Vw(PVw, sPara);
	return PImg;
}

Pnt2D_Dbl CSPN_Cmn_GUI_CoordSvr::GetPnt_Wnd_frm_Img(Pnt2D_Dbl PImg, const SPara_GUI_CrdSvc& sPara)
{
	Pnt2D_Dbl PVw  = GetPnt_Vw_frm_Img(PImg, sPara);
	Pnt2D_Dbl PWnd = GetPnt_Wnd_frm_Vw(PVw, sPara);
	return PWnd;
}

void CSPN_Cmn_GUI_CoordSvr::TransPnt_Img_to_Vw(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Vw_frm_Img(pP[i], sPara);
	}
}
void CSPN_Cmn_GUI_CoordSvr::TransPnt_Img_to_Wnd(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Wnd_frm_Img(pP[i], sPara);
	}
}
void CSPN_Cmn_GUI_CoordSvr::TransPnt_Vw_to_Img(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Img_frm_Vw(pP[i], sPara);
	}
}
void CSPN_Cmn_GUI_CoordSvr::TransPnt_Vw_to_Wnd(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Wnd_frm_Vw(pP[i], sPara);
	}
}
void CSPN_Cmn_GUI_CoordSvr::TransPnt_Wnd_to_Vw(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Vw_frm_Wnd(pP[i], sPara);
	}
}
void CSPN_Cmn_GUI_CoordSvr::TransPnt_Wnd_to_Img(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara)
{
	for (int i = 0; i < nP; i++)
	{
		pP[i] = GetPnt_Img_frm_Wnd(pP[i], sPara);
	}
}


void TestDemo_VoxMtx()
{
	//1. 定义对象
	CSPN_Cmn_3DMtx<short> Mtx16_Dcm;

	//2. 设置容器尺度
	Mtx16_Dcm;
	{
		const int C_nXTest = 100;
		const int C_nYTest = 200;
		const int C_nZTest = 1;
		Mtx16_Dcm.Set_nXYZ(C_nYTest, C_nYTest, C_nZTest);
	}

	//3. 送入像素
	for (int k = 0; k < Mtx16_Dcm.GetSize_Z(); k++)
	{
		for (int j = 0; j < Mtx16_Dcm.GetSize_Z(); j++)
		{
			for (int i = 0; i < Mtx16_Dcm.GetSize_Z(); i++)
			{
				short vPxRnd = rand();
				Mtx16_Dcm.SetVox(i, j, k, vPxRnd);
			}
		}
	}

	//4. WL映射目标
	CSPN_Cmn_3DMtx<BYTE> Mtx8_Img;
	{
		Mtx8_Img.Set_nXYZ(Mtx16_Dcm.GetSize_X(), Mtx16_Dcm.GetSize_Y(), 1);
		Mtx8_Img.ZeroMem();
	}

	//5.WL映射计算
	short iVwMin = 222;
	short iVwMax = 333;
	Mtx16_Dcm.MapMtx_byWnd_Slc(Mtx8_Img, 0, 0, iVwMin, iVwMax);
}