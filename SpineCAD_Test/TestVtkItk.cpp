#include "pch.h"
#include "TestVtkItk.h"

#include "CSPN_Cmn_MV3D_CrsLn.h"
#include "CSPN_Cmn_MD_ItkDcmReader.h"

#include<vtkSmartPointer.h>
#include<vtkSphereSource.h>
#include<vtkCylinderSource.h>
#include<vtkRenderWindow.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleTrackballCamera.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkProperty.h>
#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

vtkSmartPointer<vtkActor> Get3D_cylinder(float fH,float fR,float fOpct,double f3Clr[3])
{
	//1. Source(库内或自建): 3D几何建模：******************************************
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	(*cylinder).SetHeight(fH);
	cylinder->SetRadius(fR);
	cylinder->SetResolution(10);

	//2. Mapper: 化妆+培训：**********************************************************************************
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	//3. Actor: 角色 *****************************************************
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->SetVisibility(1);
	cylinderActor->GetProperty()->SetColor(f3Clr);
	cylinderActor->GetProperty()->SetOpacity(fOpct);

	return cylinderActor;
}

vtkSmartPointer<vtkActor> Get3D_Sphere(float fR, float fOpct, double f3Clr[3], double f3Pos[3])
{
	//1. Source(库内或自建): 3D几何建模：******************************************
	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetRadius(fR);
	sphere->SetPhiResolution(6);
	sphere->SetThetaResolution(72);

	//2. Mapper: 化妆+培训：**********************************************************************************
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphere->GetOutputPort());

	//3. Actor: 角色 *****************************************************
	vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);
	sphereActor->SetVisibility(1);
	sphereActor->GetProperty()->SetColor(f3Clr);
	sphereActor->GetProperty()->SetOpacity(fOpct);
	sphereActor->GetProperty()->SetSpecularPower(100);
	sphereActor->GetProperty()->SetSpecular(5);
	sphereActor->GetProperty()->SetDiffuse(0.9);
	sphereActor->GetProperty()->SetDiffuseColor(0,1,0);
	sphereActor->SetPosition(f3Pos);

	return sphereActor;
}


int TestVtkItk::TestITK()
{
	//1.test itk
	std::string StrDcmFile("D:/_SpineCAD/0_MedDat/1813526(1~320)_BAK/0003_0001.dcm");
	CSPN_Cmn_MD_ItkDcmReader DcmReader;
	DcmReader.ReadDcmFile(StrDcmFile);

	int nW = -1, nH = -1;
	void* pBufPx = DcmReader.GetImgBuf(nW, nH);
	assert(pBufPx);
	int k = 1;
	return 0;
}

int TestVtkItk::TestVTK()
{
	//4. Render： 合成效果
	vtkSmartPointer<vtkRenderer> cylinderRender = vtkSmartPointer<vtkRenderer>::New();

	//4A 收集actor
	double fClr1[3]={ 0.9,0.4,0.6 };
	vtkSmartPointer<vtkActor>spActor_cld1 = Get3D_cylinder(10, 2, 1, fClr1);
	cylinderRender->AddActor(spActor_cld1);

	double fClr2[3] = { 0.6,0.2,0.8 };
	vtkSmartPointer<vtkActor>spActor_cld2 = Get3D_cylinder(20, 4, 0.6, fClr2);
	cylinderRender->AddActor(spActor_cld2);

	double fClr3[3] = { 0.3,0.8,0.4 };
	vtkSmartPointer<vtkActor>spActor_cld3 = Get3D_cylinder(30, 8, 0.4, fClr3);
	cylinderRender->AddActor(spActor_cld3);

	double fClrSphr[3] = { 0.5,0.2,0.6 };
	double fPos[3] = { 0,50,0 };
	vtkSmartPointer<vtkActor>spActor_Sphr = Get3D_Sphere(25, 1, fClrSphr, fPos);
	cylinderRender->AddActor(spActor_Sphr);

	CSPN_Cmn_MV3D_CrsLn CrsLnMaker;
	vtkSmartPointer< vtkAssembly> spCrsLn = CrsLnMaker.Get_spActor_CrsLn();
	cylinderRender->AddActor(spCrsLn);

	cylinderRender->SetBackground(0.9, 0.9, 1);

	//5. RenderWindow: 戏台
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(cylinderRender);
	renWin->SetSize(300, 300);

	//6. Interactor: 交互器（操作）
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	//7.Camera: 拍摄
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);

	//8.开始表演
	iren->Initialize();
	iren->Start();
	return 0;
}