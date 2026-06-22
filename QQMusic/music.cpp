#include "music.h"
#include<QUuid>
#include<QMediaPlayer>
#include<QDebug>
#include<QCoreApplication>
#include<QSqlQuery>
#include<QSqlError>
#include<QtDebug>
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
    //2.设置媒体源：依靠setMedia方法解析元数据
    player.setMedia(musicUrl);
    //3.因为setMedia不会等待音乐加载就立即返回
    //所以，在通过mediaMeta方法获取元数据时，需要保证媒体已经添加完毕
    //可以通过isMetaDataAvailable检查是否有效，返回true则说明加载完成
    while(!player.isMetaDataAvailable())
    {
        QCoreApplication::processEvents();
    }
    //到这里说明加载完成，可以获取有效的元数据
    if(player.isMetaDataAvailable())
    {
       musicName= player.metaData("Title").toString();
       musicAlbumn=player.metaData("AlbumTitle").toString();
       musicSinger=player.metaData("Author").toString();
       duration=player.metaData("Duration").toLongLong();
       QString fileName=musicUrl.fileName();

       //musicName为""的处理
       //"2002年的第一场雪 - 刀郎.mp3"
       //找-的位置
       int index=fileName.indexOf('-');

       if(musicName.isEmpty())
       {
           if(index!=-1)//-1表示没找到
           {//"2002年的第一场雪 - 刀郎.mp3"
               musicName=fileName.mid(0,index).trimmed();
           }
           else
           {//"2002年的第一场雪刀郎.mp3"
               musicName=fileName.mid(0,fileName.indexOf('.')).trimmed();
           }
       }
       //作者为空
       if(musicSinger.isEmpty())
       {
           if(index!=-1)
           {
               musicSinger=fileName.mid(index+1,fileName.indexOf('.')-index-1).trimmed();
           }
           else
           {
               musicSinger="未知歌手";
           }
       }

       //专辑名为空
       if(musicAlbumn.isEmpty())
       {
           musicAlbumn="未知专辑";
       }

       qDebug()<<fileName<<":"<<musicName<<":"<<musicSinger<<":"<<musicAlbumn<<":"<<duration;
    }

}
