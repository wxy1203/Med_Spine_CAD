#include "pch.h"
#include "SPN_Cmn_Wnd_Vtk3D.h"
#include <QVTKOpenGLNativeWidget.h>



SPN_Cmn_Wnd_Vtk3D::SPN_Cmn_Wnd_Vtk3D(QWidget* pWndPa/*=nullptr*/)
	: QVTKOpenGLNativeWidget(pWndPa)
{
	ui.setupUi(this);


}

SPN_Cmn_Wnd_Vtk3D::~SPN_Cmn_Wnd_Vtk3D()
{

}

#ifdef tmpvtksammplecode

vtkSmartPointer<vtkRenderWindow> CoArt_Test_Cx_CPR_VesStrten::GetMk_RenderWindow(bool bUseQtWnd, CHPG_BS_2DSize<int> SzWndIni, Pnt2D_Int& P2_WndPos)
{
	vtkSmartPointer<vtkRenderWindow> spRndWnd;

	if (bUseQtWnd)
	{
		QSurfaceFormat::setDefaultFormat(CoArt_Test_VV_3D_Widget::defaultFormat());

		CoArt_Test_VV_3D_Widget* pWnd3D_Qt = nullptr;
		{
			static bool bUseAs_StandaloneDlgWnd = 0;
			if (bUseAs_StandaloneDlgWnd)
			{
				//vtkSmartPointer<CoArt_Test_VV_3D_Widget> spQtWnd3D = new CoArt_Test_VV_3D_Widget;// ::New();// CoArt_Test_VV_3D_Widget(nullptr);
				QSurfaceFormat::setDefaultFormat(CoArt_Test_VV_3D_Widget::defaultFormat());

				pWnd3D_Qt = new CoArt_Test_VV_3D_Widget;// ::New();// CoArt_Test_VV_3D_Widget(nullptr);
				pWnd3D_Qt->resize(SzWndIni[0], SzWndIni[1]);
				pWnd3D_Qt->move(P2_WndPos[0], P2_WndPos[1]);
				pWnd3D_Qt->setWindowTitle("Qt_Wnd__for__PntPicker");// setVisible(true);
				pWnd3D_Qt->show();
			}
			else
			{
				pWnd3D_Qt = this->m_pCxToMgr->m_pDlg_CoArt_VxTopMgr->m_pVw_3D;
			}

		}

		/ tkSmartPointer<vtkGenericOpenGLRenderWindow> spGenericGLRndWnd = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
		//{
		//	renderWindow->AddRenderer(pRender);
		//	renderWindow->SetWindowName("RenderWindowNoUIFile");
		//}
		//pWnd3D_Qt->SetRenderWindow(spGenericGLRndWnd);
		//spRndWnd = spGenericGLRndWnd;
		// => 解决窗口作为子窗口时，黑色不绘制3D内容问题：不能用自己创建的vtkGenericOpenGLRenderWindow再加进去！
		spRndWnd = pWnd3D_Qt->GetRenderWindow();
	}
	else
	{
		spRndWnd = vtkRenderWindow::New();
		spRndWnd->SetSize(SzWndIni[0], SzWndIni[1]);
		spRndWnd->SetPosition(P2_WndPos[0], P2_WndPos[1]);
	}

	return spRndWnd;
}

#endif