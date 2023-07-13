#include "pch.h"
#include "SPN_Cmn_DlgPane_3D.h"
#include "SPN_Cmn_DirFileOp.h"

#include <QPainter>
#include <QRectF>
#include <QVector>
#include <QResizeEvent>
#include <QColor>
#include <QWidget>
#include "windows.h"
#include "math.h"

//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
SPN_Cmn_DlgPane_3D::SPN_Cmn_DlgPane_3D(QWidget *parent)
    : SPN_Cmn_DlgPane_ShowPic(0,parent)
{

}
//----------------------------------------------------------------------------------------------

SPN_Cmn_DlgPane_3D::~SPN_Cmn_DlgPane_3D()
{

}

void SPN_Cmn_DlgPane_3D::paintEvent(QPaintEvent* pEvntPaint)
{
	QPainter Painter(this);
	Painter.save();
	if (1)
	{
		SPN_Cmn_DlgPane_ShowPic::DrawFrmLn(Painter);
	}
	else
	{

	}
	Painter.restore();
	Painter.end();
}




