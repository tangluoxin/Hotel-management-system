/****************************************************************************
** Meta object code from reading C++ file 'roommanagemainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/roommanagemainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roommanagemainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RoomManageMainWindow_t {
    QByteArrayData data[21];
    char stringdata0[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RoomManageMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RoomManageMainWindow_t qt_meta_stringdata_RoomManageMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 20), // "RoomManageMainWindow"
QT_MOC_LITERAL(1, 21, 22), // "receivebookinformation"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 10), // "bookpeople"
QT_MOC_LITERAL(4, 56, 8), // "booktype"
QT_MOC_LITERAL(5, 65, 6), // "bookid"
QT_MOC_LITERAL(6, 72, 9), // "telephone"
QT_MOC_LITERAL(7, 82, 4), // "days"
QT_MOC_LITERAL(8, 87, 9), // "bookstate"
QT_MOC_LITERAL(9, 97, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(10, 119, 31), // "on_queryEmptyRoomButton_clicked"
QT_MOC_LITERAL(11, 151, 26), // "on_orderRoomButton_clicked"
QT_MOC_LITERAL(12, 178, 23), // "on_liveinButton_clicked"
QT_MOC_LITERAL(13, 202, 28), // "on_searchOrderButton_clicked"
QT_MOC_LITERAL(14, 231, 29), // "on_cancelupdateButton_clicked"
QT_MOC_LITERAL(15, 261, 29), // "on_deletcheckinButton_clicked"
QT_MOC_LITERAL(16, 291, 28), // "on_orderToliveButton_clicked"
QT_MOC_LITERAL(17, 320, 25), // "on_checkoutButton_clicked"
QT_MOC_LITERAL(18, 346, 28), // "on_beginupdateButton_clicked"
QT_MOC_LITERAL(19, 375, 28), // "on_checkupdateButton_clicked"
QT_MOC_LITERAL(20, 404, 29) // "on_cancelchangeButton_clicked"

    },
    "RoomManageMainWindow\0receivebookinformation\0"
    "\0bookpeople\0booktype\0bookid\0telephone\0"
    "days\0bookstate\0on_pushButton_clicked\0"
    "on_queryEmptyRoomButton_clicked\0"
    "on_orderRoomButton_clicked\0"
    "on_liveinButton_clicked\0"
    "on_searchOrderButton_clicked\0"
    "on_cancelupdateButton_clicked\0"
    "on_deletcheckinButton_clicked\0"
    "on_orderToliveButton_clicked\0"
    "on_checkoutButton_clicked\0"
    "on_beginupdateButton_clicked\0"
    "on_checkupdateButton_clicked\0"
    "on_cancelchangeButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RoomManageMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    6,   79,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,
      19,    0,  102,    2, 0x08 /* Private */,
      20,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RoomManageMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RoomManageMainWindow *_t = static_cast<RoomManageMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receivebookinformation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_queryEmptyRoomButton_clicked(); break;
        case 3: _t->on_orderRoomButton_clicked(); break;
        case 4: _t->on_liveinButton_clicked(); break;
        case 5: _t->on_searchOrderButton_clicked(); break;
        case 6: _t->on_cancelupdateButton_clicked(); break;
        case 7: _t->on_deletcheckinButton_clicked(); break;
        case 8: _t->on_orderToliveButton_clicked(); break;
        case 9: _t->on_checkoutButton_clicked(); break;
        case 10: _t->on_beginupdateButton_clicked(); break;
        case 11: _t->on_checkupdateButton_clicked(); break;
        case 12: _t->on_cancelchangeButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject RoomManageMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RoomManageMainWindow.data,
      qt_meta_data_RoomManageMainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RoomManageMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoomManageMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RoomManageMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RoomManageMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
