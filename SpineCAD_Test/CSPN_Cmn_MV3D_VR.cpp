#include "pch.h"

#include "CSPN_Cmn_MV3D_VR.h"
#include "SPN_Cmn_Wnd_Vtk3D.h"

#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkImagePlaneWidget.h>
#include <vtkMarchingCubes.h>
#include <vtkImageCast.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkImageMapToColors.h>
#include <vtkProperty.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkAutoInit.h>
#include <vtkShortArray.h>
#include <QMainWindow>


VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)

CSPN_Cmn_MV3D_VR::CSPN_Cmn_MV3D_VR()
{

}

CSPN_Cmn_MV3D_VR::~CSPN_Cmn_MV3D_VR()
{

}

void CSPN_Cmn_MV3D_VR::Show3D_VR(const CSPN_Cmn_3DMtx<short>& crMtx_Dcm)
{
	//1. ��ȡdcm�ļ�
	//std::string folder = "dcm_folder";
	//
	////read all the dicom files with the received path.
	//vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	//reader->SetDirectoryName(folder.c_str());
	//reader->Update();
	//
	//int imageDims[3];
	//reader->GetOutput()->GetDimensions(imageDims); //need include <vtkimagedata.h>
	//cout << "dimension[] :" << imageDims[0] << " " << imageDims[1] << " " << imageDims[2] << endl;
	//
	//vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
	//cast->SetInputData((vtkDataObject*)reader->GetOutput());
	////cast->SetOutputScalarTypeToFloat();
	//cast->Update();

	vtkSmartPointer<vtkShortArray> spDtArr = vtkSmartPointer<vtkShortArray>::New();
	{
		spDtArr->SetNumberOfComponents(1);//sizeof(short));//(1);
		//����ԭʼ����, reuseDataΪ1�Ļ�ֻ���ò����������겻ɾ��!
		int bReuseData = 1;
		spDtArr->SetArray(crMtx_Dcm.GetVoxMem(), crMtx_Dcm.GetSize_Mtx(), bReuseData, vtkAbstractArray::VTK_DATA_ARRAY_DELETE);
	}

	vtkSmartPointer<vtkImageData> spImDt = vtkSmartPointer<vtkImageData>::New();
	{
		spImDt->SetExtent(0, crMtx_Dcm.GetUpperBound_X(),
						  0, crMtx_Dcm.GetUpperBound_Y(),
						  0, crMtx_Dcm.GetUpperBound_Z());
		spImDt->GetPointData()->SetScalars(spDtArr);
		spImDt->SetSpacing(fabs(crMtx_Dcm.GetP3D_Spc_X()), fabs(crMtx_Dcm.GetP3D_Spc_Y()), fabs(crMtx_Dcm.GetP3D_Spc_Z())); // **** ����ർ�²����ڵ��Ĵ���Ч��!
		//m_spDtArr->Delete();
	}

	//// tkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFun = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	//
	//// tkSmartPointer<vtkFixedPointVolumeRayCastMapper> m_spVRMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
	//vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_spVRMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	//{
	//	//m_spVRMapper->SetInputConnection(reader->GetOutputPort());
	//	m_spVRMapper->SetInputData(spImDt);
	//	m_spVRMapper->SetAutoAdjustSampleDistances(1);//(0);
	//	m_spVRMapper->SetSampleDistance(0.5);
	//	//m_spVRMapper->SetImageSampleDistance(0.5);
	//}

	//2.**********************************************************************
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapperGpu = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	{
		//����GPU���ٵĹ���Ͷ��������㷨
		volumeMapperGpu->SetInputData(spImDt);
		volumeMapperGpu->SetImageSampleDistance(1.);  //0.5 ==> 1.0
		volumeMapperGpu->SetSampleDistance(1.0);
		volumeMapperGpu->SetAutoAdjustSampleDistances(1);
	}

	//3.***********************************************************************
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();//�����������
	{
		volumeProperty->SetInterpolationTypeToLinear();
		volumeProperty->ShadeOn();
		volumeProperty->SetAmbient(0.4); //0.4
		volumeProperty->SetDiffuse(0.5);
		volumeProperty->SetSpecular(0.1);

		vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
		//Defines a piecewise function mapping.
		compositeOpacity->AddPoint(60, 0.00);
		compositeOpacity->AddPoint(140, 0.40);
		compositeOpacity->AddPoint(180, 0.90);


		volumeProperty->SetScalarOpacity(compositeOpacity);

		vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
		color->AddRGBPoint(0, 0, 0, 0);
		color->AddRGBPoint(64, 1, 0.52, 0.30);
		color->AddRGBPoint(190.0, 1, 1, 1);
		color->AddRGBPoint(220, 0.2, 0.2, 0.2);

		volumeProperty->SetColor(color);
	}

	//4.�������ʾ����
	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	{
		//represents a volume(data & properties) in a rendered scene
		volume->SetMapper(volumeMapperGpu);
		volume->SetProperty(volumeProperty);
	}

	//5.��ʾƽ̨
	vtkSmartPointer<vtkRenderer>				rendererVolume = vtkSmartPointer<vtkRenderer>::New();





	//vtkSmartPointer<vtkRenderWindow>			renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	//vtkSmartPointer<SPN_Cmn_Wnd_Vtk3D>			spQDlgVtk = vtkSmartPointer<SPN_Cmn_Wnd_Vtk3D>::New();
	QSurfaceFormat::setDefaultFormat(SPN_Cmn_Wnd_Vtk3D::defaultFormat());

	SPN_Cmn_Wnd_Vtk3D* spQDlgVtk = new SPN_Cmn_Wnd_Vtk3D;

	spQDlgVtk->setWindowModality(Qt::NonModal);

	vtkSmartPointer<vtkRenderWindow>			renderWindow = spQDlgVtk->GetRenderWindow();







	vtkSmartPointer<vtkRenderWindowInteractor>	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	//6.��ʾ��װ
	rendererVolume->AddVolume(volume);
	renderWindow->AddRenderer(rendererVolume);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	//7.��ʼ��ʾ
	renderWindow->Render();
	renderWindowInteractor->Start();
}

