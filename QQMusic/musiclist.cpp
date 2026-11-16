#include "musiclist.h"
#include<QMimeDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>
MusicList::MusicList()
{

}

void MusicList::addMusicsByUrl(const QList<QUrl> &musicUrls)
{
    //将所有音乐放置到musicList
    for(auto e:musicUrls)
{
        //查找用哈希O(1)
        QString musicPath=e.toLocalFile();
        if(musicPaths.contains(musicPath))
            continue;

        //歌曲不存在
        musicPaths.insert(musicPath);
        //如果musicUrl是有效歌曲文件，则将其添加到歌曲列表
        //检测歌曲文件的MIME类型
        QMimeDatabase mimeDB;
        QMimeType mimeType=mimeDB.mimeTypeForFile(e.toLocalFile());
        QString mime=mimeType.name();

        //mime:  audio/mepg(mp3文件)  audio/flac(无损音乐)  audio/wav
        if(mime=="audio/mpeg"||mime=="audio/flac"||mime=="audio/wav")
        {

            //将url转换为一个Music对象，添加到musicList中
            Music music(e);
            musicList.push_back(music);
        }


    }
}

iterator MusicList::findMusicByMusicId(const QString &musicId)
{
    for(auto it=begin();it!=end();it++)
    {
        if(it->getMusicId()==musicId)
        {
            return it;
        }
    }
    return end();
}

iterator MusicList::begin()
{
    return musicList.begin();
}

iterator MusicList::end()
{
    return musicList.end();
}

void MusicList::writeToMusicDB()
{
    for(auto music:musicList)
    {
        //拿到每个music对象后，将music所有属性写入数据库
        music.InsertMusicToDB();
    }
}

void MusicList::readFromDB()
{
    QSqlQuery query;
    query.prepare("select musicId,musicName,musicSinger,albumName,musicUrl,duration,isLike,isHistory from MusicInfo");
    if(!query.exec())
    {
        qDebug()<<"数据库查询失败"<<query.lastError();
        return;
    }
    while(query.next())
    {
        Music music;
        music.setMusicId(query.value(0).toString());
        music.setMusicName(query.value(1).toString());
        music.setMusicSinger(query.value(2).toString());
        music.setMusicAlbum(query.value(3).toString());
        music.setMusicUrl("file:///"+query.value(4).toString());
        music.setMusicDuration(query.value(5).toLongLong());
        music.setIsLike(query.value(6).toBool());
        music.setIsHistory(query.value(7).toBool());
        // 旧数据库可能保存了播放器错误解码的 ID3 中文标签，启动时一并修正。
        music.repairCorruptedMetaData();
        musicList.push_back(music);
        //恢复musicPaths，防止相同目录下歌曲重复加载
        musicPaths.insert(music.getMusicUrl().toLocalFile());
    }
}
