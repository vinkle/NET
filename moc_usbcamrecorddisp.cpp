/****************************************************************************
** Meta object code from reading C++ file 'usbcamrecorddisp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "usbcamrecorddisp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usbcamrecorddisp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_usbCamRecordDisp_producer_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_usbCamRecordDisp_producer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_usbCamRecordDisp_producer_t qt_meta_stringdata_usbCamRecordDisp_producer = {
    {
QT_MOC_LITERAL(0, 0, 25), // "usbCamRecordDisp_producer"
QT_MOC_LITERAL(1, 26, 8), // "finished"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "sendtoUI"
QT_MOC_LITERAL(4, 45, 5), // "myMat"
QT_MOC_LITERAL(5, 51, 7) // "process"

    },
    "usbCamRecordDisp_producer\0finished\0\0"
    "sendtoUI\0myMat\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_usbCamRecordDisp_producer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void usbCamRecordDisp_producer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        usbCamRecordDisp_producer *_t = static_cast<usbCamRecordDisp_producer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->sendtoUI((*reinterpret_cast< const myMat(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (usbCamRecordDisp_producer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&usbCamRecordDisp_producer::finished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (usbCamRecordDisp_producer::*_t)(const myMat & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&usbCamRecordDisp_producer::sendtoUI)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject usbCamRecordDisp_producer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_usbCamRecordDisp_producer.data,
      qt_meta_data_usbCamRecordDisp_producer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *usbCamRecordDisp_producer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usbCamRecordDisp_producer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_usbCamRecordDisp_producer.stringdata0))
        return static_cast<void*>(const_cast< usbCamRecordDisp_producer*>(this));
    return QObject::qt_metacast(_clname);
}

int usbCamRecordDisp_producer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void usbCamRecordDisp_producer::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void usbCamRecordDisp_producer::sendtoUI(const myMat & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_usbCamRecordDisp_consumer_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_usbCamRecordDisp_consumer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_usbCamRecordDisp_consumer_t qt_meta_stringdata_usbCamRecordDisp_consumer = {
    {
QT_MOC_LITERAL(0, 0, 25), // "usbCamRecordDisp_consumer"
QT_MOC_LITERAL(1, 26, 8), // "finished"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7) // "process"

    },
    "usbCamRecordDisp_consumer\0finished\0\0"
    "process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_usbCamRecordDisp_consumer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void usbCamRecordDisp_consumer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        usbCamRecordDisp_consumer *_t = static_cast<usbCamRecordDisp_consumer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (usbCamRecordDisp_consumer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&usbCamRecordDisp_consumer::finished)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject usbCamRecordDisp_consumer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_usbCamRecordDisp_consumer.data,
      qt_meta_data_usbCamRecordDisp_consumer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *usbCamRecordDisp_consumer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usbCamRecordDisp_consumer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_usbCamRecordDisp_consumer.stringdata0))
        return static_cast<void*>(const_cast< usbCamRecordDisp_consumer*>(this));
    return QObject::qt_metacast(_clname);
}

int usbCamRecordDisp_consumer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void usbCamRecordDisp_consumer::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
