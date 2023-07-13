/****************************************************************************
** Meta object code from reading C++ file 'SPN_Cmn_Dlg_Main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SPN_Cmn_Dlg_Main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SPN_Cmn_Dlg_Main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SPN_Cmn_Dlg_Main_t {
    QByteArrayData data[19];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SPN_Cmn_Dlg_Main_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SPN_Cmn_Dlg_Main_t qt_meta_stringdata_SPN_Cmn_Dlg_Main = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SPN_Cmn_Dlg_Main"
QT_MOC_LITERAL(1, 17, 12), // "ImgTp_SelChg"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "iSel_Tp"
QT_MOC_LITERAL(4, 39, 11), // "resizeEvent"
QT_MOC_LITERAL(5, 51, 13), // "QResizeEvent*"
QT_MOC_LITERAL(6, 65, 14), // "On_Slash_YesNo"
QT_MOC_LITERAL(7, 80, 4), // "nBgn"
QT_MOC_LITERAL(8, 85, 15), // "ShowImg2D_Mn_Ax"
QT_MOC_LITERAL(9, 101, 8), // "S_Img2D*"
QT_MOC_LITERAL(10, 110, 7), // "pImgSum"
QT_MOC_LITERAL(11, 118, 7), // "kSlcImg"
QT_MOC_LITERAL(12, 126, 15), // "ShowImg2D_Mn_Co"
QT_MOC_LITERAL(13, 142, 7), // "jSlcImg"
QT_MOC_LITERAL(14, 150, 15), // "ShowImg2D_Mn_Sa"
QT_MOC_LITERAL(15, 166, 7), // "iSlcImg"
QT_MOC_LITERAL(16, 174, 18), // "ShowImg2D_Mn_Slash"
QT_MOC_LITERAL(17, 193, 17), // "on_RadGrp_Clicked"
QT_MOC_LITERAL(18, 211, 4) // "iSel"

    },
    "SPN_Cmn_Dlg_Main\0ImgTp_SelChg\0\0iSel_Tp\0"
    "resizeEvent\0QResizeEvent*\0On_Slash_YesNo\0"
    "nBgn\0ShowImg2D_Mn_Ax\0S_Img2D*\0pImgSum\0"
    "kSlcImg\0ShowImg2D_Mn_Co\0jSlcImg\0"
    "ShowImg2D_Mn_Sa\0iSlcImg\0ShowImg2D_Mn_Slash\0"
    "on_RadGrp_Clicked\0iSel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SPN_Cmn_Dlg_Main[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       8,    2,   63,    2, 0x0a /* Public */,
      12,    2,   68,    2, 0x0a /* Public */,
      14,    2,   73,    2, 0x0a /* Public */,
      16,    2,   78,    2, 0x0a /* Public */,
      17,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   13,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   15,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void SPN_Cmn_Dlg_Main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SPN_Cmn_Dlg_Main *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ImgTp_SelChg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 2: _t->On_Slash_YesNo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->ShowImg2D_Mn_Ax((*reinterpret_cast< S_Img2D*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->ShowImg2D_Mn_Co((*reinterpret_cast< S_Img2D*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->ShowImg2D_Mn_Sa((*reinterpret_cast< S_Img2D*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->ShowImg2D_Mn_Slash((*reinterpret_cast< S_Img2D*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_RadGrp_Clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SPN_Cmn_Dlg_Main::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPN_Cmn_Dlg_Main::ImgTp_SelChg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SPN_Cmn_Dlg_Main::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SPN_Cmn_Dlg_Main.data,
    qt_meta_data_SPN_Cmn_Dlg_Main,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SPN_Cmn_Dlg_Main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SPN_Cmn_Dlg_Main::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SPN_Cmn_Dlg_Main.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SPN_Cmn_Dlg_Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SPN_Cmn_Dlg_Main::ImgTp_SelChg(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
