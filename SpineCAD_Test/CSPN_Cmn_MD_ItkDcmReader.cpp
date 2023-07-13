#include "pch.h"
#include "CSPN_Cmn_MD_ItkDcmReader.h"
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


//using namespace std;
//typedef short PixelType;
//const unsigned int Dimension = 2;
//typedef itk::Image< PixelType, Dimension > Input2dImageType;
//typedef itk::Image< PixelType, 3 > Input3dImageType;
//typedef itk::Image< PixelType, Dimension > Output2dImageType;
//typedef itk::Image< PixelType, 3 > Output3dImageType;
//typedef itk::GDCMImageIO ImageIOType;//GDCMImageIO读DICOM
//
//void CItkDcmRead::TestReadDcm(std::string file_path_str)
//{
//	ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
//
//	using ReaderType3d = itk::ImageSeriesReader< Input3dImageType >;
//	ReaderType3d::Pointer reader3d = ReaderType3d::New();
//
//	typedef itk::ImageFileReader< Input2dImageType > ReaderType2d;
//	ReaderType2d::Pointer reader2d = ReaderType2d::New();
//
//	using NamesGeneratorType = itk::GDCMSeriesFileNames;
//	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
//
//	//主要实现
//	reader3d->SetImageIO(gdcmImageIO);
//
//	nameGenerator->SetUseSeriesDetails(true);
//	nameGenerator->SetDirectory(file_path_str);
//
//	using SeriesIdContainer = std::vector< std::string >;
//	const SeriesIdContainer& seriesUID = nameGenerator->GetSeriesUIDs();
//
//	auto seriesItr = seriesUID.begin();
//	auto seriesEnd = seriesUID.end();
//	using FileNamesContainer = std::vector< std::string >;
//	FileNamesContainer fileNames;
//	std::string seriesIdentifier;
//	while (seriesItr != seriesEnd)
//	{
//		seriesIdentifier = seriesItr->c_str();
//		fileNames = nameGenerator->GetFileNames(seriesIdentifier);
//		++seriesItr;
//
//	}
//	reader3d->SetFileNames(fileNames);
//	reader3d->Update();
//
//	//typedef itk::ImageToVTKImageFilter< Input3dImageType> itkTovtkFilterType;
//	//
//	//itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
//	//itkTovtkImageFilter->SetInput(reader3d->GetOutput());//设置图像数据从ITK转向VTK
//	//itkTovtkImageFilter->Update();
//	//
//	//vtkSmartPointer< vtkImageFlip > reader1 = vtkSmartPointer< vtkImageFlip >::New();
//	//
//	//reader1->SetInputData(itkTovtkImageFilter->GetOutput());
//	//reader1->SetFilteredAxes(1);
//	//reader1->Update();
//
//}



bool CSPN_Cmn_MD_ItkDcmReader::ReadDcmFile(std::string file_path_str)
{
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(file_path_str);

	ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
	reader->SetImageIO(gdcmImageIO);

	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject & e)
	{
		std::cerr << "exception in file reader " << std::endl;
		std::cerr << e << std::endl;
		return false;
	}

	//typedef itk::ImageFileWriter< InputImageType >  Writer1Type;
	//Writer1Type::Pointer writer = Writer1Type::New();
	//writer->SetFileName("C:/output/lung.dcm");
	//writer->SetInput(reader->GetOutput());
	//
	//try
	//{
	//	writer->Update();
	//}
	//catch (itk::ExceptionObject & e)
	//{
	//	std::cerr << "exception in file writer " << std::endl;
	//	std::cerr << e << std::endl;
	//	return false;
	//}

	m_pImgItk = reader->GetOutput();//itk::Image<InputPixelType>::New();

	//using ImageType = itk::Image<int, 3>;
	//using ReaderType = itk::ImageFileReader<ImageType>;
	//const char* src_path = "H:\\tmp\\a.mhd";
	//auto reader = ReaderType::New();
	//reader->SetFileName(src_path);
	//reader->Update();
	//auto image = reader->GetOutput();

	short * buffer = m_pImgItk->GetBufferPointer(); // 这是一块连续的内存
	InputImageType::SizeType size = m_pImgItk->GetLargestPossibleRegion().GetSize();
	//std::cout << buffer[10 * size[0] * size[1] + 207 * size[0] + 92] << std::endl;
	m_StrFPath = file_path_str;
	return true;
}
