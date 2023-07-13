
#ifndef SPN_BS_GUI_CrdSvr_H__INCLUDED_
#define SPN_BS_GUI_CrdSvr_H__INCLUDED_

#	pragma once

#include <QRect>
#include <QPointF>

struct SPara_GUI_CrdSvc
{
public:
	Rct2D_Dbl	m_RctVw_inWnd;
	Pnt2D_Dbl	m_PCnter_inImg;
	double		m_fK_Scale_PxSz_Vw2Img;
	double		m_fDeg_ImgRot;

public:
	SPara_GUI_CrdSvc()
		: m_RctVw_inWnd(-1, -1, -1, -1)
		, m_PCnter_inImg(-1, -1)
		, m_fK_Scale_PxSz_Vw2Img(-1)
		, m_fDeg_ImgRot(0)
	{
	};

	SPara_GUI_CrdSvc(const SPara_GUI_CrdSvc& sPara)
	{
		*this = sPara;
	};

	const SPara_GUI_CrdSvc& operator=(const SPara_GUI_CrdSvc& sPara)
	{
		m_RctVw_inWnd = sPara.m_RctVw_inWnd;
		m_PCnter_inImg = sPara.m_PCnter_inImg;
		m_fK_Scale_PxSz_Vw2Img = sPara.m_fK_Scale_PxSz_Vw2Img;
		m_fDeg_ImgRot = sPara.m_fDeg_ImgRot;
		return *this;
	};

	bool IsEqualTo(const SPara_GUI_CrdSvc& sPar) const
	{
		bool bEq =
			FLT_EQ(m_fDeg_ImgRot, sPar.m_fDeg_ImgRot) &&
			FLT_EQ(m_fK_Scale_PxSz_Vw2Img, sPar.m_fK_Scale_PxSz_Vw2Img) &&
			m_RctVw_inWnd.IsEqualTo(sPar.m_RctVw_inWnd) &&
			m_PCnter_inImg.IsEqualTo(sPar.m_PCnter_inImg);
		return bEq;
	};
};

class SPN_CMN_MATH_EXPORT CSPN_Cmn_GUI_CoordSvr
{
public:
	static Pnt2D_Dbl GetPnt_Img_frm_Vw(Pnt2D_Dbl PVw, const SPara_GUI_CrdSvc& sPara);
	static Pnt2D_Dbl GetPnt_Img_frm_Wnd(Pnt2D_Dbl PWnd, const SPara_GUI_CrdSvc& sPara);
	static Pnt2D_Dbl GetPnt_Vw_frm_Img(Pnt2D_Dbl PImg, const SPara_GUI_CrdSvc& sPara);
	static Pnt2D_Dbl GetPnt_Vw_frm_Wnd(Pnt2D_Dbl PWnd, const SPara_GUI_CrdSvc& sPara);
	static Pnt2D_Dbl GetPnt_Wnd_frm_Vw(Pnt2D_Dbl PVw, const SPara_GUI_CrdSvc& sPara);
	static Pnt2D_Dbl GetPnt_Wnd_frm_Img(Pnt2D_Dbl PImg, const SPara_GUI_CrdSvc& sPara);

	static void TransPnt_Img_to_Vw(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
	static void TransPnt_Img_to_Wnd(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
	static void TransPnt_Vw_to_Img(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
	static void TransPnt_Vw_to_Wnd(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
	static void TransPnt_Wnd_to_Vw(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
	static void TransPnt_Wnd_to_Img(Pnt2D_Dbl* pP, int nP, const SPara_GUI_CrdSvc& sPara);
};

#endif //  //SPN_BS_GUI_CrdSvr_H__INCLUDED_
