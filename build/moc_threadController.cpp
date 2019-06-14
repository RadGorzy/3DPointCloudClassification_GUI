/****************************************************************************
** Meta object code from reading C++ file 'threadController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../threadController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[30];
    char stringdata0[484];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 11), // "resultReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "result"
QT_MOC_LITERAL(4, 27, 8), // "classify"
QT_MOC_LITERAL(5, 36, 24), // "cloudControllerSharedPtr"
QT_MOC_LITERAL(6, 61, 15), // "modelController"
QT_MOC_LITERAL(7, 77, 26), // "listOfTreeWidgetItemRawPtr"
QT_MOC_LITERAL(8, 104, 14), // "selectedClouds"
QT_MOC_LITERAL(9, 119, 27), // "classificationTypeSharedPtr"
QT_MOC_LITERAL(10, 147, 18), // "classificationType"
QT_MOC_LITERAL(11, 166, 25), // "segmentationTypeSharedPtr"
QT_MOC_LITERAL(12, 192, 16), // "segmentationType"
QT_MOC_LITERAL(13, 209, 23), // "projectionTypeSharedPtr"
QT_MOC_LITERAL(14, 233, 14), // "projectionType"
QT_MOC_LITERAL(15, 248, 17), // "editTypeSharedPtr"
QT_MOC_LITERAL(16, 266, 8), // "editType"
QT_MOC_LITERAL(17, 275, 9), // "stdString"
QT_MOC_LITERAL(18, 285, 9), // "modelPath"
QT_MOC_LITERAL(19, 295, 7), // "integer"
QT_MOC_LITERAL(20, 303, 12), // "numOfClasses"
QT_MOC_LITERAL(21, 316, 9), // "benchmark"
QT_MOC_LITERAL(22, 326, 22), // "benchmarkTypeSharedPtr"
QT_MOC_LITERAL(23, 349, 13), // "benchmarkType"
QT_MOC_LITERAL(24, 363, 10), // "folderPath"
QT_MOC_LITERAL(25, 374, 13), // "prepareFrom3D"
QT_MOC_LITERAL(26, 388, 33), // "prepareDatasetControllerShare..."
QT_MOC_LITERAL(27, 422, 10), // "controller"
QT_MOC_LITERAL(28, 433, 29), // "prepareDatasetFrom3DSharedPtr"
QT_MOC_LITERAL(29, 463, 20) // "prepareDatasetFrom3D"

    },
    "Worker\0resultReady\0\0result\0classify\0"
    "cloudControllerSharedPtr\0modelController\0"
    "listOfTreeWidgetItemRawPtr\0selectedClouds\0"
    "classificationTypeSharedPtr\0"
    "classificationType\0segmentationTypeSharedPtr\0"
    "segmentationType\0projectionTypeSharedPtr\0"
    "projectionType\0editTypeSharedPtr\0"
    "editType\0stdString\0modelPath\0integer\0"
    "numOfClasses\0benchmark\0benchmarkTypeSharedPtr\0"
    "benchmarkType\0folderPath\0prepareFrom3D\0"
    "prepareDatasetControllerSharedPtr\0"
    "controller\0prepareDatasetFrom3DSharedPtr\0"
    "prepareDatasetFrom3D"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    8,   37,    2, 0x0a /* Public */,
      21,    4,   54,    2, 0x0a /* Public */,
      25,    2,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17, 0x80000000 | 19,    6,    8,   10,   12,   14,   16,   18,   20,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 22, 0x80000000 | 17,    6,    8,   23,   24,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28,   27,   29,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->classify((*reinterpret_cast< const cloudControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< listOfTreeWidgetItemRawPtr(*)>(_a[2])),(*reinterpret_cast< classificationTypeSharedPtr(*)>(_a[3])),(*reinterpret_cast< segmentationTypeSharedPtr(*)>(_a[4])),(*reinterpret_cast< projectionTypeSharedPtr(*)>(_a[5])),(*reinterpret_cast< editTypeSharedPtr(*)>(_a[6])),(*reinterpret_cast< stdString(*)>(_a[7])),(*reinterpret_cast< integer(*)>(_a[8]))); break;
        case 2: _t->benchmark((*reinterpret_cast< const cloudControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< listOfTreeWidgetItemRawPtr(*)>(_a[2])),(*reinterpret_cast< benchmarkTypeSharedPtr(*)>(_a[3])),(*reinterpret_cast< stdString(*)>(_a[4]))); break;
        case 3: _t->prepareFrom3D((*reinterpret_cast< const prepareDatasetControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< prepareDatasetFrom3DSharedPtr(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< classificationTypeSharedPtr >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< cloudControllerSharedPtr >(); break;
            case 5:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< editTypeSharedPtr >(); break;
            case 7:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< integer >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< listOfTreeWidgetItemRawPtr >(); break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< projectionTypeSharedPtr >(); break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< segmentationTypeSharedPtr >(); break;
            case 6:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stdString >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< benchmarkTypeSharedPtr >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< cloudControllerSharedPtr >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< listOfTreeWidgetItemRawPtr >(); break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stdString >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< prepareDatasetControllerSharedPtr >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< prepareDatasetFrom3DSharedPtr >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Worker.data,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Worker::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ThreadController_t {
    QByteArrayData data[30];
    char stringdata0[496];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadController_t qt_meta_stringdata_ThreadController = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ThreadController"
QT_MOC_LITERAL(1, 17, 8), // "classify"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 24), // "cloudControllerSharedPtr"
QT_MOC_LITERAL(4, 52, 15), // "modelController"
QT_MOC_LITERAL(5, 68, 26), // "listOfTreeWidgetItemRawPtr"
QT_MOC_LITERAL(6, 95, 14), // "selectedClouds"
QT_MOC_LITERAL(7, 110, 27), // "classificationTypeSharedPtr"
QT_MOC_LITERAL(8, 138, 18), // "classificationType"
QT_MOC_LITERAL(9, 157, 25), // "segmentationTypeSharedPtr"
QT_MOC_LITERAL(10, 183, 16), // "segmentationType"
QT_MOC_LITERAL(11, 200, 23), // "projectionTypeSharedPtr"
QT_MOC_LITERAL(12, 224, 14), // "projectionType"
QT_MOC_LITERAL(13, 239, 17), // "editTypeSharedPtr"
QT_MOC_LITERAL(14, 257, 8), // "editType"
QT_MOC_LITERAL(15, 266, 9), // "stdString"
QT_MOC_LITERAL(16, 276, 9), // "modelPath"
QT_MOC_LITERAL(17, 286, 7), // "integer"
QT_MOC_LITERAL(18, 294, 12), // "numOfClasses"
QT_MOC_LITERAL(19, 307, 9), // "benchmark"
QT_MOC_LITERAL(20, 317, 22), // "benchmarkTypeSharedPtr"
QT_MOC_LITERAL(21, 340, 13), // "benchmarkType"
QT_MOC_LITERAL(22, 354, 10), // "folderPath"
QT_MOC_LITERAL(23, 365, 13), // "prepareFrom3D"
QT_MOC_LITERAL(24, 379, 33), // "prepareDatasetControllerShare..."
QT_MOC_LITERAL(25, 413, 10), // "controller"
QT_MOC_LITERAL(26, 424, 29), // "prepareDatasetFrom3DSharedPtr"
QT_MOC_LITERAL(27, 454, 20), // "prepareDatasetFrom3D"
QT_MOC_LITERAL(28, 475, 13), // "handleResults"
QT_MOC_LITERAL(29, 489, 6) // "result"

    },
    "ThreadController\0classify\0\0"
    "cloudControllerSharedPtr\0modelController\0"
    "listOfTreeWidgetItemRawPtr\0selectedClouds\0"
    "classificationTypeSharedPtr\0"
    "classificationType\0segmentationTypeSharedPtr\0"
    "segmentationType\0projectionTypeSharedPtr\0"
    "projectionType\0editTypeSharedPtr\0"
    "editType\0stdString\0modelPath\0integer\0"
    "numOfClasses\0benchmark\0benchmarkTypeSharedPtr\0"
    "benchmarkType\0folderPath\0prepareFrom3D\0"
    "prepareDatasetControllerSharedPtr\0"
    "controller\0prepareDatasetFrom3DSharedPtr\0"
    "prepareDatasetFrom3D\0handleResults\0"
    "result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    8,   34,    2, 0x06 /* Public */,
      19,    4,   51,    2, 0x06 /* Public */,
      23,    2,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17,    4,    6,    8,   10,   12,   14,   16,   18,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 20, 0x80000000 | 15,    4,    6,   21,   22,
    QMetaType::Void, 0x80000000 | 24, 0x80000000 | 26,   25,   27,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   29,

       0        // eod
};

void ThreadController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->classify((*reinterpret_cast< const cloudControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< listOfTreeWidgetItemRawPtr(*)>(_a[2])),(*reinterpret_cast< classificationTypeSharedPtr(*)>(_a[3])),(*reinterpret_cast< segmentationTypeSharedPtr(*)>(_a[4])),(*reinterpret_cast< projectionTypeSharedPtr(*)>(_a[5])),(*reinterpret_cast< editTypeSharedPtr(*)>(_a[6])),(*reinterpret_cast< stdString(*)>(_a[7])),(*reinterpret_cast< integer(*)>(_a[8]))); break;
        case 1: _t->benchmark((*reinterpret_cast< const cloudControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< listOfTreeWidgetItemRawPtr(*)>(_a[2])),(*reinterpret_cast< benchmarkTypeSharedPtr(*)>(_a[3])),(*reinterpret_cast< stdString(*)>(_a[4]))); break;
        case 2: _t->prepareFrom3D((*reinterpret_cast< const prepareDatasetControllerSharedPtr(*)>(_a[1])),(*reinterpret_cast< prepareDatasetFrom3DSharedPtr(*)>(_a[2]))); break;
        case 3: _t->handleResults((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< classificationTypeSharedPtr >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< cloudControllerSharedPtr >(); break;
            case 5:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< editTypeSharedPtr >(); break;
            case 7:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< integer >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< listOfTreeWidgetItemRawPtr >(); break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< projectionTypeSharedPtr >(); break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< segmentationTypeSharedPtr >(); break;
            case 6:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stdString >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< benchmarkTypeSharedPtr >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< cloudControllerSharedPtr >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< listOfTreeWidgetItemRawPtr >(); break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stdString >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< prepareDatasetControllerSharedPtr >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< prepareDatasetFrom3DSharedPtr >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadController::*)(const cloudControllerSharedPtr , listOfTreeWidgetItemRawPtr , classificationTypeSharedPtr , segmentationTypeSharedPtr , projectionTypeSharedPtr , editTypeSharedPtr , stdString , integer );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadController::classify)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadController::*)(const cloudControllerSharedPtr , listOfTreeWidgetItemRawPtr , benchmarkTypeSharedPtr , stdString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadController::benchmark)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ThreadController::*)(const prepareDatasetControllerSharedPtr , prepareDatasetFrom3DSharedPtr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadController::prepareFrom3D)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ThreadController.data,
    qt_meta_data_ThreadController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThreadController::classify(const cloudControllerSharedPtr _t1, listOfTreeWidgetItemRawPtr _t2, classificationTypeSharedPtr _t3, segmentationTypeSharedPtr _t4, projectionTypeSharedPtr _t5, editTypeSharedPtr _t6, stdString _t7, integer _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadController::benchmark(const cloudControllerSharedPtr _t1, listOfTreeWidgetItemRawPtr _t2, benchmarkTypeSharedPtr _t3, stdString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ThreadController::prepareFrom3D(const prepareDatasetControllerSharedPtr _t1, prepareDatasetFrom3DSharedPtr _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
