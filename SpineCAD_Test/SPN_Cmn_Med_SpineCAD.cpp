#include "pch.h"
#include "SPN_Cmn_Med_SpineCAD.h"
#include "TestVtkItk.h"
#include "SPN_Cmn_WString.h"
#include "SPN_Cmn_DirFileOp.h"

#include "SPN_Cmn_Dlg_DbgImg.h"
#include "SPN_Cmn_Dlg_Main.h"
#include "CSPN_Cmn_Mx_Demo_Animate.h"
#include "CSPN_Cmn_Mx_Demo_3DMtx.h"
#include "CSPN_Cmn_MV3D_VR.h"

SPN_Cmn_Med_SpineCAD::SPN_Cmn_Med_SpineCAD(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

SPN_Cmn_Med_SpineCAD::~SPN_Cmn_Med_SpineCAD()
{
}

void SPN_Cmn_Med_SpineCAD::on_Btn_ShowDlg_DbgImg_Slc_clicked()
{
	CSPN_Cmn_Mx_Demo_3DMtx MxDemo3D;
	SPN_Cmn_Dlg_DbgImg Dlg_DbgImg3D;

	connect(&MxDemo3D, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_ShowImgSlc_Ax, &Dlg_DbgImg3D, &SPN_Cmn_Dlg_DbgImg::ShowImg2D);

	Dlg_DbgImg3D.setVisible(true);
	Dlg_DbgImg3D.exec();
}


void SPN_Cmn_Med_SpineCAD::on_Btn_ShowDlg_DbgImg_clicked()
{
	CSPN_Cmn_Mx_Demo_Animate MxDemo;
	SPN_Cmn_Dlg_DbgImg Dlg_DbgImg;

	connect(&MxDemo, &CSPN_Cmn_Mx_Demo_Animate::Sn_ShowImg2D, &Dlg_DbgImg, &SPN_Cmn_Dlg_DbgImg::ShowImg2D);

	Dlg_DbgImg.setVisible(true);
	Dlg_DbgImg.exec();
}

void SPN_Cmn_Med_SpineCAD::on_Btn_ShowDlg_Main_clicked()
{	
	SPN_String StrPrompt("Sel Dir For Read Dicom Fileset:");
	SPN_String StrDirPath_Def("D:/_SpineCAD/0_MedDat/1813526(1~320)_BAK/");

	SPN_String StrRslt_DirPath;
	bool bOK = CSPN_Cmn_DirFileOp::GetSel_PathDir_by_BrowseUI(StrRslt_DirPath, StrPrompt, StrDirPath_Def);
	if (bOK)
	{
		OpenShow_DcmDir3D(StrRslt_DirPath.To_StdString());
	}
}

void SPN_Cmn_Med_SpineCAD::OpenShow_DcmDir3D(std::string Str_DirPath)
{
	//1.MM数据构造-------------------------------------------------------------------------------------
	CSPN_Cmn_Mx_Demo_3DMtx MxDemo3D_Mn;
	
	int nDcmRd = MxDemo3D_Mn.ReadDcmDir(Str_DirPath);
	if (nDcmRd <= 0)
	{
		return;
	}

	//2.VV构造-------------------------------------------------------------------------------------
	SPN_Cmn_Dlg_Main Dlg_Main;

	//3.M-V链接-------------------------------------------------------------------------------------
	//3A.显示图像
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_ShowImgSlc_Ax, &Dlg_Main, &SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Ax);
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_ShowImgSlc_Co, &Dlg_Main, &SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Co);
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_ShowImgSlc_Sa, &Dlg_Main, &SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Sa);
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_ShowImgSlc_Slash, &Dlg_Main, &SPN_Cmn_Dlg_Main::ShowImg2D_Mn_Slash);

	//3B.交点变换
	connect(Dlg_Main.m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::snNewFoc_XY_L, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::OnFocChg_MPR);
	connect(Dlg_Main.m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::snNewFoc_XY_L, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::OnFocChg_MPR);
	connect(Dlg_Main.m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::snNewFoc_XY_L, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::OnFocChg_MPR);

	//3C.slash剖面
	connect(Dlg_Main.m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::snSlashChg, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::onSlashChg);
	connect(Dlg_Main.m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::snSlashChg, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::onSlashChg);
	connect(Dlg_Main.m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::snSlashChg, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::onSlashChg);

	//3D.广播交点变更
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_FocChg, Dlg_Main.m_pPane_Ax, &SPN_Cmn_DlgPane_ShowPic::OnNewFoc_XYZ_G);
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_FocChg, Dlg_Main.m_pPane_Co, &SPN_Cmn_DlgPane_ShowPic::OnNewFoc_XYZ_G);
	connect(&MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::Sn_FocChg, Dlg_Main.m_pPane_Sa, &SPN_Cmn_DlgPane_ShowPic::OnNewFoc_XYZ_G);

	//3E.
	connect(&Dlg_Main, &SPN_Cmn_Dlg_Main::sn_ImgTp_SelChg, &MxDemo3D_Mn, &CSPN_Cmn_Mx_Demo_3DMtx::onImgTp_SelChg);

	//4.V层显示-------------------------------------------------------------------------------------
	MxDemo3D_Mn.InitPaint();

	Dlg_Main.setVisible(true);
	Dlg_Main.show();

	//5.VR测试
	CSPN_Cmn_MV3D_VR VR3D;
	VR3D.Show3D_VR(MxDemo3D_Mn.m_Mtx3D);
}

void SPN_Cmn_Med_SpineCAD::on_Btn_TestVTK_clicked()
{
	TestVtkItk::TestVTK();
}
void SPN_Cmn_Med_SpineCAD::on_Btn_TestITK_clicked()
{
	TestVtkItk::TestITK();
}

