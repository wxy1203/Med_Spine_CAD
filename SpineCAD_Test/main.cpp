#include "pch.h"
#include "SPN_Cmn_Med_SpineCAD.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SPN_Cmn_Med_SpineCAD w;
    w.show();
    return a.exec();
}
