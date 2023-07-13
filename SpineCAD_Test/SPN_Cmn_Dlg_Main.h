#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SPN_Cmn_Dlg_Main.h"
#include "SPN_Cmn_DlgPane_ShowPic.h"
#include "SPN_Cmn_DlgPane_3D.h"
#include <QButtonGroup>


class SPN_Cmn_DlgPane_ShowPic;

class SPN_Cmn_Dlg_Main : public QDialog
{
	Q_OBJECT

public:
	SPN_Cmn_Dlg_Main(QWidget *parent = nullptr);
	~SPN_Cmn_Dlg_Main();

public slots:
	void resizeEvent(QResizeEvent *) override;
	void On_Slash_YesNo(bool nBgn);
	void On_Gamma_YesNo(bool nBgn);

public slots:
	void ShowImg2D_Mn_Ax(S_Img2D* pImgSum,int kSlcImg);
	void ShowImg2D_Mn_Co(S_Img2D* pImgSum, int jSlcImg);
	void ShowImg2D_Mn_Sa(S_Img2D* pImgSum, int iSlcImg);
	void ShowImg2D_Mn_Slash(S_Img2D* pImgSum,int kSlcImg);

	void on_RadGrp_Clicked(int iSel);

signals:
	void sn_ImgTp_SelChg(int iSel_Tp);
	void sn_ImgGamma_SelChg(bool bGamma);

protected:
	void RePos_UI();

public:
	Ui::SPN_Cmn_Dlg_Main	 ui;

	QButtonGroup*			 m_pRadGrp_ImgTp	= nullptr;            //����
	int						 m_iSel_ImgTp		= -1;

	SPN_Cmn_DlgPane_3D*		 m_pPane_3D			= nullptr;

	SPN_Cmn_DlgPane_ShowPic* m_pPane_Slash		= nullptr;	// б����
	SPN_Cmn_DlgPane_ShowPic* m_pPane_Ax			= nullptr;	// Ax -- Axial	(����棬��״�棩
	SPN_Cmn_DlgPane_ShowPic* m_pPane_Co			= nullptr;	// Co -- Coronal	(��״��)
	SPN_Cmn_DlgPane_ShowPic* m_pPane_Sa			= nullptr;	// Sa -- Saggitl	(ʸ״��)

	//SPN_Cmn_DlgPane_ShowPic*	m_pPane_3D		= nullptr;	// 3D

	bool					 m_bInitPns			= false;

	int						 m_iPnSlashing		= -1;

	bool					 m_bGamma			= true;
};
//todo��
//1.��ά��ͼ
