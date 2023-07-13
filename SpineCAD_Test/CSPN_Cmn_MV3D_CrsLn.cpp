#include "pch.h"
#include "CSPN_Cmn_MV3D_CrsLn.h"
#include "vtkLineSource.h"
#include<vtkSmartPointer.h>

#include<vtkCylinderSource.h>
#include<vtkRenderWindow.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleTrackballCamera.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkProperty.h>


#include "vtkAutoInit.h"

CSPN_Cmn_MV3D_CrsLn::CSPN_Cmn_MV3D_CrsLn()
	: m_pP3_Foc{ 0,0,0 }
	, m_fLeng(100)
	, m_spAsm_CrsLn(nullptr)
	, m_spActor_XYZ{ nullptr,nullptr,nullptr }
	, m_f3Clr3_XYZ{ {1,0,0},{0,1,0},{0,0,1} }
{

}
CSPN_Cmn_MV3D_CrsLn::~CSPN_Cmn_MV3D_CrsLn()
{

}

vtkSmartPointer<vtkAssembly> CSPN_Cmn_MV3D_CrsLn::Get_spActor_CrsLn()
{
	if (nullptr == m_spAsm_CrsLn)
	{
		m_spAsm_CrsLn = vtkSmartPointer<vtkAssembly>::New();
		double pf3Bgn_XYZ[3][3];
		double pf3End_XYZ[3][3];
		{
			pf3Bgn_XYZ[0][0] = this->m_pP3_Foc[0] - 0.5*(this->m_fLeng);
			pf3Bgn_XYZ[0][1] = this->m_pP3_Foc[1];
			pf3Bgn_XYZ[0][2] = this->m_pP3_Foc[2];

			pf3Bgn_XYZ[1][0] = this->m_pP3_Foc[0];
			pf3Bgn_XYZ[1][1] = this->m_pP3_Foc[1] - 0.5*(this->m_fLeng);
			pf3Bgn_XYZ[1][2] = this->m_pP3_Foc[2];

			pf3Bgn_XYZ[2][0] = this->m_pP3_Foc[0];
			pf3Bgn_XYZ[2][1] = this->m_pP3_Foc[1];
			pf3Bgn_XYZ[2][2] = this->m_pP3_Foc[2] - 0.5*(this->m_fLeng);

			pf3End_XYZ[0][0] = this->m_pP3_Foc[0] + 0.5*(this->m_fLeng);
			pf3End_XYZ[0][1] = this->m_pP3_Foc[1];
			pf3End_XYZ[0][2] = this->m_pP3_Foc[2];

			pf3End_XYZ[1][0] = this->m_pP3_Foc[0];
			pf3End_XYZ[1][1] = this->m_pP3_Foc[1] + 0.5*(this->m_fLeng);
			pf3End_XYZ[1][2] = this->m_pP3_Foc[2];

			pf3End_XYZ[2][0] = this->m_pP3_Foc[0];
			pf3End_XYZ[2][1] = this->m_pP3_Foc[1];
			pf3End_XYZ[2][2] = this->m_pP3_Foc[2] + 0.5*(this->m_fLeng);
		}


		for (int j = 0; j < 3; j++)
		{

			//1. Source(库内或自建): 3D几何建模：******************************************
			vtkSmartPointer<vtkLineSource> spLineSrc = vtkSmartPointer<vtkLineSource>::New();
			spLineSrc->SetPoint1(pf3Bgn_XYZ[j]);
			spLineSrc->SetPoint2(pf3End_XYZ[j]);

			//2. Mapper: 化妆+培训：**********************************************************************************
			vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			cylinderMapper->SetInputConnection(spLineSrc->GetOutputPort());

			//3. Actor: 角色 *****************************************************
			this->m_spActor_XYZ[j] = vtkSmartPointer<vtkActor>::New();
			this->m_spActor_XYZ[j]->SetMapper(cylinderMapper);
			this->m_spActor_XYZ[j]->SetVisibility(1);
			this->m_spActor_XYZ[j]->GetProperty()->SetColor(m_f3Clr3_XYZ[j]);

			m_spAsm_CrsLn->AddPart(m_spActor_XYZ[j]);

			////3A. Assembler: 角色捆绑
			//
			////4. Render： 合成效果
			//vtkSmartPointer<vtkRenderer> cylinderRender = vtkSmartPointer<vtkRenderer>::New();
			//cylinderRender->AddActor(cylinderActor);
			//cylinderRender->SetBackground(0.1, 0.2, 0.4);
			//
			////5. RenderWindow: 戏台
			//vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
			//renWin->AddRenderer(cylinderRender);
			//renWin->SetSize(300, 300);
			//
			////6. Interactor: 交互器（操作）
			//vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
			//iren->SetRenderWindow(renWin);
			//
			////7.Camera: 拍摄
			//vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
			//iren->SetInteractorStyle(style);
			//
			////8.开始表演
			//iren->Initialize();
			//iren->Start();
		}
	}
	return m_spAsm_CrsLn;
}
