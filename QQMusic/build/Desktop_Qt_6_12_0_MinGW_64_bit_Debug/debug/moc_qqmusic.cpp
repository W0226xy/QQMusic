/****************************************************************************
** Meta object code from reading C++ file 'qqmusic.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qqmusic.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qqmusic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN7QQMusicE_t {};
} // unnamed namespace

template <> constexpr inline auto QQMusic::qt_create_metaobjectdata<qt_meta_tag_ZN7QQMusicE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QQMusic",
        "on_quit_clicked",
        "",
        "onBtFormClick",
        "pageId",
        "on_volume_clicked",
        "on_addLocal_clicked",
        "UpdateLikeMusicAndPage",
        "isLike",
        "musicId",
        "onPlayMusic",
        "onPlayerStateChanged",
        "onCurrentIndexChanged",
        "index",
        "onPlayDownClicked",
        "onPlayUpClicked",
        "onPlaybackModelClicked",
        "onPlayAll",
        "PageType",
        "pageType",
        "playAllMusicOfCommonPage",
        "CommonPage*",
        "page",
        "playMusicByIndex",
        "setPlayerMuted",
        "isMuted",
        "setPlayerVolume",
        "volume",
        "onDurationChanged",
        "duration",
        "onPositionChanged",
        "position",
        "onMusicSliderChanged",
        "ration",
        "onMetaDataChanged",
        "onLrcWordClicked",
        "on_min_clicked",
        "on_max_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_quit_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBtFormClick'
        QtMocHelpers::SlotData<void(int)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Slot 'on_volume_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_addLocal_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'UpdateLikeMusicAndPage'
        QtMocHelpers::SlotData<void(bool, const QString &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'onPlayMusic'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPlayerStateChanged'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCurrentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'onPlayDownClicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPlayUpClicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPlaybackModelClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPlayAll'
        QtMocHelpers::SlotData<void(PageType)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'playAllMusicOfCommonPage'
        QtMocHelpers::SlotData<void(CommonPage *, int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 21, 22 }, { QMetaType::Int, 13 },
        }}),
        // Slot 'playMusicByIndex'
        QtMocHelpers::SlotData<void(CommonPage *, int)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 21, 22 }, { QMetaType::Int, 13 },
        }}),
        // Slot 'setPlayerMuted'
        QtMocHelpers::SlotData<void(bool)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
        // Slot 'setPlayerVolume'
        QtMocHelpers::SlotData<void(int)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 27 },
        }}),
        // Slot 'onDurationChanged'
        QtMocHelpers::SlotData<void(qint64)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 29 },
        }}),
        // Slot 'onPositionChanged'
        QtMocHelpers::SlotData<void(qint64)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 31 },
        }}),
        // Slot 'onMusicSliderChanged'
        QtMocHelpers::SlotData<void(float)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Float, 33 },
        }}),
        // Slot 'onMetaDataChanged'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLrcWordClicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_min_clicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_max_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QQMusic, qt_meta_tag_ZN7QQMusicE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QQMusic::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QQMusicE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QQMusicE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7QQMusicE_t>.metaTypes,
    nullptr
} };

void QQMusic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QQMusic *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_quit_clicked(); break;
        case 1: _t->onBtFormClick((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->on_volume_clicked(); break;
        case 3: _t->on_addLocal_clicked(); break;
        case 4: _t->UpdateLikeMusicAndPage((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->onPlayMusic(); break;
        case 6: _t->onPlayerStateChanged(); break;
        case 7: _t->onCurrentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->onPlayDownClicked(); break;
        case 9: _t->onPlayUpClicked(); break;
        case 10: _t->onPlaybackModelClicked(); break;
        case 11: _t->onPlayAll((*reinterpret_cast<std::add_pointer_t<PageType>>(_a[1]))); break;
        case 12: _t->playAllMusicOfCommonPage((*reinterpret_cast<std::add_pointer_t<CommonPage*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->playMusicByIndex((*reinterpret_cast<std::add_pointer_t<CommonPage*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 14: _t->setPlayerMuted((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->setPlayerVolume((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->onDurationChanged((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 17: _t->onPositionChanged((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 18: _t->onMusicSliderChanged((*reinterpret_cast<std::add_pointer_t<float>>(_a[1]))); break;
        case 19: _t->onMetaDataChanged(); break;
        case 20: _t->onLrcWordClicked(); break;
        case 21: _t->on_min_clicked(); break;
        case 22: _t->on_max_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CommonPage* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CommonPage* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *QQMusic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QQMusic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QQMusicE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QQMusic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
