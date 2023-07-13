#include "pch.h"

#include "SPN_Cmn_DlgPane_ShowPic.h"
#include "SPN_Cmn_DirFileOp.h"
#include "SPN_Cmn_WString.h"


#include <QPainter>
#include <QRectF>
#include <QVector>
#include <QResizeEvent>
#include <QColor>
#include <QWidget>
#include "windows.h"
#include "math.h"

//----------------------------------------------------------------------------------------------

bool SPN_Cmn_DlgPane_ShowPic::ReadImg()
{
	QString StrFPth_Img;
	{
		QString StrTitle("Sel image file for read and show: ");
		QString StrDirDef("D:/Img");
		SPN_String spnStrFPath(StrFPth_Img);
		bool bOkImgF = CSPN_Cmn_DirFileOp::GetSel_PathFile_by_BrowseUI_forLoad(spnStrFPath, StrTitle, StrDirDef);

		if (!bOkImgF)
		{
			return false;
		}
	}

	bool bOK_Load = m_QMemImg_VM.load(StrFPth_Img);

	return bOK_Load;
}

bool SPN_Cmn_DlgPane_ShowPic::Update_MemImg()
{
	//1.------------------------------------------------------
	if (nullptr == m_psImgData_MV)
	{
		return false;
	}

	int nXY = m_psImgData_MV->GetSize_Slc();
	if (0 == nXY)
	{
		return false;
	}

	//2.------------------------------------------------------
	short iVw_Min = m_iVwLevel - 0.5 * m_nVwWidth;
	short iVw_Max = m_iVwLevel + 0.5 * m_nVwWidth;
	//m_psImgData_MV->GetVoxMinMax(vMin, vMax);

	//3.------------------------------------------------------
	CSPN_Cmn_3DMtx<BYTE> Mtx2D_Byte;
	if (m_bGamma)
	{
		m_psImgData_MV->MapMtx_byWndGamma_Slc(Mtx2D_Byte, 0, 0, iVw_Min, iVw_Max);
	}
	else
	{
		m_psImgData_MV->MapMtx_byWnd_Slc(Mtx2D_Byte, 0, 0, iVw_Min, iVw_Max);
	}
	//m_psImgData_MV->MapMtx_byWnd_Slc(Mtx2D_Byte, 0, 0, -2000, 2000);

	Mtx2D_Byte.GetQImage_Grey888(m_QMemImg_VM, 0);

	return true;
}
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
SPN_Cmn_DlgPane_ShowPic::SPN_Cmn_DlgPane_ShowPic(int iPn_0X1Y2Z,QWidget *parent)
    : QWidget(parent)
	//, m_nStep(0)
	//,m_RctDst
	//,m_RctImg
	, m_iPn_0X1Y2Z(iPn_0X1Y2Z)
	, m_kSlcL_CurImg(-1)
	, m_bL_BtnPress(false)
	, m_bR_BtnPress(false)
	, m_bM_BtnPress(false)

{
    m_uiPnPic.setupUi(this);/*
	m_psImgData_MV->Init();*/
	setMouseTracking(true);

	m_P2_Foc_V.rx() = width()/2;
	m_P2_Foc_V.ry() = height()/2;


	m_P2_Foc_L.rx() = -1;
	m_P2_Foc_L.ry() = -1;
	m_sP3_Foc_G.Construct(-1, -1, -1);

	//const int C_nFrmPerScd = 33;
	
//Q_SIGNALS:
//	void timeout(QPrivateSignal);

	//m_Timer.start(C_nFrmPerScd);

	//connect(&m_Timer, SIGNAL(timeout), this, SLOT(StepNewDraw));
	//connect(&m_Timer, SIGNAL(myTimeOut), this, SLOT(StepNewDraw));
	//connect(&m_Timer, &MyTimer::myTimeOut, this, &SPN_Cmn_DlgPane_ShowPic::StepNewDraw);

	//m_Timer.AddListener(this);//Im
}
//----------------------------------------------------------------------------------------------

SPN_Cmn_DlgPane_ShowPic::~SPN_Cmn_DlgPane_ShowPic()
{
	if (m_psImgData_MV && m_kSlcL_CurImg >= 0)
	{
		delete m_psImgData_MV;
		m_psImgData_MV = nullptr;
	}
}



void SPN_Cmn_DlgPane_ShowPic::ShowImg2D(const S_Img2D& sImgMV,int kSlcL)
{
	if (m_psImgData_MV && m_kSlcL_CurImg>=0)
	{
		delete m_psImgData_MV;
		m_psImgData_MV = nullptr;
	}
	m_psImgData_MV = &(const_cast<S_Img2D&>(sImgMV));
	m_kSlcL_CurImg = kSlcL;


	QWidget::repaint();
}

//void SPN_Cmn_DlgPane_ShowPic::StepNewDraw()
//{
//	int iBrk = 0;
//
//	if (0 == m_nStep)
//	{
//		/*QRect*/ m_RctDst = this->rect();
//		/*QRect*/ m_RctImg = m_QMemImg_VM.rect();
//		m_nDx = 2;
//		m_nDy = 2;
//	}
//	else
//	{
//		static bool bMv = 0;
//		if (bMv)
//		{
//			if (m_RctDst.left() > this->rect().right() ||
//				m_RctDst.right() < 0)
//			{
//				m_nDx *= -1;
//			}
//
//			if (m_RctDst.top() > this->rect().bottom() ||
//				m_RctDst.bottom() < 0)
//			{
//				m_nDy *= -1;
//			}
//
//			m_RctDst.adjust(m_nDx, m_nDy,
//							m_nDx, m_nDy);
//			//m_RctImg;
//		}
//		else
//		{
//			/*QRect*/ m_RctDst = this->rect();
//			/*QRect*/ m_RctImg = m_QMemImg_VM.rect();
//		}
//	}
//
//	m_nStep++;
//
//	this->repaint();
//}

void SPN_Cmn_DlgPane_ShowPic::paintEvent(QPaintEvent* pEvntPaint)
{
	//int iBrk = 1;

	if (1)
	{
		DoDraw(pEvntPaint);
	}
	else
	{
		//DoDraw1(pEvntPaint);
	}
};

void SPN_Cmn_DlgPane_ShowPic::DrawFrmLn(QPainter& Painter)
{
	QSize SzPn = this->size();
	SzPn.setWidth(SzPn.width() - 2);
	SzPn.setHeight(SzPn.height() - 2);
	QPen PenFrm;
	{
		PenFrm.setWidth(1);
		PenFrm.setColor(QColor(100, 100, 100));
	}
	Painter.setPen(PenFrm);

	Painter.drawRect(QRect(1, 1, SzPn.width(), SzPn.height()));
}


void SPN_Cmn_DlgPane_ShowPic::DoDraw(QPaintEvent *pEvntPaint)
{
	//0.Prepair: ------------------------------------------------------------------------------
	QPainter Painter(this);	
	Painter.save();

	//1.//Draw FrameLn-------------------------------------------------------------------------
	DrawFrmLn(Painter);
	//assert(true);
	//{
		//QSize SzPn = this->size();
		//SzPn.setWidth(SzPn.width() - 2);
		//SzPn.setHeight(SzPn.height() - 2);
		//QPen PenFrm;
		//{
		//	PenFrm.setWidth(1);
		//	PenFrm.setColor(QColor(100, 100, 100));
		//}
		//Painter.setPen(PenFrm);

		//Painter.drawRect(QRect(1, 1, SzPn.width(), SzPn.height()));
	//}

	//2.PaintImg: -----------------------------------------------------------------------------
	bool bChg = Update_MemImg();
	if (!m_QMemImg_VM.isNull())
	{
		//*********************************************************
		Painter.drawImage(this->rect(), m_QMemImg_VM, m_QMemImg_VM.rect());
	}

	//3.DrawGraph------------------------------------------------------------------------------

	//Draw_CrsLn_at_foc
	QPen Pen;
	if (m_iPn_0X1Y2Z >= 0 && m_iPn_0X1Y2Z <= 2)
	{
		{
			Pen.setWidth(1);
			Pen.setColor(/*QColor(*/Qt::red/*)*/);
		}
		Painter.setPen(Pen);
		{
			int iXBgn = 0;
			int iXEnd = width();
			Painter.drawLine(iXBgn, m_P2_Foc_V.y()
				, iXEnd, m_P2_Foc_V.y());

			int jYBgn = 0;
			int jYEnd = width();
			Painter.drawLine(m_P2_Foc_V.x(), jYBgn
				, m_P2_Foc_V.x(), jYEnd);
			//for (int i = 0; i < 10/*000*/; i++)
			//{
			//	QRectF RctF((iX + i * 2 + rand()) % 1500, (15 + i * 2 + rand()) % 1000, 100, 80);
			//	Painter.drawEllipse(RctF);
			//}
		}
	}

	//Draw Slash_Line

	Pen.setColor(Qt::green);
	if(nullptr!= m_piPn_Slashing && *m_piPn_Slashing==m_iPn_0X1Y2Z)
	{
		Painter.setPen(Pen);
		Painter.drawLine(m_SlashLn);
	}
	   	  
	if (m_kSlcL_CurImg >= 0)
	{
		Pen.setColor(Qt::green);
		Painter.setPen(Pen);
		{
			QPoint P2Txt;
			{
				QRect RctPn = this->rect();
				const int C_nW_TxtSlcNum = 50;
				const int C_nW_X_Edge = 10;
				P2Txt.setX(RctPn.right() - C_nW_TxtSlcNum - C_nW_X_Edge);
				P2Txt.setY(RctPn.top() + C_nW_X_Edge);

			}
			QString StrSlcNum;
			{
				StrSlcNum = QString::number(m_kSlcL_CurImg);
			}
			Painter.drawText(P2Txt, StrSlcNum);
		}
	}


	assert(true);
	static bool bTestDrawGraph = 0;
	if (bTestDrawGraph)
	{
		srand(GetTickCount());

		QPen Pen;
		{
			Pen.setWidth(2);
			Pen.setColor(/*QColor(*/Qt::red/*)*/);
			//Pen.setColor(QColor(Qt::red));
			//QColor Clr(Qt::green);
			//Pen.setColor(Clr);
			//Pen.setColor(QColor(Qt::green));
			//Pen.setColor(Qt::green);
		}
		Painter.setPen(Pen);
		{
			int iX = 10;
			int iY = 15;
			for (int i = 0; i < 10/*000*/; i++)
			{
				QRectF RctF((iX + i * 2 + rand()) % 1500, (15 + i * 2 + rand()) % 1000, 100, 80);
				Painter.drawEllipse(RctF);
			}
		}

		//--------------------------------------------------------
		QPen PenL;
		{
			PenL.setWidth(1);
			PenL.setColor(/*QColor(*/Qt::green/*)*/);
			//Pen.setColor(QColor(Qt::red));
			//QColor Clr(Qt::green);
			//Pen.setColor(Clr);
			//Pen.setColor(QColor(Qt::green));
			//Pen.setColor(Qt::green);
		}
		Painter.setPen(PenL);
		{
			QLine Ln(100, 100, 500, 300);
			Painter.drawLine(Ln);
		}
		//-------------------------------------------------------
		PenL.setColor(QColor(50, 80, 200));
		PenL.setWidth(5);
		Painter.setPen(PenL);
		{
			QVector<QPoint> ArrP2;
			{
				//ArrP2.resize(5);
				for (int j = 0; j < 6; j++)
				{
					if (j > 1 && 0 == j % 2)
					{
						ArrP2.push_back(ArrP2[j - 1]);
					}
					else
					{
						ArrP2.push_back(QPoint(rand() % 1000, rand() % 800));
					}
				}

				ArrP2.push_back(ArrP2[ArrP2.size() - 1]);
				ArrP2.push_back(ArrP2[0]);
			}
			Painter.drawLines(ArrP2);
		}
		//-------------------------------------------------------
		QPen PenR;
		{
			PenR.setWidth(9);
			PenR.setColor(QColor(200, 50, 255));
			//Pen.setColor(QColor(Qt::red));
			//QColor Clr(Qt::green);
			//Pen.setColor(Clr);
			//Pen.setColor(QColor(Qt::green));
			//Pen.setColor(Qt::green);
		}
		Painter.setPen(PenR);
		Painter.drawRect(QRect(40, 40, 150, 160));
	}

	//4.EndPaint------------------------------------------------------------------------------
	Painter.restore();
	Painter.end();
}

void SPN_Cmn_DlgPane_ShowPic::resizeEvent(QResizeEvent* /*pEvntSz*/)
{
	//pEvntSz->
	this->repaint();//>invalidate();
	m_P2_Foc_V.rx() = width() / 2;
	m_P2_Foc_V.ry() = height() / 2;

}

void SPN_Cmn_DlgPane_ShowPic::moveEvent(QMoveEvent*)
{
	this->repaint();//>invalidate();
}


void SPN_Cmn_DlgPane_ShowPic::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	m_bL_BtnPress = (event->button() == Qt::MouseButton::LeftButton);
	m_bR_BtnPress = (event->button() == Qt::MouseButton::RightButton);
	m_bM_BtnPress = (event->button() == Qt::MouseButton::MiddleButton);

	if (m_bR_BtnPress)
	{
		m_PsRtPrs = event->pos();
	}

	if  (m_bL_BtnPress && 
		(m_iPn_0X1Y2Z >= 0 && m_iPn_0X1Y2Z <= 2))
	{
		if (E_SPN_MS_OP_MODE__DO_SLASH == m_eMsOp_Mode)
		{
			m_SlashLn.setP1(event->pos());
			m_SlashLn.setP2(event->pos());
			m_bSlashing = true;
			*m_piPn_Slashing = m_iPn_0X1Y2Z;
			parentWidget()->repaint();
		}
		if (m_bNearHz && m_bNearVt)
		{ 
			m_bDrag_XY = true;
			m_eMsOp_Mode = E_SPN_MS_OP_MODE__MV_CRSLN;

		}
		else if (m_bNearHz)
		{
			m_bDrag_Y = true;
			m_eMsOp_Mode = E_SPN_MS_OP_MODE__MV_CRSLN;

		}
		else if (m_bNearVt)
		{
			m_bDrag_X = true;
			m_eMsOp_Mode = E_SPN_MS_OP_MODE__MV_CRSLN;

		}
	}
}
void SPN_Cmn_DlgPane_ShowPic::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
	if (m_bL_BtnPress)
	{
		m_bDrag_XY = false;
		m_bDrag_X = false;
		m_bDrag_Y = false;

		if (E_SPN_MS_OP_MODE__DO_SLASH == m_eMsOp_Mode)
		{
			m_SlashLn.setP2(event->pos());
			m_bSlashing = false;
			//m_eMsOp_Mode = E_SPN_MS_OP_MODE__NULL;
		}
	}

	if (m_bR_BtnPress)
	{
		this->m_dPs_Prev = QPoint(0, 0);
	}


	m_bL_BtnPress = (event->button() == Qt::MouseButton::LeftButton) ? (0): (m_bL_BtnPress);
	m_bR_BtnPress = (event->button() == Qt::MouseButton::RightButton) ? (0) : (m_bR_BtnPress);
	m_bM_BtnPress = (event->button() == Qt::MouseButton::MiddleButton) ? (0) : (m_bM_BtnPress);

}
void SPN_Cmn_DlgPane_ShowPic::mouseDoubleClickEvent(QMouseEvent *event)
{
	QWidget::mouseDoubleClickEvent(event);
}

void SPN_Cmn_DlgPane_ShowPic::mouseMoveEvent(QMouseEvent *event)
{
	Qt::MouseButton MsBtn = event->button();
	if (this->m_bR_BtnPress)
	{
		mouseMoveEvent_Rt(event);
	}
	switch (MsBtn)
	{
	//case Qt::RightButton:
	//	mouseMoveEvent_Rt(event);
	//	break;
	case Qt::MidButton:
		mouseMoveEvent_Mid(event); 
		break;
	default:
		mouseMoveEvent_Left(event);
		//mouseMoveEvent_Free(event);
	}
}
void SPN_Cmn_DlgPane_ShowPic::mouseMoveEvent_Free(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}

void SPN_Cmn_DlgPane_ShowPic::mouseMoveEvent_Left(QMouseEvent *event)
{
	QPoint PCur = event->pos();
	if (E_SPN_MS_OP_MODE__DO_SLASH == m_eMsOp_Mode ||
		E_SPN_MS_OP_MODE__MV_CRSLN == m_eMsOp_Mode)
	{
		PCur.rx() = std::min<int>(PCur.x(), this->rect().right() - 1);
		PCur.rx() = std::max<int>(PCur.x(), this->rect().left() + 1);

		PCur.ry() = std::max<int>(PCur.y(), this->rect().top() + 1);
		PCur.ry() = std::min<int>(PCur.y(), this->rect().bottom() - 1);

		event->setLocalPos(PCur);
	}

	//1.近线判断 修改光标
	if (m_iPn_0X1Y2Z >= 0 && m_iPn_0X1Y2Z <= 2)
	{
		const int C_Near_dXY = 3;

		if (E_SPN_MS_OP_MODE__DO_SLASH == m_eMsOp_Mode)
		{
			this->setCursor(Qt::CrossCursor);
			if (m_bSlashing)
			{
				m_SlashLn.setP2(event->pos());
				NotifySlashChg();
			}
		}
		else /*(E_SPN_MS_OP_MODE__MV_CRSLN == m_eMsOp_Mode)*/
		{
			m_bNearHz = std::abs(PCur.y() - m_P2_Foc_V.y()) <= C_Near_dXY;
			m_bNearVt = std::abs(PCur.x() - m_P2_Foc_V.x()) <= C_Near_dXY;

			if (m_bNearHz && m_bNearVt)
			{
				this->setCursor(Qt::SizeAllCursor);
				if (m_bDrag_X || m_bDrag_Y)
				{
					m_bDrag_XY = true;
					m_bDrag_X = false;
					m_bDrag_Y = false;
				}
			}
			else if (m_bNearHz)
			{
				this->setCursor(Qt::SizeVerCursor);
			}
			else if (m_bNearVt)
			{
				this->setCursor(Qt::SizeHorCursor);
			}
			else
			{
				this->setCursor(Qt::ArrowCursor);
			}
			//2.拖动十字线
			if (m_bDrag_XY || m_bDrag_Y || m_bDrag_X)
			{
				if (m_bDrag_XY)
				{
					m_P2_Foc_V = PCur;
				}
				else if (m_bDrag_Y)
				{
					m_P2_Foc_V.setY(PCur.y());
				}
				else if (m_bDrag_X)
				{
					m_P2_Foc_V.setX(PCur.x());
				}

				Transfm_V_to_L(m_P2_Foc_L, m_P2_Foc_V);
				Transfm_L_to_G(m_sP3_Foc_G, m_P2_Foc_L);

				emit this->snNewFoc_XY_L(m_iPn_0X1Y2Z, m_P2_Foc_L, m_sP3_Foc_G, (*m_piSelTpImg));
			}
		}
	}
	//Z.

	this->update();
	QWidget::mouseMoveEvent(event);
}

void SPN_Cmn_DlgPane_ShowPic::mouseMoveEvent_Mid(QMouseEvent *event)
{

}

void SPN_Cmn_DlgPane_ShowPic::mouseMoveEvent_Rt(QMouseEvent *event)
{
	QPoint PsCur = event->pos();
	QPoint dPsCur = PsCur - m_PsRtPrs;
	QPoint ddPs = dPsCur - m_dPs_Prev;

	const float fK_VwWid_to_MsMv = 5;
	m_nVwWidth += fK_VwWid_to_MsMv * ddPs.x();
	m_iVwLevel += fK_VwWid_to_MsMv * (-ddPs.y());

	//Update_MemImg();
	this->repaint();
	emit snWLChg(m_nVwWidth, m_iVwLevel);

	QWidget::mouseMoveEvent(event);

	m_dPs_Prev = dPsCur;
}

void SPN_Cmn_DlgPane_ShowPic::OnWLChg(int nW, int iL)
{
	this->m_nVwWidth = nW;
	this->m_iVwLevel = iL;
	repaint();
}

void SPN_Cmn_DlgPane_ShowPic::OnGammaChg(bool bGamma)
{
	this->m_bGamma = bGamma;
	repaint();
}



void SPN_Cmn_DlgPane_ShowPic::Set_eMsOp_Modeb(E_SPN_MS_OP_MODE eMsOp)
{
	m_eMsOp_Mode = eMsOp;
}

void SPN_Cmn_DlgPane_ShowPic::OnNewFoc_XYZ_G(SSPN_Cmn_3DPoint<float>& sP3_G,int iS_0X1Y2Z_ChgSrc)
{
	m_sP3_Foc_G = sP3_G;
	Transfm_G_to_L(m_P2_Foc_L,sP3_G);
	Transfm_L_to_V(m_P2_Foc_V, m_P2_Foc_L);
	repaint();
}

void SPN_Cmn_DlgPane_ShowPic::Transfm_L_to_G(SSPN_Cmn_3DPoint<float>& sP3_Dst,const QPointF& P2L_Src)const
{
	switch (m_iPn_0X1Y2Z)
	{
	case 0:
	{
		sP3_Dst[0] = m_kSlcL_CurImg;
		sP3_Dst[1] = P2L_Src.x();
		sP3_Dst[2] = P2L_Src.y();
	}
	break;
	case 1:
		sP3_Dst[0] = P2L_Src.x();
		sP3_Dst[1] = m_kSlcL_CurImg;
		sP3_Dst[2] = P2L_Src.y();
		break;

	case 2:
		sP3_Dst[0] = P2L_Src.x();
		sP3_Dst[1] = P2L_Src.y();
		sP3_Dst[2] = m_kSlcL_CurImg;
		break;
	default:;
	//	assert(false);
	}

}
void SPN_Cmn_DlgPane_ShowPic::Transfm_G_to_L(QPointF& P2L_Src,const SSPN_Cmn_3DPoint<float>& sP3_Dst)const
{
	switch (m_iPn_0X1Y2Z)
	{
	case 0:
	{
		P2L_Src.rx() = sP3_Dst[1];
		P2L_Src.ry() = sP3_Dst[2];
	}
	break;
	case 1:
		P2L_Src.rx() = sP3_Dst[0];
		P2L_Src.ry() = sP3_Dst[2];
		break;

	case 2:
		P2L_Src.rx() = sP3_Dst[0];
		P2L_Src.ry() = sP3_Dst[1];
		break;
	default:
		assert(false);
	}
}
void SPN_Cmn_DlgPane_ShowPic::Transfm_V_to_L(QPointF& P2L, const QPoint& P2V)const
{
	int nW_Img = m_QMemImg_VM.width();
	int nH_Img = m_QMemImg_VM.height();

	if (0 == nH_Img || 0 == nW_Img)
	{
		return;
	}

	float fKx_V2L = float(this->width()) / nW_Img;
	float fKy_V2L = float(this->height()) / nH_Img;

	P2L.rx() = P2V.x() / fKx_V2L;
	P2L.ry() = P2V.y() / fKy_V2L;

}
void SPN_Cmn_DlgPane_ShowPic::Transfm_L_to_V(QPoint& P2V, const QPointF& P2L)const
{
	int nW_Img = m_QMemImg_VM.width();
	int nH_Img = m_QMemImg_VM.height();
	if (0 == nH_Img || 0 == nW_Img)
	{
		return;
	}

	float fKx_V2L = float(this->width()) / nW_Img;
	float fKy_V2L = float(this->height()) / nH_Img;

	P2V.rx() = P2L.x() * fKx_V2L;
	P2V.ry() = P2L.y() * fKy_V2L;

}

void SPN_Cmn_DlgPane_ShowPic::NotifySlashChg()
{
	SSPN_Cmn_3DPoint<float>P3G1, P3G2;
	{
		QPointF P2L1;
		QPointF P2L2;
		Transfm_V_to_L(P2L1, m_SlashLn.p1());
		Transfm_V_to_L(P2L2, m_SlashLn.p2());

		Transfm_L_to_G(P3G1,P2L1);
		Transfm_L_to_G(P3G2, P2L2);
	}
	emit snSlashChg(m_iPn_0X1Y2Z,P3G1,P3G2);
}

