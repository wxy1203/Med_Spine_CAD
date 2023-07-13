#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_SPN_Cmn_DlgPane_ShowPic.h"
#include "SPN_Cmn_DlgPane_ShowPic.h"


//class SPN_Cmn_DlgPane_ShowPic;



class SPN_Cmn_DlgPane_3D : public SPN_Cmn_DlgPane_ShowPic
{
	Q_OBJECT

public:
	SPN_Cmn_DlgPane_3D(QWidget *parent = nullptr);
	~SPN_Cmn_DlgPane_3D();

public:
	//void ShowImg2D(const S_Img2D& sImg);

public:
	//void OnListenTm() override
	//{
	//	StepNewDraw();
	//};

//signals:
//	void NewFocXYZ_G(SSPN_Cmn_3DPoint<int>& sP3_G);
//
//	void NewFoc_XY_L(int iS_0X1Y2Z,int iXL, int jYL, SSPN_Cmn_3DPoint<int>& sP3_G);
//
//public slots:
//	//void StepNewDraw();
//	//void on_Btn_ShowPic_clicked();
//	////void on_pushButton_clicked()

protected:
	void	paintEvent(QPaintEvent* pEvntPaint) override;	// 重写绘制事件，显示在widgt上面
//	//virtual void	resizeEvent(QResizeEvent*) override;
//	//virtual void	moveEvent(QMoveEvent*) override;
//
//	//void			paintInMem();				// 绘在内存图片中
//
//protected:
//	void			DoDraw(QPaintEvent *pEvntPaint);
//	bool			UpdateMemImg();
//
//protected:
//	bool			CalcMemImg();
//	bool			ReadImg();
//
//public:
//    Ui::SPN_Cmn_DlgPane_ShowPic	m_uiPnPic;
//
//	QImage						m_QMemImg_VM;					// VM
//	const S_Img2D*				m_psImgData_MV = nullptr;		// MV
//
//	QPoint						m_P2_Foc;
//
//	//MyTimer						m_Timer;
//
//	//int							m_nStep = 0;
//	////QRect						m_RctDst;
//	////QRect                       m_RctImg;
//	//int							m_nDx = 0;
//	//int                         m_nDy = 0;
//};
};