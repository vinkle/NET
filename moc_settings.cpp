/****************************************************************************
** Meta object code from reading C++ file 'settings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_settings_t {
    QByteArrayData data[23];
    char stringdata0[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_settings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_settings_t qt_meta_stringdata_settings = {
    {
QT_MOC_LITERAL(0, 0, 8), // "settings"
QT_MOC_LITERAL(1, 9, 16), // "makeUpdateParams"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "params"
QT_MOC_LITERAL(4, 34, 19), // "enablePushButtonSig"
QT_MOC_LITERAL(5, 54, 3), // "val"
QT_MOC_LITERAL(6, 58, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(7, 80, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(8, 102, 19), // "on_btnCalib_clicked"
QT_MOC_LITERAL(9, 122, 14), // "openSerialPort"
QT_MOC_LITERAL(10, 137, 15), // "closeSerialPort"
QT_MOC_LITERAL(11, 153, 8), // "readData"
QT_MOC_LITERAL(12, 162, 9), // "writeData"
QT_MOC_LITERAL(13, 172, 4), // "data"
QT_MOC_LITERAL(14, 177, 11), // "handleError"
QT_MOC_LITERAL(15, 189, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(16, 218, 5), // "error"
QT_MOC_LITERAL(17, 224, 20), // "enablePushButtonSlot"
QT_MOC_LITERAL(18, 245, 7), // "average"
QT_MOC_LITERAL(19, 253, 14), // "vector<double>"
QT_MOC_LITERAL(20, 268, 1), // "v"
QT_MOC_LITERAL(21, 270, 27), // "on_btnAddtoDatabase_clicked"
QT_MOC_LITERAL(22, 298, 21) // "on_pushButton_clicked"

    },
    "settings\0makeUpdateParams\0\0params\0"
    "enablePushButtonSig\0val\0on_buttonBox_accepted\0"
    "on_buttonBox_rejected\0on_btnCalib_clicked\0"
    "openSerialPort\0closeSerialPort\0readData\0"
    "writeData\0data\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "enablePushButtonSlot\0average\0"
    "vector<double>\0v\0on_btnAddtoDatabase_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_settings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   90,    2, 0x08 /* Private */,
       7,    0,   91,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      14,    1,   99,    2, 0x08 /* Private */,
      17,    1,  102,    2, 0x08 /* Private */,
      18,    1,  105,    2, 0x08 /* Private */,
      21,    0,  108,    2, 0x08 /* Private */,
      22,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Double, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        settings *_t = static_cast<settings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->makeUpdateParams((*reinterpret_cast< const params(*)>(_a[1]))); break;
        case 1: _t->enablePushButtonSig((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_buttonBox_accepted(); break;
        case 3: _t->on_buttonBox_rejected(); break;
        case 4: _t->on_btnCalib_clicked(); break;
        case 5: _t->openSerialPort(); break;
        case 6: _t->closeSerialPort(); break;
        case 7: _t->readData(); break;
        case 8: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 9: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 10: _t->enablePushButtonSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { double _r = _t->average((*reinterpret_cast< const vector<double>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 12: _t->on_btnAddtoDatabase_clicked(); break;
        case 13: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (settings::*_t)(const params & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settings::makeUpdateParams)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (settings::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settings::enablePushButtonSig)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject settings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settings.data,
      qt_meta_data_settings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *settings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_settings.stringdata0))
        return static_cast<void*>(const_cast< settings*>(this));
    return QDialog::qt_metacast(_clname);
}

int settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void settings::makeUpdateParams(const params & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void settings::enablePushButtonSig(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
