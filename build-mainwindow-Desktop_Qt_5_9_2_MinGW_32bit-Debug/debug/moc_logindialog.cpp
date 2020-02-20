/****************************************************************************
** Meta object code from reading C++ file 'logindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/logindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_loginDialog_t {
    QByteArrayData data[8];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_loginDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_loginDialog_t qt_meta_stringdata_loginDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "loginDialog"
QT_MOC_LITERAL(1, 12, 12), // "sigsendlogin"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "sigsendSig"
QT_MOC_LITERAL(4, 37, 25), // "on_exitpushButton_clicked"
QT_MOC_LITERAL(5, 63, 26), // "on_loginpushButton_clicked"
QT_MOC_LITERAL(6, 90, 26), // "on_UexitpushButton_clicked"
QT_MOC_LITERAL(7, 117, 27) // "on_UloginpushButton_clicked"

    },
    "loginDialog\0sigsendlogin\0\0sigsendSig\0"
    "on_exitpushButton_clicked\0"
    "on_loginpushButton_clicked\0"
    "on_UexitpushButton_clicked\0"
    "on_UloginpushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_loginDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   48,    2, 0x08 /* Private */,
       5,    0,   49,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void loginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        loginDialog *_t = static_cast<loginDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigsendlogin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigsendSig(); break;
        case 2: _t->on_exitpushButton_clicked(); break;
        case 3: _t->on_loginpushButton_clicked(); break;
        case 4: _t->on_UexitpushButton_clicked(); break;
        case 5: _t->on_UloginpushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (loginDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&loginDialog::sigsendlogin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (loginDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&loginDialog::sigsendSig)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject loginDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_loginDialog.data,
      qt_meta_data_loginDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *loginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *loginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_loginDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int loginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void loginDialog::sigsendlogin(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void loginDialog::sigsendSig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
