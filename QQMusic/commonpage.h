#ifndef COMMONPAGE_H
#define COMMONPAGE_H
#include "musiclist.h"
#include <QWidget>
#include<QMediaPlaylist>
namespace Ui {
class CommonPage;
}


enum PageType
{
    LIKEE_PAGE,//我喜欢页面
    LOCAL_PAGE,//本地下载页面
    HISTORY_PAGE//历史播放页面
};

class CommonPage : public QWidget
{
    Q_OBJECT

public:
    explicit CommonPage(QWidget *parent = nullptr);
    ~CommonPage();

    void setMusicListType(PageType pageType);
    void setCommonPageUi(const QString& text,const QString& image);
    void addMusicToMusicPage(MusicList& musicList);
    void reFresh(MusicList& musicList);

    //将歌曲添加到播放列表中
    void addMusicToPlaylist(MusicList& musicList,QMediaPlaylist* playList);

    void setMusicImage(QPixmap pixmap);

    QString getMusicIdByIndex(int index);
signals:
    void updateLikeMusic(bool isLike,const QString& musicId);
    void playAll(PageType);
    void playMusicByIndex(CommonPage* ,int);
private:
    Ui::CommonPage *ui;
    PageType pageType;//保存该页面的类别说明
    QVector<QString> musicOfPage;//保存pageType对应页面的歌曲ID
};

#endif // COMMONPAGE_H
