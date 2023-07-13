#pragma once

#include "TestVtkItk.h"
#include <QtWidgets/QMainWindow>
#include "ui_SPN_Cmn_Med_SpineCAD.h"

class SPN_Cmn_Med_SpineCAD : public QMainWindow
{
    Q_OBJECT

public:
    SPN_Cmn_Med_SpineCAD(QWidget *parent = nullptr);
    ~SPN_Cmn_Med_SpineCAD();

public slots:
	void on_Btn_ShowDlg_Main_clicked();
	void on_Btn_ShowDlg_DbgImg_Slc_clicked();
	void on_Btn_ShowDlg_DbgImg_clicked();
	void on_Btn_TestVTK_clicked();
	void on_Btn_TestITK_clicked();

private:
	void OpenShow_DcmDir3D(std::string Str_DirPath);

private:
	Ui::SPN_Cmn_Med_SpineCADClass ui;
};
