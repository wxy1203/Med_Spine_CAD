/****************************************************************************
** Meta object code from reading C++ file 'SPN_Cmn_DlgPane_ShowPic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SPN_Cmn_DlgPane_ShowPic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SPN_Cmn_DlgPane_ShowPic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic_t {
    QByteArrayData data[19];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic_t qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic = {
    {
QT_MOC_LITERAL(0, 0, 23), // "SPN_Cmn_DlgPane_ShowPic"
QT_MOC_LITERAL(1, 24, 13), // "snNewFoc_XY_L"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "iS_0X1Y2Z"
QT_MOC_LITERAL(4, 49, 6), // "P2FocL"
QT_MOC_LITERAL(5, 56, 24), // "SSPN_Cmn_3DPoint<float>&"
QT_MOC_LITERAL(6, 81, 5), // "sP3_G"
QT_MOC_LITERAL(7, 87, 9), // "iSelImgTp"
QT_MOC_LITERAL(8, 97, 10), // "snSlashChg"
QT_MOC_LITERAL(9, 108, 11), // "iPnSlashing"
QT_MOC_LITERAL(10, 120, 23), // "SSPN_Cmn_3DPoint<float>"
QT_MOC_LITERAL(11, 144, 4), // "P3G1"
QT_MOC_LITERAL(12, 149, 4), // "P3G2"
QT_MOC_LITERAL(13, 154, 7), // "snWLChg"
QT_MOC_LITERAL(14, 162, 2), // "nW"
QT_MOC_LITERAL(15, 165, 2), // "iL"
QT_MOC_LITERAL(16, 168, 14), // "OnNewFoc_XYZ_G"
QT_MOC_LITERAL(17, 183, 16), // "iS_0X1Y2Z_ChgSrc"
QT_MOC_LITERAL(18, 200, 7) // "OnWLChg"

    },
    "SPN_Cmn_DlgPane_ShowPic\0snNewFoc_XY_L\0"
    "\0iS_0X1Y2Z\0P2FocL\0SSPN_Cmn_3DPoint<float>&\0"
    "sP3_G\0iSelImgTp\0snSlashChg\0iPnSlashing\0"
    "SSPN_Cmn_3DPoint<float>\0P3G1\0P3G2\0"
    "snWLChg\0nW\0iL\0OnNewFoc_XYZ_G\0"
    "iS_0X1Y2Z_ChgSrc\0OnWLChg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SPN_Cmn_DlgPane_ShowPic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   39,    2, 0x06 /* Public */,
       8,    3,   48,    2, 0x06 /* Public */,
      13,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    2,   60,    2, 0x0a /* Public */,
      18,    2,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF, 0x80000000 | 5, QMetaType::Int,    3,    4,    6,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 10,    9,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

       0        // eod
};

void SPN_Cmn_DlgPane_ShowPic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SPN_Cmn_DlgPane_ShowPic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->snNewFoc_XY_L((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2])),(*reinterpret_cast< SSPN_Cmn_3DPoint<float>(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->snSlashChg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const SSPN_Cmn_3DPoint<float>(*)>(_a[2])),(*reinterpret_cast< const SSPN_Cmn_3DPoint<float>(*)>(_a[3]))); break;
        case 2: _t->snWLChg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->OnNewFoc_XYZ_G((*reinterpret_cast< SSPN_Cmn_3DPoint<float>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->OnWLChg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SPN_Cmn_DlgPane_ShowPic::*)(int , QPointF , SSPN_Cmn_3DPoint<float> & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPN_Cmn_DlgPane_ShowPic::snNewFoc_XY_L)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SPN_Cmn_DlgPane_ShowPic::*)(int , const SSPN_Cmn_3DPoint<float> & , const SSPN_Cmn_3DPoint<float> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPN_Cmn_DlgPane_ShowPic::snSlashChg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SPN_Cmn_DlgPane_ShowPic::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPN_Cmn_DlgPane_ShowPic::snWLChg)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SPN_Cmn_DlgPane_ShowPic::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic.data,
    qt_meta_data_SPN_Cmn_DlgPane_ShowPic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SPN_Cmn_DlgPane_ShowPic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SPN_Cmn_DlgPane_ShowPic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SPN_Cmn_DlgPane_ShowPic.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SPN_Cmn_DlgPane_ShowPic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SPN_Cmn_DlgPane_ShowPic::snNewFoc_XY_L(int _t1, QPointF _t2, SSPN_Cmn_3DPoint<float> & _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SPN_Cmn_DlgPane_ShowPic::snSlashChg(int _t1, const SSPN_Cmn_3DPoint<float> & _t2, const SSPN_Cmn_3DPoint<float> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SPN_Cmn_DlgPane_ShowPic::snWLChg(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
