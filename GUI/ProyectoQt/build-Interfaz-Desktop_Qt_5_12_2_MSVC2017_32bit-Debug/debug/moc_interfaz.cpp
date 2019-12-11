/****************************************************************************
** Meta object code from reading C++ file 'interfaz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interfaz/interfaz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Interfaz_t {
    QByteArrayData data[21];
    char stringdata0[378];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Interfaz_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Interfaz_t qt_meta_stringdata_Interfaz = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Interfaz"
QT_MOC_LITERAL(1, 9, 17), // "on_noseup_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "on_noseright_clicked"
QT_MOC_LITERAL(4, 49, 19), // "on_nosedown_clicked"
QT_MOC_LITERAL(5, 69, 19), // "on_noseleft_clicked"
QT_MOC_LITERAL(6, 89, 16), // "on_modo1_clicked"
QT_MOC_LITERAL(7, 106, 16), // "on_modo2_clicked"
QT_MOC_LITERAL(8, 123, 19), // "on_calibrar_clicked"
QT_MOC_LITERAL(9, 143, 25), // "on_pitch1_editingFinished"
QT_MOC_LITERAL(10, 169, 24), // "on_roll2_editingFinished"
QT_MOC_LITERAL(11, 194, 29), // "on_pushButtonConectar_clicked"
QT_MOC_LITERAL(12, 224, 35), // "on_comboBoxPort_currentIndexC..."
QT_MOC_LITERAL(13, 260, 5), // "index"
QT_MOC_LITERAL(14, 266, 20), // "on_btnUpdate_clicked"
QT_MOC_LITERAL(15, 287, 10), // "Recibiendo"
QT_MOC_LITERAL(16, 298, 20), // "on_btnEnviar_clicked"
QT_MOC_LITERAL(17, 319, 19), // "on_yaw_valueChanged"
QT_MOC_LITERAL(18, 339, 4), // "arg1"
QT_MOC_LITERAL(19, 344, 18), // "on_btnPlot_clicked"
QT_MOC_LITERAL(20, 363, 14) // "verificarTrama"

    },
    "Interfaz\0on_noseup_clicked\0\0"
    "on_noseright_clicked\0on_nosedown_clicked\0"
    "on_noseleft_clicked\0on_modo1_clicked\0"
    "on_modo2_clicked\0on_calibrar_clicked\0"
    "on_pitch1_editingFinished\0"
    "on_roll2_editingFinished\0"
    "on_pushButtonConectar_clicked\0"
    "on_comboBoxPort_currentIndexChanged\0"
    "index\0on_btnUpdate_clicked\0Recibiendo\0"
    "on_btnEnviar_clicked\0on_yaw_valueChanged\0"
    "arg1\0on_btnPlot_clicked\0verificarTrama"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Interfaz[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    1,  109,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    1,  115,    2, 0x08 /* Private */,
      19,    0,  118,    2, 0x08 /* Private */,
      20,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Interfaz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Interfaz *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_noseup_clicked(); break;
        case 1: _t->on_noseright_clicked(); break;
        case 2: _t->on_nosedown_clicked(); break;
        case 3: _t->on_noseleft_clicked(); break;
        case 4: _t->on_modo1_clicked(); break;
        case 5: _t->on_modo2_clicked(); break;
        case 6: _t->on_calibrar_clicked(); break;
        case 7: _t->on_pitch1_editingFinished(); break;
        case 8: _t->on_roll2_editingFinished(); break;
        case 9: _t->on_pushButtonConectar_clicked(); break;
        case 10: _t->on_comboBoxPort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_btnUpdate_clicked(); break;
        case 12: _t->Recibiendo(); break;
        case 13: _t->on_btnEnviar_clicked(); break;
        case 14: _t->on_yaw_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_btnPlot_clicked(); break;
        case 16: _t->verificarTrama(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Interfaz::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Interfaz.data,
    qt_meta_data_Interfaz,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Interfaz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interfaz::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Interfaz.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Interfaz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
