/********************************************************************************
** Form generated from reading UI file 'SPN_Cmn_Dlg_Main.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPN_CMN_DLG_MAIN_H
#define UI_SPN_CMN_DLG_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SPN_Cmn_Dlg_Main
{
public:
    QCheckBox *Chk_DoSlash;
    QRadioButton *BtnRad_MPR;
    QRadioButton *BtnRad_DRR;
    QRadioButton *BtnRad_MaxIP;

    void setupUi(QDialog *SPN_Cmn_Dlg_Main)
    {
        if (SPN_Cmn_Dlg_Main->objectName().isEmpty())
            SPN_Cmn_Dlg_Main->setObjectName(QString::fromUtf8("SPN_Cmn_Dlg_Main"));
        SPN_Cmn_Dlg_Main->resize(570, 369);
        Chk_DoSlash = new QCheckBox(SPN_Cmn_Dlg_Main);
        Chk_DoSlash->setObjectName(QString::fromUtf8("Chk_DoSlash"));
        Chk_DoSlash->setGeometry(QRect(400, 30, 71, 16));
        BtnRad_MPR = new QRadioButton(SPN_Cmn_Dlg_Main);
        BtnRad_MPR->setObjectName(QString::fromUtf8("BtnRad_MPR"));
        BtnRad_MPR->setGeometry(QRect(400, 60, 89, 16));
        BtnRad_DRR = new QRadioButton(SPN_Cmn_Dlg_Main);
        BtnRad_DRR->setObjectName(QString::fromUtf8("BtnRad_DRR"));
        BtnRad_DRR->setGeometry(QRect(400, 90, 89, 16));
        BtnRad_MaxIP = new QRadioButton(SPN_Cmn_Dlg_Main);
        BtnRad_MaxIP->setObjectName(QString::fromUtf8("BtnRad_MaxIP"));
        BtnRad_MaxIP->setGeometry(QRect(400, 120, 89, 16));

        retranslateUi(SPN_Cmn_Dlg_Main);

        QMetaObject::connectSlotsByName(SPN_Cmn_Dlg_Main);
    } // setupUi

    void retranslateUi(QDialog *SPN_Cmn_Dlg_Main)
    {
        SPN_Cmn_Dlg_Main->setWindowTitle(QApplication::translate("SPN_Cmn_Dlg_Main", "Dlg_Main", nullptr));
        Chk_DoSlash->setText(QApplication::translate("SPN_Cmn_Dlg_Main", "DoSlash", nullptr));
        BtnRad_MPR->setText(QApplication::translate("SPN_Cmn_Dlg_Main", "MPR", nullptr));
        BtnRad_DRR->setText(QApplication::translate("SPN_Cmn_Dlg_Main", "DRR", nullptr));
        BtnRad_MaxIP->setText(QApplication::translate("SPN_Cmn_Dlg_Main", "MaxIP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SPN_Cmn_Dlg_Main: public Ui_SPN_Cmn_Dlg_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPN_CMN_DLG_MAIN_H
