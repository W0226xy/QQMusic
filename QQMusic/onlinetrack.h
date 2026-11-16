#ifndef ONLINETRACK_H
#define ONLINETRACK_H

#include <QMetaType>
#include <QString>
#include <QUrl>
#include <QList>

struct OnlineTrack
{
    QString id;
    QString name;
    QString artist;
    QString album;
    QUrl audioUrl;
    QUrl coverUrl;
    qint64 duration = 0;
};

Q_DECLARE_METATYPE(OnlineTrack)
Q_DECLARE_METATYPE(QList<OnlineTrack>)

#endif // ONLINETRACK_H
