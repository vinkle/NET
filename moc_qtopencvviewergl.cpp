/****************************************************************************
** Meta object code from reading C++ file 'qtopencvviewergl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtopencvviewergl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtopencvviewergl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtOpencvViewerGL_t {
    QByteArrayData data[8];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtOpencvViewerGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtOpencvViewerGL_t qt_meta_stringdata_QtOpencvViewerGL = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QtOpencvViewerGL"
QT_MOC_LITERAL(1, 17, 16), // "imageSizeChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "outW"
QT_MOC_LITERAL(4, 40, 4), // "outH"
QT_MOC_LITERAL(5, 45, 9), // "showImage"
QT_MOC_LITERAL(6, 55, 7), // "cv::Mat"
QT_MOC_LITERAL(7, 63, 5) // "image"

    },
    "QtOpencvViewerGL\0imageSizeChanged\0\0"
    "outW\0outH\0showImage\0cv::Mat\0image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtOpencvViewerGL[] = {

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
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 6,    7,

       0        // eod
};

void QtOpencvViewerGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtOpencvViewerGL *_t = static_cast<QtOpencvViewerGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->imageSizeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: { bool _r = _t->showImage((*reinterpret_cast< const cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtOpencvViewerGL::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtOpencvViewerGL::imageSizeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QtOpencvViewerGL::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_QtOpencvViewerGL.data,
      qt_meta_data_QtOpencvViewerGL,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtOpencvViewerGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtOpencvViewerGL::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtOpencvViewerGL.stringdata0))
        return static_cast<void*>(const_cast< QtOpencvViewerGL*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions_2_0"))
        return static_cast< QOpenGLFunctions_2_0*>(const_cast< QtOpencvViewerGL*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int QtOpencvViewerGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
void QtOpencvViewerGL::imageSizeChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE