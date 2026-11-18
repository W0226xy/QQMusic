#ifndef ONLINEMUSICSERVICE_H
#define ONLINEMUSICSERVICE_H

#include "onlinetrack.h"

#include <QNetworkAccessManager>//发送网络请求，例如请求在线歌曲接口。
#include <QObject>//Qt 对象体系的基类，支持信号与槽
#include <QPointer>//一种安全指针，所指向的 Qt 对象被销毁后会自动变成 nullptr
#include <QTimer>//定时器，这里通常用于网络请求超时控制

class QNetworkReply;

class OnlineMusicService : public QObject
{
    Q_OBJECT
public:
    explicit OnlineMusicService(QObject *parent = nullptr);//parent 是 Qt 的对象树父对象，如果传入父对象，父对象销毁时会自动销毁这个服务对象

    bool isLoading() const;//当前是否正在请求网络歌曲
    void fetchTracks(int limit = 12, int offset = -1);//请求在线歌曲，默认一次请求12首歌，offset = -1：通常表示“不指定偏移量”，由函数内部决定随机位置或默认位置

signals:
    void tracksReady(const QList<OnlineTrack> &tracks);//歌曲请求成功后发出，并携带歌曲列表
    void requestFailed(const QString &message);//请求失败时发出，例如网络异常、接口返回错误、超时
    void loadingChanged(bool loading);//加载状态变化时发出

private:
    void finishRequest();

    QNetworkAccessManager manager;
    QPointer<QNetworkReply> activeReply;
    QTimer timeoutTimer;
    quint64 requestSerial = 0;
    bool loading = false;
};

#endif // ONLINEMUSICSERVICE_H
