/****************************************************************************
** Meta object code from reading C++ file 'tabofhosts.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HostChange/tabofhosts.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabofhosts.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TabOfHosts_t {
    QByteArrayData data[8];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TabOfHosts_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TabOfHosts_t qt_meta_stringdata_TabOfHosts = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TabOfHosts"
QT_MOC_LITERAL(1, 11, 15), // "setCurrentHosts"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "changedHostTab"
QT_MOC_LITERAL(4, 43, 14), // "patternChanged"
QT_MOC_LITERAL(5, 58, 22), // "patternCheckboxChanged"
QT_MOC_LITERAL(6, 81, 1), // "i"
QT_MOC_LITERAL(7, 83, 19) // "variableDataChanged"

    },
    "TabOfHosts\0setCurrentHosts\0\0changedHostTab\0"
    "patternChanged\0patternCheckboxChanged\0"
    "i\0variableDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabOfHosts[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void TabOfHosts::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabOfHosts *_t = static_cast<TabOfHosts *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCurrentHosts(); break;
        case 1: _t->changedHostTab(); break;
        case 2: _t->patternChanged(); break;
        case 3: _t->patternCheckboxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->variableDataChanged(); break;
        default: ;
        }
    }
}

const QMetaObject TabOfHosts::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TabOfHosts.data,
      qt_meta_data_TabOfHosts,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TabOfHosts::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabOfHosts::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TabOfHosts.stringdata0))
        return static_cast<void*>(const_cast< TabOfHosts*>(this));
    return QObject::qt_metacast(_clname);
}

int TabOfHosts::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
