#pragma once

class Spring;

class CSPN_Cmn_Mx_Demo_Animate : public QObject
{
	Q_OBJECT

public:
	CSPN_Cmn_Mx_Demo_Animate();
	~CSPN_Cmn_Mx_Demo_Animate();

public slots:
	void StepNewCalc();

signals:
	void Sn_ShowImg2D(S_Img2D* pImgSum,int iSlcImg);


public:
	void ShowImg2D();

	void timerEvent(QTimerEvent *event)override;

public:	
	int   m_nStepClc = 0;//
	float m_fAPhase = 0;
	int m_iTimerID = -1;
	std::vector<Spring*>	m_Arr_pSping;


};

