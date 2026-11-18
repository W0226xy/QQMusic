#ifndef ONLINETRACK_H
#define ONLINETRACK_H

#include <QMetaType>
#include <QString>
#include <QUrl>
#include <QList>

//在线歌曲数据模型 OnlineTrack
//前面的 OnlineMusicService 请求到 Jamendo 的 JSON 后，就是把每首歌整理成这个结构体，再发送给推荐页面。
struct OnlineTrack
{
    QString id;//歌曲id
    QString name;//歌曲名
    QString artist;//歌手
    QString album;//专辑
    QUrl audioUrl;//音频地址
    QUrl coverUrl;//封面地址
    qint64 duration = 0;//歌曲时长
};

//告诉qt，OnlineTrack 和 “歌曲列表 QList<OnlineTrack>” 是 Qt 可以识别和传递的自定义数据类型。
Q_DECLARE_METATYPE(OnlineTrack)
Q_DECLARE_METATYPE(QList<OnlineTrack>)

#endif // ONLINETRACK_H
