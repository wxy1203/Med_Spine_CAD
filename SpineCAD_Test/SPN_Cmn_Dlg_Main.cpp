#include "pch.h"
#include "SPN_Cmn_Dlg_Main.h"
#include "SPN_Cmn_DlgPane_ShowPic.h"

SPN_Cmn_Dlg_Main::SPN_Cmn_Dlg_Main(QWidget *parent/* = nullptr*/)
	: QDialog(parent)
	, m_bInitPns(false)
{
	ui.setupUi(this);
	//QSize SzDesk = this->parentWidget()->rect().size();
	//this->resize(SzDesk);
	//this->move(0, 0);

	this->setWindowFlags(this->windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);   //隐藏最大化、最小化按钮
	this->showMaximized();
	
	m_pRadGrp_ImgTp = new QButtonGroup(this);            //分组
	{
		m_pRadGrp_ImgTp->addButton(ui.BtnRad_MPR, 0);        //一个值为0
		m_pRadGrp_ImgTp->addButton(ui.BtnRad_DRR, 1);        //一个值为1
		m_pRadGrp_ImgTp->addButton(ui.BtnRad_MaxIP, 2);      //一个值为2

		connect(m_pRadGrp_ImgTp, static_cast<void(QButtonGroup::*)(int)> (&QButtonGroup::buttonClicked),
				this, &SPN_Cmn_Dlg_Main::on_RadGrp_Clicked);
	}
	m_pRadGrp_ImgTp->button(1)->setChecked(true);


	m_pPane_Ax = new SPN_Cmn_DlgPane_ShowPic(2,this);
	m_pPane_Ax->show();

	m_pPane_Co = new SPN_Cmn_DlgPane_ShowPic(1,this);
	m_pPane_Co->show();

	m_pPane_Sa = new SPN_Cmn_DlgPane_ShowPic(0,this);
	m_pPane_Sa->show();

	m_pPane_Ax->HookTpSel_Img(&(this->m_iSel_ImgTp));
	m_pPane_Co->HookTpSel_Img(&(this->m_iSel_ImgTp));
	m_pPane_Sa->HookTpSel_Img(&(this->m_iSel_ImgTp));

	connect(m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);
	connect(m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);

	connect(m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);
	connect(m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);

	connect(m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);
	connect(m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::snWLChg, m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::OnWLChg);
	
	//connect(m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::NewFocXYZ, &m_CrsLn3D, CSPN_Cmn_VM3S_CrsLn::SetXYZ);

	m_pPane_Slash = new SPN_Cmn_DlgPane_ShowPic(3,this);
	m_pPane_Slash->show();

	m_pPane_3D = new SPN_Cmn_DlgPane_3D(this);
	m_pPane_3D->show();

	this->m_bInitPns = true;

	connect(ui.Chk_DoSlash, &QCheckBox::clicked,this, &SPN_Cmn_Dlg_Main::On_Slash_YesNo);
	connect(ui.Chk_GammaMap, &QCheckBox::clicked,this, &SPN_Cmn_Dlg_Main::On_Gamma_YesNo);

	connect(this, &SPN_Cmn_Dlg_Main::sn_ImgGamma_SelChg, m_pPane_Ax,    &SPN_Cmn_DlgPane_ShowPic::OnGammaChg);
	connect(this, &SPN_Cmn_Dlg_Main::sn_ImgGamma_SelChg, m_pPane_Co,    &SPN_Cmn_DlgPane_ShowPic::OnGammaChg);
	connect(this, &SPN_Cmn_Dlg_Main::sn_ImgGamma_SelChg, m_pPane_Sa,    &SPN_Cmn_DlgPane_ShowPic::OnGammaChg);
	connect(this, &SPN_Cmn_Dlg_Main::sn_ImgGamma_SelChg, m_pPane_Slash, &SPN_Cmn_DlgPane_ShowPic::OnGammaChg);

	m_pPane_Ax->Hook_iPnSlashing(&m_iPnSlashing);
	m_pPane_Co->Hook_iPnSlashing(&m_iPnSlashing);
	m_pPane_Sa->Hook_iPnSlashing(&m_iPnSlashing);
	ui.Chk_DoSlash->setChecked(true);
	ui.Chk_GammaMap->setChecked(m_bGamma);

//todo:
//	1.初始化Radio * 3;
//	2.gamma控制判断与计算;
}

SPN_Cmn_Dlg_Main::~SPN_Cmn_Dlg_Main()
{
}

void SPN_Cmn_Dlg_Main::RePos_UI()
{
	if(!m_bInitPns)
	{
		return;
	}
	//Ax(L-LT_Pane)-------------------------------------------------------
	//Co(L-LB_Pane)-------------------------------------------------------
	QSize SzDlg = this->size();
	
	const int C_nW_Edge = 5;
	const int C_nH_Edge = 5;

	const int C_nW_Spc = 2;
	const int C_nH_Spc = 2;

	int nH_RgnPn4 = SzDlg.height() - 2 * C_nH_Edge;
	int nW_RgnPn4 = nH_RgnPn4;

	QSize SzRgnPn4(nW_RgnPn4, nH_RgnPn4);
	QPoint PsRgnPn4(C_nW_Edge, C_nH_Edge);

	int nH_Pn_LLT = (SzRgnPn4.height() - C_nH_Spc) / 2;
	int nH_Pn_LLB = (SzRgnPn4.height() - C_nH_Spc - nH_Pn_LLT);

	int nW_Pn_LLT = nH_Pn_LLT;
	int nW_Pn_LLB = nW_Pn_LLT;

	//L-LT
	m_pPane_Ax->move(PsRgnPn4);
	m_pPane_Ax->resize(nW_Pn_LLT, nH_Pn_LLT);

	//L-LB
	m_pPane_Co->move(PsRgnPn4.x(), C_nH_Edge + nH_Pn_LLT + C_nH_Spc);
	m_pPane_Co->resize(nW_Pn_LLB, nH_Pn_LLB);

	//Slash(LRT_Pane)----------------------------------------------------
	//Sa(L-RB_Pane)-------------------------------------------------------
	QPoint PsLRT(C_nW_Edge + nW_Pn_LLT + C_nW_Spc, C_nH_Edge);
	QSize  SzLRT = m_pPane_Ax->size();
	m_pPane_Slash->move(PsLRT);
	m_pPane_Slash->resize(SzLRT);

	QPoint PsLRB(PsLRT.x(), m_pPane_Co->pos().y());
	QSize  SzLRB = m_pPane_Co->size();
	m_pPane_Sa->move  (PsLRB);
	m_pPane_Sa->resize(SzLRB);

	//3D(Mid_Pane)-------------------------------------------------------
	QRect RctLRT = m_pPane_Slash->rect();
	QPoint PsTR_LRT_inPa = m_pPane_Slash->mapToParent(RctLRT.topRight());

	QPoint PsM3D(PsTR_LRT_inPa.x() + C_nW_Spc,
				 m_pPane_Slash->pos().y());

	int nW_netW_MnR = SzDlg.width()- SzRgnPn4.width() - C_nW_Edge*2 - C_nW_Spc*2;
	int nW_M3D = nW_netW_MnR * 2 / 3;
	QSize  SzM3D(nW_M3D, SzRgnPn4.height());
	m_pPane_3D->move(PsM3D);
	m_pPane_3D->resize(SzM3D);

	QPoint PsChk_Slash;
	{
		PsChk_Slash.rx() = this->rect().right() - 20 - ui.Chk_DoSlash->width();
		PsChk_Slash.ry() = this->rect().top() + 20;
	}
	
	ui.Chk_DoSlash->move(PsChk_Slash);
	//ui.Chk_DoSlash->resize(SzChk);

	const int nDistY= 30;
	QPoint PsRad_MPR;
	{
		PsRad_MPR.rx() = PsChk_Slash.x();
		PsRad_MPR.ry() = PsChk_Slash.y() + 2*nDistY;
	}
	ui.BtnRad_MPR->move(PsRad_MPR);

	QPoint PsRad_DRR;
	{
		PsRad_DRR.rx() = PsRad_MPR.x();
		PsRad_DRR.ry() = PsRad_MPR.y() + nDistY;
	}
	ui.BtnRad_DRR->move(PsRad_DRR);

	QPoint PsRad_MaxIP;
	{
		PsRad_MaxIP.rx() = PsRad_DRR.x();
		PsRad_MaxIP.ry() = PsRad_DRR.y() + nDistY;
	}
	ui.BtnRad_MaxIP->move(PsRad_MaxIP);

	QPoint PsChk_Gamma;
	{
		PsChk_Gamma.rx() = PsRad_MaxIP.x();
		PsChk_Gamma.ry() = PsRad_MaxIP.y() + nDistY;
	}
	ui.Chk_GammaMap->move(PsChk_Gamma);
}



void SPN_Cmn_Dlg_Main::resizeEvent(QResizeEvent *pReszEvnt)
{
	this->RePos_UI();
}


void SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Ax(S_Img2D* pImgSum,int kSlcImg)
{
	m_pPane_Ax->ShowImg2D(*pImgSum, kSlcImg);
}

void SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Co(S_Img2D* pImgSum,int jSlcImg)
{
	m_pPane_Co->ShowImg2D(*pImgSum, jSlcImg);
}

void SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Sa(S_Img2D* pImgSum, int iSlcImg)
{
	m_pPane_Sa->ShowImg2D(*pImgSum, iSlcImg);
}

void SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Slash(S_Img2D* pImgSum,int kSlcImg)
{
	m_pPane_Slash->ShowImg2D(*pImgSum, kSlcImg);
}

void SPN_Cmn_Dlg_Main::On_Slash_YesNo(bool bSlash)
{
	E_SPN_MS_OP_MODE eMsOp = (bSlash) ? (E_SPN_MS_OP_MODE__DO_SLASH) : (E_SPN_MS_OP_MODE__NULL);
	m_pPane_Ax->Set_eMsOp_Modeb(eMsOp);
	m_pPane_Co->Set_eMsOp_Modeb(eMsOp);
	m_pPane_Sa->Set_eMsOp_Modeb(eMsOp);
}

void SPN_Cmn_Dlg_Main::On_Gamma_YesNo(bool bGamma)
{
	m_bGamma = bGamma;
	emit sn_ImgGamma_SelChg(m_bGamma);
	repaint();
}


void SPN_Cmn_Dlg_Main::on_RadGrp_Clicked(int iSel)
{
	this->m_iSel_ImgTp = iSel;
	emit sn_ImgTp_SelChg(m_iSel_ImgTp);
}
