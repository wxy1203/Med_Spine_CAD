/********************************************************************************
** Form generated from reading UI file 'SPN_Cmn_Med_SpineCAD.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPN_CMN_MED_SPINECAD_H
#define UI_SPN_CMN_MED_SPINECAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SPN_Cmn_Med_SpineCADClass
{
public:
    QWidget *centralWidget;
    QPushButton *Btn_ShowDlg_DbgImg;
    QPushButton *Btn_ShowDlg_Main;
    QPushButton *Btn_ShowDlg_DbgImg_Slc;
    QPushButton *Btn_TestVTK;
    QPushButton *Btn_TestITK;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SPN_Cmn_Med_SpineCADClass)
    {
        if (SPN_Cmn_Med_SpineCADClass->objectName().isEmpty())
            SPN_Cmn_Med_SpineCADClass->setObjectName(QString::fromUtf8("SPN_Cmn_Med_SpineCADClass"));
        SPN_Cmn_Med_SpineCADClass->resize(600, 400);
        centralWidget = new QWidget(SPN_Cmn_Med_SpineCADClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Btn_ShowDlg_DbgImg = new QPushButton(centralWidget);
        Btn_ShowDlg_DbgImg->setObjectName(QString::fromUtf8("Btn_ShowDlg_DbgImg"));
        Btn_ShowDlg_DbgImg->setGeometry(QRect(420, 20, 161, 23));
        Btn_ShowDlg_Main = new QPushButton(centralWidget);
        Btn_ShowDlg_Main->setObjectName(QString::fromUtf8("Btn_ShowDlg_Main"));
        Btn_ShowDlg_Main->setGeometry(QRect(420, 80, 161, 23));
        Btn_ShowDlg_DbgImg_Slc = new QPushButton(centralWidget);
        Btn_ShowDlg_DbgImg_Slc->setObjectName(QString::fromUtf8("Btn_ShowDlg_DbgImg_Slc"));
        Btn_ShowDlg_DbgImg_Slc->setGeometry(QRect(420, 50, 161, 23));
        Btn_TestVTK = new QPushButton(centralWidget);
        Btn_TestVTK->setObjectName(QString::fromUtf8("Btn_TestVTK"));
        Btn_TestVTK->setGeometry(QRect(310, 20, 75, 23));
        Btn_TestITK = new QPushButton(centralWidget);
        Btn_TestITK->setObjectName(QString::fromUtf8("Btn_TestITK"));
        Btn_TestITK->setGeometry(QRect(310, 50, 75, 23));
        SPN_Cmn_Med_SpineCADClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SPN_Cmn_Med_SpineCADClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        SPN_Cmn_Med_SpineCADClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SPN_Cmn_Med_SpineCADClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SPN_Cmn_Med_SpineCADClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SPN_Cmn_Med_SpineCADClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SPN_Cmn_Med_SpineCADClass->setStatusBar(statusBar);

        retranslateUi(SPN_Cmn_Med_SpineCADClass);

        QMetaObject::connectSlotsByName(SPN_Cmn_Med_SpineCADClass);
    } // setupUi

    void retranslateUi(QMainWindow *SPN_Cmn_Med_SpineCADClass)
    {
        SPN_Cmn_Med_SpineCADClass->setWindowTitle(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "SPN_Cmn_Med_SpineCAD", nullptr));
        Btn_ShowDlg_DbgImg->setText(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "Btn_ShowDlg_DbgImg", nullptr));
        Btn_ShowDlg_Main->setText(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "Btn_ShowDlg_Main", nullptr));
        Btn_ShowDlg_DbgImg_Slc->setText(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "Btn_ShowDlg_DbgImg_Slc", nullptr));
        Btn_TestVTK->setText(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "TestVTK", nullptr));
        Btn_TestITK->setText(QApplication::translate("SPN_Cmn_Med_SpineCADClass", "TestITK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SPN_Cmn_Med_SpineCADClass: public Ui_SPN_Cmn_Med_SpineCADClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPN_CMN_MED_SPINECAD_H
