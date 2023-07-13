#pragma once
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGDCMImageIO.h"

#include <list>
#include <fstream>

//#include "itkImageToVTKImageFilter.h"
#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
//#include "ImageToVTKImageFilter.h"
#include <string>


class CSPN_Cmn_MD_ItkDcmReader
{	
	friend class CSPN_Cmn_MD_ItkDcm_Dir3D;
	enum{													C_InputDimension = 3 };
	typedef signed short									InputPixelType;

	typedef itk::Image< InputPixelType, C_InputDimension >  InputImageType;
	typedef itk::ImageFileReader< InputImageType >			ReaderType;
	typedef itk::GDCMImageIO								ImageIOType;


public:
	bool ReadDcmFile(std::string file_path_str);

	void* GetImgBuf(int& nW, int& nH)
	{
		if (m_pImgItk)
		{
			nW = m_pImgItk->GetLargestPossibleRegion().GetSize()[0];
			nH = m_pImgItk->GetLargestPossibleRegion().GetSize()[1];
			return m_pImgItk->GetBufferPointer();
		}
		else
		{
			return nullptr;
		}
	}


public:
	static int Cmp_DcmRd(const void* p1, const void* p2)
	{
		const CSPN_Cmn_MD_ItkDcmReader& DcmRd1 = **((const CSPN_Cmn_MD_ItkDcmReader**)(p1));
		const CSPN_Cmn_MD_ItkDcmReader& DcmRd2 = **((const CSPN_Cmn_MD_ItkDcmReader**)(p2));

		//HJ????
		float fdZ = DcmRd1.m_pImgItk->GetOrigin()[2] - DcmRd2.m_pImgItk->GetOrigin()[2];
		if (fdZ > 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}

		//暂用文件名排序并假定z坐标为0,1,2，...
		//std::string StrFName1 = DcmRd1.m_StrFPath;
		//std::string StrFName2 = DcmRd2.m_StrFPath;
		//if (StrFName1 > StrFName2)
		//{
		//	return 1;
		//}
		//else
		//{
		//	return -1;
		//}
	}

protected:
	itk::Image<InputPixelType, C_InputDimension>::Pointer m_pImgItk = nullptr;
	std::string m_StrFPath;

};

