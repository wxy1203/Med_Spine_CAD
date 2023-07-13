#ifndef __include__QT_H__
#define __include__QT_H__

#pragma once

#include <qglobal.h>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#else
#include <QtGUI\QtGui>
#include <QtCore\QtCore>
#include "qglobal.h"
#include "QMutex.h"
#include "QMessageBox.h"
#include "qfile.h"
#include "qfileInfo.h"
#include <QPoint>
#include <QRect>
#endif // 

#endif //  // __include__QT_H__

