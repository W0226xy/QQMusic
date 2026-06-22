#ifndef MUSIC_H
#define MUSIC_H
#include<QUrl>

class Music
{
public:
    Music();

    Music(QUrl url);

    void setMusicName(const QString& musicName);

    void setMusicSinger(const QString& musicSinger);

    void setMusicAlbum(const QString& musicAlbum);

    void setMusicDuration(qint64 duration);

    void setIsLike(bool isLike);

    void setIsHistory(bool isHistory);

    void setHistory(QUrl musicUrl);

    void setMusicId(const QString& musicID);

    void setMusicUrl(const QUrl& url);

    QString getMusicName() const;

    QString getMusicSinger() const;

    QString getMusicAlbum() const;

    qint64 getMusicDuration() const;

    bool getIsLike() const;

    bool getIsHistory() const;

    QUrl getHistory()const;

    QString getMusicId() const;

    QUrl getMusicUrl();

    QString getLrcFilePath() const;

    void InsertMusicToDB();//将歌曲属性写入数据库
private:
    void parseMediaMetaMusic();
private:
    //为了保证歌曲的唯一性，给音乐添加id
    QString musicId;
    //音乐名称
    QString musicName;
    //音乐作者
    QString musicSinger;
    //音乐专辑
    QString musicAlbumn;
    //持续时常(qt中的long long类型 4:30.56--->(4*60+30)*1000+56=270 000 +56毫秒)
    qint64 duration;
    //是否收藏/喜欢
    bool isLike;

    //是否为历史播放
    bool isHistory;
    //音乐的QUrl
    QUrl musicUrl;
};

#endif // MUSIC_H
