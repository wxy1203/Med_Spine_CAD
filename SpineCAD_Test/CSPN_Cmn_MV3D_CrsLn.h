#pragma once

#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkAssembly.h>

class CSPN_Cmn_MV3D_CrsLn
{
public:
	CSPN_Cmn_MV3D_CrsLn();
	~CSPN_Cmn_MV3D_CrsLn();

public:
	vtkSmartPointer<vtkAssembly> Get_spActor_CrsLn();

protected:
	double						m_pP3_Foc[3];
	double						m_fLeng;

	vtkSmartPointer<vtkAssembly>m_spAsm_CrsLn;
	vtkSmartPointer<vtkActor>	m_spActor_XYZ[3];
	double						m_f3Clr3_XYZ[3][3];
};

