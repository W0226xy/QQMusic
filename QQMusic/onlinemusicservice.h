#ifndef ONLINEMUSICSERVICE_H
#define ONLINEMUSICSERVICE_H

#include "onlinetrack.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QPointer>
#include <QTimer>

class QNetworkReply;

class OnlineMusicService : public QObject
{
    Q_OBJECT
public:
    explicit OnlineMusicService(QObject *parent = nullptr);

    bool isLoading() const;
    void fetchTracks(int limit = 12, int offset = -1);

signals:
    void tracksReady(const QList<OnlineTrack> &tracks);
    void requestFailed(const QString &message);
    void loadingChanged(bool loading);

private:
    void finishRequest();

    QNetworkAccessManager manager;
    QPointer<QNetworkReply> activeReply;
    QTimer timeoutTimer;
    quint64 requestSerial = 0;
    bool loading = false;
};

#endif // ONLINEMUSICSERVICE_H
