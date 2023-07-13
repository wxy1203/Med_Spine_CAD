#pragma once
#include <QTimerEvent>
#include <QObject>
class CSPN_Cmn_Mx_Demo_3DMtx:public QObject
{
	Q_OBJECT

public:
	CSPN_Cmn_Mx_Demo_3DMtx();
	~CSPN_Cmn_Mx_Demo_3DMtx();

	void Construct_3DMtx();
	int  ReadDcmDir(std::string Str_DirPath);

	void InitPaint();

public:
	void StepNewCalc();

	void ShowImg_Slc_Slash(int iPn_0X1Y2Z, const SSPN_Cmn_3DPoint<float>& P3G1, const SSPN_Cmn_3DPoint<float>& P3G2);
	void ShowImg_Slc_Ax(int kSlcShow);
	void ShowImg_Slc_Co(int jSlcShow);
	void ShowImg_Slc_Sa(int iSlcShow);

	void ShowImg_DRR_Ax();
	void ShowImg_DRR_Co();
	void ShowImg_DRR_Sa();

	void ShowImg_MaxIP_Ax();
	void ShowImg_MaxIp_Co();
	void ShowImg_MaxIP_Sa();


signals:
	void Sn_ShowImgSlc_Ax(S_Img2D* pImgSum,int kSlcImg);
	void Sn_ShowImgSlc_Co(S_Img2D* pImgSum,int jSlcImg);
	void Sn_ShowImgSlc_Sa(S_Img2D* pImgSum,int iSlcImg);
	void Sn_ShowImgSlc_Slash(S_Img2D* pImgSum,int kSlcImg);

	void Sn_FocChg(SSPN_Cmn_3DPoint<float>& sP3FocImg, int iPn_ChgSrc);

public slots:
	void OnFocChg_MPR(int iS_0X1Y2Z,QPointF P2FocL, SSPN_Cmn_3DPoint<float>& sP3_G,int iSelImgTp_0MPR_1DRR_2MaxIP);
	void onSlashChg(int iPnSlashing, const SSPN_Cmn_3DPoint<float>& P3G1, const SSPN_Cmn_3DPoint<float>& P3G2);

	void onImgTp_SelChg(int iSel_Tp);

public:
	void timerEvent(QTimerEvent *event) override;

public:
	CSPN_Cmn_3DMtx<short>	m_Mtx3D;

protected:
	CSPN_Cmn_3DPoint<float> m_P3fFoc_MPR;

	int						m_iTimerId = -1;
	int						m_nStepClc=0;

	S_Img2D*				m_pImgSum_AxDRR = nullptr;
	S_Img2D*				m_pImgSum_CoDRR = nullptr;
	S_Img2D*				m_pImgSum_SaDRR = nullptr;

	S_Img2D*				m_pImgSum_AxMaxIP = nullptr;
	S_Img2D*				m_pImgSum_CoMaxIP = nullptr;
	S_Img2D*				m_pImgSum_SaMaxIP = nullptr;
};

