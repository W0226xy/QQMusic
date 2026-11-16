#include "music.h"
#include<QUuid>
#include<QMediaPlayer>
#include<QMediaMetaData>
#include<QDebug>
#include<QEventLoop>
#include<QTimer>
#include<QSqlQuery>
#include<QSqlError>
#include<QtDebug>
#include<QFileInfo>

namespace {
bool hasBrokenText(const QString &text)
{
    return text.contains(QChar::ReplacementCharacter)
            || text.contains(QStringLiteral("???"))
            || text.contains(QChar(0x00C3))
            || text.contains(QChar(0x00C2));
}

QString repairedUtf8Text(const QString &text)
{
    if (!hasBrokenText(text))
        return text;

    const QString candidate = QString::fromUtf8(text.toLatin1());
    return hasBrokenText(candidate) ? text : candidate;
}
}
Music::Music()
    :isLike(false)
    ,isHistory(false)
{

}

Music::Music(QUrl url)
    :isLike(false)
    ,isHistory(false)
    ,musicUrl(url)
{
    //通过url，获取对应歌曲文件信息，得到元数据
    //歌曲名称、作者、所在专辑、持续时常
    musicId=QUuid::createUuid().toString();
    parseMediaMetaMusic();
}

void Music::setMusicName(const QString& musicName)
{
    this->musicName=musicName;
}

void Music::setMusicSinger(const QString& musicSinger)
{
    this->musicSinger=musicSinger;
}

void Music::setMusicAlbum(const QString& musicAlbum)
{
    this->musicAlbumn=musicAlbum;
}

void Music::setMusicDuration(qint64 duration)
{
    this->duration=duration;
}

void Music::setIsLike(bool isLike)
{
    this->isLike=isLike;
}

void Music::setIsHistory(bool isHistory)
{
    this->isHistory=isHistory;
}

void Music::setHistory(QUrl musicUrl)
{
    this->musicUrl=musicUrl;
}

void Music::setMusicId(const QString &musicID)
{
    this->musicId=musicID;
}

void Music::setMusicUrl(const QUrl &url)
{
    this->musicUrl = url;
}




QString Music::getMusicName() const
{
    return musicName;
}

QString Music::getMusicSinger() const
{
    return musicSinger;
}

QString Music::getMusicAlbum() const
{
    return musicAlbumn;
}

qint64 Music::getMusicDuration() const
{
    return duration;
}

bool Music::getIsLike() const
{
    return isLike;
}

bool Music::getIsHistory() const
{
    return isHistory;
}

QUrl Music::getHistory()const
{
    return musicUrl;
}

QString Music::getMusicId() const
{
    return musicId;
}

QUrl Music::getMusicUrl()
{
    return musicUrl;
}

QString Music::getLrcFilePath() const
{
    //D:/musics/2002年的第一场雪.mps 歌曲文件路径
    //D:/musics/2002年的第一场雪.lrc 歌词文件路径
    QString lrcPath= musicUrl.toLocalFile();
    lrcPath.replace("mp3","lrc");//把mp3后缀替换为lrc后缀
    lrcPath.replace("flac","lrc");
    lrcPath.replace("mpga","lrc");
    return lrcPath;
}

void Music::repairCorruptedMetaData()
{
    musicName = repairedUtf8Text(musicName);
    musicSinger = repairedUtf8Text(musicSinger);
    musicAlbumn = repairedUtf8Text(musicAlbumn);

    const QString baseName = QFileInfo(musicUrl.toLocalFile()).completeBaseName();
    int separator = baseName.indexOf(QStringLiteral(" - "));
    const int separatorLength = 3;
    if (separator < 0) {
        separator = baseName.lastIndexOf('-');
    }
    const int offset = baseName.mid(separator, separatorLength) == QStringLiteral(" - ")
            ? separatorLength : 1;

    if (musicName.isEmpty() || hasBrokenText(musicName)) {
        musicName = separator >= 0 ? baseName.left(separator).trimmed() : baseName.trimmed();
    }
    if (musicSinger.isEmpty() || hasBrokenText(musicSinger)) {
        musicSinger = separator >= 0
                ? baseName.mid(separator + offset).trimmed()
                : QStringLiteral("未知歌手");
    }
    if (musicAlbumn.isEmpty() || hasBrokenText(musicAlbumn)) {
        musicAlbumn = QStringLiteral("未知专辑");
    }
}

void Music::InsertMusicToDB()
{
   //1.检测music是否在数据库中存在
    QSqlQuery query;
    query.prepare("select exists(select 1 from MusicInfo where musicId=?)");
    query.addBindValue(musicId);
    if(!query.exec())
    {
        qDebug()<<"查询失败"<<query.lastError().text();
        return;
    }
    bool isExists=query.value(0).toBool();
    if(isExists)
    {
        //2.存在，不用再插入music对象，只需要将isLike和isHistory属性更新
        query.prepare("update MusicInfo set isLike=?,isHistory=? where musicId=?");
        query.addBindValue(isLike?1:0);
        query.addBindValue(isHistory?1:0);
        query.addBindValue(musicId);
        if(!query.exec())
        {
            qDebug()<<"更新失败"<<query.lastError().text();
        }
        qDebug()<<"更新music信息"<<musicName<<" "<<musicId;
    }
    else
    {
        //3.不存在，直接将music属性信息插入数据库
        query.prepare("insert into MusicInfo(musicId,musicName,musicSinger,albumName,musicUrl,duration,isLike,isHistory) values(?,?,?,?,?,?,?,?)");
        query.addBindValue(musicId);
        query.addBindValue(musicName);
        query.addBindValue(musicSinger);
        query.addBindValue(musicAlbumn);
        query.addBindValue(musicUrl.toLocalFile());
        query.addBindValue(duration);
        query.addBindValue(isLike?1:0);
        query.addBindValue(isHistory?1:0);

        if(!query.exec())
        {
            qDebug()<<"插入失败"<<query.lastError().text();
            return;
        }
        qDebug()<<"插入music信息成功"<<musicName<<" "<<musicId;
    }



}

void Music::parseMediaMetaMusic()
{
    //1.创建媒体播放对象
    QMediaPlayer player;
    // Qt 6 使用 setSource()，元数据在媒体加载完成后才可读取。
    QEventLoop eventLoop;
    QTimer timeout;
    timeout.setSingleShot(true);
    QObject::connect(&timeout, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, &eventLoop,
            [&eventLoop](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::InvalidMedia)
            eventLoop.quit();
    });
    player.setSource(musicUrl);
    timeout.start(3000);
    eventLoop.exec();

    const QMediaMetaData metaData = player.metaData();
    musicName = metaData.value(QMediaMetaData::Title).toString();
    musicAlbumn = metaData.value(QMediaMetaData::AlbumTitle).toString();
    musicSinger = metaData.value(QMediaMetaData::Author).toString();
    duration = metaData.value(QMediaMetaData::Duration).toLongLong();
    repairCorruptedMetaData();
    qDebug() << musicUrl.fileName() << ":" << musicName << ":"
             << musicSinger << ":" << musicAlbumn << ":" << duration;
}
