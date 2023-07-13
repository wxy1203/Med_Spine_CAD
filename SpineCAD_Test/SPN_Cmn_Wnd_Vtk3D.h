#pragma once

#include "ui_SPN_Cmn_Wnd_Vtk3D.h"


#include <QVTKOpenGLNativeWidget.h>

class SPN_Cmn_Wnd_Vtk3D 
	: public QVTKOpenGLNativeWidget
	//, public vtkObject
{
	Q_OBJECT

public:
	//static vtkRenderWindowInteractor *New();
	static SPN_Cmn_Wnd_Vtk3D* New()
	{
		return new SPN_Cmn_Wnd_Vtk3D;
	}
	//vtkTypeMacro(vtkRenderWindowInteractor, vtkObject);
	//vtkTypeMacro(SPN_Cmn_Wnd_Vtk3D, vtkObject);




	SPN_Cmn_Wnd_Vtk3D(QWidget* pWndPa=nullptr);
	~SPN_Cmn_Wnd_Vtk3D();


public slots:

protected:
	Ui::SPN_Cmn_Wnd_Vtk3D	 ui;

};

