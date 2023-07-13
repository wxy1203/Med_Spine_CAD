#include "pch.h"

#include "CSPN_Cmn_MD_ItkDcm_Dir3D.h"
#include "CSPN_Cmn_MD_ItkDcmReader.h"
#include "SPN_Cmn_WString.h"
#include "SPN_Cmn_FileDir_Filter.h"

CSPN_Cmn_MD_ItkDcm_Dir3D::CSPN_Cmn_MD_ItkDcm_Dir3D()
{

}

CSPN_Cmn_MD_ItkDcm_Dir3D::~CSPN_Cmn_MD_ItkDcm_Dir3D()
{

}

int	CSPN_Cmn_MD_ItkDcm_Dir3D::Load_Construct(std::string Str_DirPath)
{
	//1.搜集目录下所有文件
	std::vector<SPN_String> ArrStrFPath_Dst;
	bool bOK= CSPN_Cmn_FileDir_Filter::GetAllPath_Files_inDir(ArrStrFPath_Dst,SPN_String(Str_DirPath).To_QString(), false);
	if (!bOK)
	{
		return 0;
	}

	//std::vector<CSPN_Cmn_MD_ItkDcmReader*> m_Arr_pDcmFileRd;
	//2.尝试读取dcm文件
	for (int i = 0; i < ArrStrFPath_Dst.size(); i++)
	{
		CSPN_Cmn_MD_ItkDcmReader* pDcmRd = new CSPN_Cmn_MD_ItkDcmReader;
		bool bOK = (*pDcmRd).ReadDcmFile(ArrStrFPath_Dst[i].To_StdString());
		if (bOK)
		{
			m_Arr_pDcmFileRd.push_back(pDcmRd);
		}
		else
		{
			delete pDcmRd;
			pDcmRd = nullptr;
		}
	}

	//3.dcm文件按Z坐标排序
	Sort_DCMFile();


	return m_Arr_pDcmFileRd.size();
}
void* CSPN_Cmn_MD_ItkDcm_Dir3D::Get_pImgBuf(int& nW, int& nH, int kSlc)
{
	void* pBufSlc = this->m_Arr_pDcmFileRd[kSlc]->GetImgBuf(nW, nH);
	return pBufSlc;
}

void CSPN_Cmn_MD_ItkDcm_Dir3D::Sort_DCMFile()
{
	::qsort(m_Arr_pDcmFileRd.data(),m_Arr_pDcmFileRd.size() ,sizeof(CSPN_Cmn_MD_ItkDcmReader*) , CSPN_Cmn_MD_ItkDcmReader::Cmp_DcmRd);
	for (int i = 0; i < m_Arr_pDcmFileRd.size(); i++)
	{
		std::string sTmp = m_Arr_pDcmFileRd[i]->m_StrFPath;
		float fZ = m_Arr_pDcmFileRd[i]->m_pImgItk->GetOrigin()[2];
		int k = 0;
	}
}

SSPN_Cmn_3DPoint<float> CSPN_Cmn_MD_ItkDcm_Dir3D::GetSlcPos()
{
	SSPN_Cmn_3DPoint<float> P3Bgn;
	P3Bgn[0] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetOrigin()[0];
	P3Bgn[1] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetOrigin()[1];
	P3Bgn[2] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetOrigin()[2];
	return P3Bgn;
}

SSPN_Cmn_3DPoint<float> CSPN_Cmn_MD_ItkDcm_Dir3D::GetSpcXYZ()
{
	SSPN_Cmn_3DPoint<float> P3Spc;
	P3Spc[0] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetSpacing()[0];
	P3Spc[1] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetSpacing()[1];
	P3Spc[2] = this->m_Arr_pDcmFileRd[0]->m_pImgItk->GetSpacing()[2];
	return P3Spc;
	
}
