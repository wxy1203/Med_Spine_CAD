#pragma once
#include "pch.h"
#include <QtWidgets/QMainWindow>
#include "ui_SPN_Cmn_Dlg_DbgImg.h"

#include "SPN_Cmn_DlgPane_ShowPic.h"

#include <cmath>

//class S_Img2D;

class Spring
{
public:
	enum 
	{
		E_C_nW_Img = 512,
		E_C_nH_Img = 512,
	};

public:
	S_Img2D* CalcImg(int iCx, int jCy, float fAPhase)
	{
		//1
		S_Img2D* pImg2D = new S_Img2D;
		S_Img2D& sImg = *pImg2D;
		{
			//1A
			sImg.Set_nXYZ(E_C_nW_Img, E_C_nH_Img,1);

			//1B
			float fCx = iCx; //E_C_nW_Img * 0.5f;
			float fCy = jCy; //E_C_nH_Img * 0.5f;

#pragma omp parallel for
			for (int j = 0; j < sImg.GetSize_Y(); j++)
			{
				float fRy2 = (j - fCy); fRy2 *= fRy2;

				for (int i = 0; i < sImg.GetSize_X(); i++)
				{
					float fRx2 = (i - fCx); fRx2 *= fRx2;
					float fR = sqrt(fRx2 + fRy2);

					//*(sImg.m_pfImgBuf + j * sImg.m_nW + i) = fPix;
					//<==>
					sImg.GetVox(i,j,0) = sin(fR*0.1f + fAPhase) / (1+pow(fR, 0.7)) * 2000;
					//<==>
					//sImg.m_pfImgBuf[iPx++] = fPix;
				}
			}
		}

		return pImg2D;
	}

public:

	static void CalcSumImg(S_Img2D& sImgSum, const std::vector<Spring*>& rArr_pSping, float fAPhase)
	{
		int iCx[3] = { 100, 200, 400 };
		int jCy[3] = { 400, 200, 300 };

		for (int i = 0; i < rArr_pSping.size(); i++)
		{
			S_Img2D* pImg = rArr_pSping[i]->CalcImg(iCx[i], jCy[i], fAPhase + i*1.5);

			sImgSum += *pImg;

			delete pImg;
			pImg = nullptr;
		}
	}
};

//---------------------------------------------------------------

class SPN_Cmn_Dlg_DbgImg : public QDialog/*, public I_TmListen*/
{
	Q_OBJECT

public:
	SPN_Cmn_Dlg_DbgImg(QWidget *parent = nullptr);
	~SPN_Cmn_Dlg_DbgImg();

public slots:
	void resizeEvent(QResizeEvent *) override;
	void ShowImg2D(S_Img2D* pImgSum,int kSlcImg);

	//void StepNewCalc();


	//void OnListenTm() override;

private:
	Ui::SPN_Cmn_Dlg_DbgImg	ui;

	SPN_Cmn_DlgPane_ShowPic* m_pPanePic = nullptr;

	//std::vector<Spring*>	m_Arr_pSping;

	////S_Img2D*				m_pImg2D = nullptr;
	//int   m_nStepClc = 0;//
	//float m_fAPhase = 0;

};

