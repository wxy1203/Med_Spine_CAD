#pragma once

#include <string>

class CSPN_Cmn_MD_ItkDcmReader;

class CSPN_Cmn_MD_ItkDcm_Dir3D
{
public:
	CSPN_Cmn_MD_ItkDcm_Dir3D();
	~CSPN_Cmn_MD_ItkDcm_Dir3D();

public:
	int						Load_Construct(std::string Str_DirPath);
	void*					Get_pImgBuf(int& nW, int& nH,int kSlc);
	SSPN_Cmn_3DPoint<float>	GetSlcPos();
	SSPN_Cmn_3DPoint<float>	GetSpcXYZ();

protected:
	void Sort_DCMFile();


protected:
	std::vector<CSPN_Cmn_MD_ItkDcmReader*> m_Arr_pDcmFileRd;

};

