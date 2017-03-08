/****************************************************************************
** Meta object code from reading C++ file 'auxcamgraphicsview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "auxcamgraphicsview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auxcamgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_auxcamgraphicsview_t {
    QByteArrayData data[14];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_auxcamgraphicsview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_auxcamgraphicsview_t qt_meta_stringdata_auxcamgraphicsview = {
    {
QT_MOC_LITERAL(0, 0, 18), // "auxcamgraphicsview"
QT_MOC_LITERAL(1, 19, 19), // "sendMouseClickEvent"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "string&"
QT_MOC_LITERAL(4, 48, 3), // "clk"
QT_MOC_LITERAL(5, 52, 12), // "vector<int>&"
QT_MOC_LITERAL(6, 65, 4), // "data"
QT_MOC_LITERAL(7, 70, 17), // "sendMouseMoveData"
QT_MOC_LITERAL(8, 88, 21), // "sendMouseReleaseEvent"
QT_MOC_LITERAL(9, 110, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(10, 125, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 138, 1), // "e"
QT_MOC_LITERAL(12, 140, 15), // "mousePressEvent"
QT_MOC_LITERAL(13, 156, 17) // "mouseReleaseEvent"

    },
    "auxcamgraphicsview\0sendMouseClickEvent\0"
    "\0string&\0clk\0vector<int>&\0data\0"
    "sendMouseMoveData\0sendMouseReleaseEvent\0"
    "mouseMoveEvent\0QMouseEvent*\0e\0"
    "mousePressEvent\0mouseReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_auxcamgraphicsview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       7,    1,   49,    2, 0x06 /* Public */,
       8,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   55,    2, 0x0a /* Public */,
      12,    1,   58,    2, 0x0a /* Public */,
      13,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void auxcamgraphicsview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auxcamgraphicsview *_t = static_cast<auxcamgraphicsview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMouseClickEvent((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2]))); break;
        case 1: _t->sendMouseMoveData((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 2: _t->sendMouseReleaseEvent((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 3: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (auxcamgraphicsview::*_t)(string & , vector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auxcamgraphicsview::sendMouseClickEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (auxcamgraphicsview::*_t)(vector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auxcamgraphicsview::sendMouseMoveData)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (auxcamgraphicsview::*_t)(vector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auxcamgraphicsview::sendMouseReleaseEvent)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject auxcamgraphicsview::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_auxcamgraphicsview.data,
      qt_meta_data_auxcamgraphicsview,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *auxcamgraphicsview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *auxcamgraphicsview::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_auxcamgraphicsview.stringdata0))
        return static_cast<void*>(const_cast< auxcamgraphicsview*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int auxcamgraphicsview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
void auxcamgraphicsview::sendMouseClickEvent(string & _t1, vector<int> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void auxcamgraphicsview::sendMouseMoveData(vector<int> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void auxcamgraphicsview::sendMouseReleaseEvent(vector<int> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
