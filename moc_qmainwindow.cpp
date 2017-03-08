/****************************************************************************
** Meta object code from reading C++ file 'qmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qMainWindow_t {
    QByteArrayData data[22];
    char stringdata0[378];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qMainWindow_t qt_meta_stringdata_qMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "qMainWindow"
QT_MOC_LITERAL(1, 12, 33), // "on_actionStart_Activity_trigg..."
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 31), // "on_action_Vertical_Flip_toggled"
QT_MOC_LITERAL(4, 79, 4), // "arg1"
QT_MOC_LITERAL(5, 84, 35), // "on_action_Horizontal_Flip_tri..."
QT_MOC_LITERAL(6, 120, 7), // "checked"
QT_MOC_LITERAL(7, 128, 12), // "updateScreen"
QT_MOC_LITERAL(8, 141, 5), // "myMat"
QT_MOC_LITERAL(9, 147, 12), // "updateStatus"
QT_MOC_LITERAL(10, 160, 11), // "trackingMsg"
QT_MOC_LITERAL(11, 172, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(12, 196, 25), // "on_actionStop_2_triggered"
QT_MOC_LITERAL(13, 222, 8), // "readData"
QT_MOC_LITERAL(14, 231, 11), // "handleError"
QT_MOC_LITERAL(15, 243, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(16, 272, 5), // "error"
QT_MOC_LITERAL(17, 278, 23), // "on_actionTemp_triggered"
QT_MOC_LITERAL(18, 302, 24), // "on_actionTemp2_triggered"
QT_MOC_LITERAL(19, 327, 32), // "on_actionSwitch_Camera_triggered"
QT_MOC_LITERAL(20, 360, 14), // "LEDindexChange"
QT_MOC_LITERAL(21, 375, 2) // "id"

    },
    "qMainWindow\0on_actionStart_Activity_triggered\0"
    "\0on_action_Vertical_Flip_toggled\0arg1\0"
    "on_action_Horizontal_Flip_triggered\0"
    "checked\0updateScreen\0myMat\0updateStatus\0"
    "trackingMsg\0on_actionQuit_triggered\0"
    "on_actionStop_2_triggered\0readData\0"
    "handleError\0QSerialPort::SerialPortError\0"
    "error\0on_actionTemp_triggered\0"
    "on_actionTemp2_triggered\0"
    "on_actionSwitch_Camera_triggered\0"
    "LEDindexChange\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qMainWindow[] = {

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
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       7,    1,   86,    2, 0x08 /* Private */,
       9,    1,   89,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    1,   95,    2, 0x08 /* Private */,
      17,    0,   98,    2, 0x08 /* Private */,
      18,    0,   99,    2, 0x08 /* Private */,
      19,    0,  100,    2, 0x08 /* Private */,
      20,    1,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void qMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        qMainWindow *_t = static_cast<qMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionStart_Activity_triggered(); break;
        case 1: _t->on_action_Vertical_Flip_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_action_Horizontal_Flip_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateScreen((*reinterpret_cast< const myMat(*)>(_a[1]))); break;
        case 4: _t->updateStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_actionQuit_triggered(); break;
        case 6: _t->on_actionStop_2_triggered(); break;
        case 7: _t->readData(); break;
        case 8: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 9: _t->on_actionTemp_triggered(); break;
        case 10: _t->on_actionTemp2_triggered(); break;
        case 11: _t->on_actionSwitch_Camera_triggered(); break;
        case 12: _t->LEDindexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject qMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qMainWindow.data,
      qt_meta_data_qMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *qMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_qMainWindow.stringdata0))
        return static_cast<void*>(const_cast< qMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
