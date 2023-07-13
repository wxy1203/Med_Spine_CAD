#include "pch.h"
#include "SPN_Cmn_Dlg_DbgImg.h"
#include "SPN_Cmn_DlgPane_ShowPic.h"

//void SPN_Cmn_Dlg_DbgImg::StepNewCalc()
//{
//	m_nStepClc++;
//	m_fAPhase = -float(m_nStepClc) / 12.f;
//
//	ShowImg2D();
//}
//void SPN_Cmn_Dlg_DbgImg::OnListenTm()
//{
//	m_nStepClc++;
//	m_fAPhase = -float(m_nStepClc) / 12.f;
//
//	Test_ShowImg2D();
//}

SPN_Cmn_Dlg_DbgImg::SPN_Cmn_Dlg_DbgImg(QWidget *parent/* = nullptr*/)
	: QDialog(parent)
{
	//1
	ui.setupUi(this);

	//2
	m_pPanePic = new SPN_Cmn_DlgPane_ShowPic(1,this);
	//m_pPanePic->setVisible(true);
	m_pPanePic->show();

	//m_pPanePic->m_Timer.AddListener(this);
	//connect(&(m_pPanePic->m_Timer), SIGNAL(timeout), this, SLOT(StepNewCalc));
	//connect(&(m_pPanePic->m_Timer), SIGNAL(myTimeOut), this, SLOT(StepNewCalc));
	//connect(&(m_pPanePic->m_Timer), &MyTimer::myTimeOut, this, &SPN_Cmn_Dlg_DbgImg::StepNewCalc);

	////3
	//Test_ShowImg2D();


}

SPN_Cmn_Dlg_DbgImg::~SPN_Cmn_Dlg_DbgImg()
{
}

void SPN_Cmn_Dlg_DbgImg::ShowImg2D(S_Img2D* pImgSum,int kSlcImg)
{
	////1
	//S_Img2D* pImgSum = new S_Img2D;
	//{
	//	pImgSum->Set_nXYZ(Spring::E_C_nW_Img, Spring::E_C_nH_Img,1);
	//	pImgSum->SetVox_All(0);
	//}

	////2
	//Spring::CalcSumImg(*pImgSum, m_Arr_pSping, m_fAPhase);

	//3
	m_pPanePic->ShowImg2D(*pImgSum, kSlcImg);
}

void SPN_Cmn_Dlg_DbgImg::resizeEvent(QResizeEvent* pReszEv)
{
	const int C_nWEdge = 2;
	const int C_nHEdge = 2;
	m_pPanePic->move(C_nWEdge, C_nHEdge);

	QSize SzWnd = this->size();
	SzWnd.setWidth (SzWnd.width ()-2*C_nWEdge);
	SzWnd.setHeight(SzWnd.height()-2*C_nHEdge);
	m_pPanePic->resize(SzWnd);
}



