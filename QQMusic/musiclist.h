#ifndef MUSICLIST_H
#define MUSICLIST_H
#include<QVector>
#include"music.h"
#include<QUrl>
#include<QList>
#include<QSet>
typedef  QVector<Music>::iterator iterator;
//管理所有歌曲对应的music对象
class MusicList
{
public:
    MusicList();
    void addMusicsByUrl(const QList<QUrl>& musicUrls);

    iterator findMusicByMusicId(const QString& musicId);
    iterator begin();
    iterator end();
    void writeToMusicDB();
    void readFromDB();
private:
    QVector<Music> musicList;
    QSet<QString> musicPaths;
};

#endif // MUSICLIST_H
