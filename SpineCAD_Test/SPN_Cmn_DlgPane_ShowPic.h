#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_SPN_Cmn_DlgPane_ShowPic.h"

//class S_Img2D// : public CBase, public CABC
//{
//public:
//	S_Img2D() 
//		: //CBase(), CABC()
//		m_pfImgBuf(nullptr),
//		m_nW(0),
//		m_nH(0)
//	{
//	}
//
//	~S_Img2D()
//	{
//		free();
//	}
//
//
//
//public:
//	float* m_pfImgBuf;
//	int    m_nW;
//	int    m_nH;
//
//public:
//	void operator+=(const S_Img2D& sImg)
//	{
//		int iXY = Get_nXY();
//		while (iXY--)
//		{
//			m_pfImgBuf[iXY] += sImg.m_pfImgBuf[iXY];
//		}
//	};
//
//public:
//	inline void Construct(int C_nW, int C_nH)
//	{
//		free();
//
//		m_nW = C_nW;
//		m_nH = C_nH;
//		m_pfImgBuf = new float[Get_nXY()];
//	}
//	inline void free()
//	{
//		if (m_pfImgBuf)
//		{
//			delete []m_pfImgBuf;
//			m_pfImgBuf = nullptr;
//			m_nW = 0;
//			m_nH = 0;
//		}
//		else
//		{
//			assert(0 == m_nW);
//			assert(0 == m_nH);
//			assert(nullptr == m_pfImgBuf);
//		}
//	}
//
//public:
//	inline int Get_nXY() const
//	{
//		return m_nW*m_nH;
//	}
//
//	inline void FindMinMax(float& rfMin, float& rfMax) const
//	{
//		int nXY = Get_nXY();
//
//		rfMax = m_pfImgBuf[0];
//		rfMin = m_pfImgBuf[0];
//
//		for (int i = 1; i < nXY; i++)
//		{
//			if (m_pfImgBuf[i] < rfMin)
//			{
//				rfMin = m_pfImgBuf[i];
//			}
//
//			if (m_pfImgBuf[i] > rfMax)
//			{
//				rfMax = m_pfImgBuf[i];
//			}
//		}
//	}
//
//	inline void MapTo_GreyImg_WL(QImage& rImg, float fW, float fL) const
//	{
//		float fLo_to_0   = fL - 0.5f*fW;
//		float fUp_to_255 = fL + 0.5f*fW;
//
//		MapTo_GreyImg_LoUp(rImg, fLo_to_0, fUp_to_255);
//	}
//
//	inline void MapTo_GreyImg_LoUp(QImage& rImg, float fLow_to_0, float fUp_to_255) const
//	{
//		if (m_nW != rImg.width() || m_nH != rImg.height())
//		{
//			rImg = QImage(m_nW, m_nH, QImage::Format_RGB888);
//		}
//
//		if (fabs(fUp_to_255 - fLow_to_0) < 2 * FLT_EPSILON)
//		{
//			uchar vGrey = 128;
//			for (int j = 0; j < m_nH; j++)
//			{
//				for (int i = 0; i < m_nW; i++)
//				{
//					rImg.setPixel(i, j, qRgb(vGrey, vGrey, vGrey/*, 0*/));
//				}
//			}
//		}
//		else
//		{
//			float fK = 255.f / (fUp_to_255 - fLow_to_0);
//
//			int nBytesPerLine = rImg.bytesPerLine();
//			int nBytePerPx = nBytesPerLine / m_nW;
//
////#pragma omp parallel for
//			for (int j = 0; j < m_nH; j++)
//			{
//				uchar* pRowBuf = rImg.scanLine(j);
//				for (int i = 0; i < m_nW; i++)
//				{
//					int iPx = j * m_nW + i;
//
//					uchar vGrey;
//					{
//						if (m_pfImgBuf[iPx] < fLow_to_0)
//						{
//							vGrey = 0;
//						}
//						else if (m_pfImgBuf[iPx] > fUp_to_255)
//						{
//							vGrey = 255;
//						}
//						else
//						{
//							vGrey = (m_pfImgBuf[iPx] - fLow_to_0) * fK;
//						}
//					}
//
//					//rImg.setPixel(i, j, qRgb(vGrey, vGrey, vGrey/*, 0*/));
//					int iBytePxBgn_inRow = i*nBytePerPx;
//					int iByte_inPx = nBytePerPx;
//					while (iByte_inPx--)
//					{
//						pRowBuf[iBytePxBgn_inRow + iByte_inPx] = vGrey;
//					}
//				}
//			}
//		}
//	}
//};

enum E_SPN_MS_OP_MODE
{
	E_SPN_MS_OP_MODE__NULL,
	E_SPN_MS_OP_MODE__DO_SLASH,
	E_SPN_MS_OP_MODE__MV_CRSLN,

};


//--------------------------------------------------------------

class SPN_Cmn_DlgPane_ShowPic;

//class I_TmListen
//{
//public:
//	virtual void OnListenTm() = 0;
//};

//class MyTimer : public QTimer
//{
//    Q_OBJECT
//
//public:
//	void timerEvent(QTimerEvent *) override
//	{
//		emit myTimeOut();
//	}
//
//signals:
//	void myTimeOut();
//	
//protected:
//};


class SPN_Cmn_DlgPane_ShowPic : public QWidget/*, public I_TmListen*/
{
    Q_OBJECT

public:
    SPN_Cmn_DlgPane_ShowPic(int iPn_0X1Y2Z,QWidget *parent = nullptr);
    ~SPN_Cmn_DlgPane_ShowPic();

	void Hook_iPnSlashing(int* piPnSlashing) 
	{
		m_piPn_Slashing = piPnSlashing;
	}

	void HookTpSel_Img(int* pSelTp)
	{
		m_piSelTpImg = pSelTp;
	}

public:
	void ShowImg2D(const S_Img2D& sImg,int kSlcL);

public:
	//void OnListenTm() override
	//{
	//	StepNewDraw();
	//};

signals:

	void snNewFoc_XY_L(int iS_0X1Y2Z,QPointF P2FocL, SSPN_Cmn_3DPoint<float>& sP3_G,int iSelImgTp);
	void snSlashChg(int iPnSlashing, const SSPN_Cmn_3DPoint<float>& P3G1,const SSPN_Cmn_3DPoint<float>& P3G2);
	void snWLChg(int nW, int iL);


public slots:
	//void StepNewDraw();
	//void on_Btn_ShowPic_clicked();
	////void on_pushButton_clicked()
	void OnNewFoc_XYZ_G(SSPN_Cmn_3DPoint<float>& sP3_G, int iS_0X1Y2Z_ChgSrc);
	void OnWLChg(int nW, int iL);
	void OnGammaChg(bool bGamma);

protected:
	void Transfm_L_to_G(SSPN_Cmn_3DPoint<float>& sP3_Dst,const QPointF& P2L_Src)const;
	void Transfm_G_to_L(QPointF& P2L_Src,const SSPN_Cmn_3DPoint<float>& sP3_Dst)const;

	void Transfm_L_to_V(QPoint& P2V,const QPointF& P2L)const;
	void Transfm_V_to_L(QPointF& P2L, const QPoint& P2V)const;

public:
	void Set_eMsOp_Modeb(E_SPN_MS_OP_MODE eMsOp);

protected:
	virtual void	paintEvent(QPaintEvent* pEvntPaint) override;	// 重写绘制事件，显示在widgt上面
	virtual void	resizeEvent(QResizeEvent*) override;
	virtual void	moveEvent(QMoveEvent*) override;

	virtual void	mousePressEvent(QMouseEvent *event)override;
	virtual void	mouseReleaseEvent(QMouseEvent *event)override;
	virtual void	mouseDoubleClickEvent(QMouseEvent *event)override;

	virtual void	mouseMoveEvent(QMouseEvent *event)override;
	virtual void	mouseMoveEvent_Free(QMouseEvent *event);
	virtual void	mouseMoveEvent_Left(QMouseEvent *event);
	virtual void	mouseMoveEvent_Mid(QMouseEvent *event);
	virtual void	mouseMoveEvent_Rt(QMouseEvent *event);

protected:
	void NotifySlashChg();
		//void			paintInMem();				// 绘在内存图片中

protected:
	void			DoDraw(QPaintEvent *pEvntPaint);
	void			DrawFrmLn(QPainter& Painter);

	bool			Update_MemImg();

protected:
	bool			ReadImg();

public:
    Ui::SPN_Cmn_DlgPane_ShowPic	m_uiPnPic;

	QImage						m_QMemImg_VM;					// VM
	short						m_nVwWidth = 3000;
	short						m_iVwLevel = 500;
	bool						m_bGamma = true;
	QPoint						m_PsRtPrs;
	QPoint						m_dPs_Prev;
	const S_Img2D*				m_psImgData_MV = nullptr;		// MV

	QPoint						m_P2_Foc_V;
	QPointF						m_P2_Foc_L;
	int							m_kSlcL_CurImg;
	int*						m_piSelTpImg = nullptr;
	int*						m_piPn_Slashing = nullptr;

	SSPN_Cmn_3DPoint<float>		m_sP3_Foc_G;

	bool						m_bNearHz = 0;
	bool						m_bNearVt = 0;

	bool						m_bL_BtnPress = 0;
	bool						m_bR_BtnPress = 0;
	bool						m_bM_BtnPress = 0;

	bool						m_bDrag_XY = 0;
	bool						m_bDrag_X = 0;
	bool						m_bDrag_Y = 0;

	int							m_iPn_0X1Y2Z;

	E_SPN_MS_OP_MODE			m_eMsOp_Mode = E_SPN_MS_OP_MODE__NULL;

	QLine						m_SlashLn;
	bool						m_bVisible;
	bool						m_bSlashing = false;
};
