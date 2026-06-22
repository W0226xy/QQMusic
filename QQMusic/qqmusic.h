#ifndef QQMUSIC_H
#define QQMUSIC_H
#include "volumetool.h"
#include <QWidget>
#include <QMouseEvent>
#include"music.h"
#include"musiclist.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include"commonpage.h"
#include"lrcpage.h"
#include<QPropertyAnimation>
#include<QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class QQMusic; }
QT_END_NAMESPACE

class QQMusic : public QWidget
{
    Q_OBJECT

public:
    QQMusic(QWidget *parent = nullptr);
    ~QQMusic();
    void initui();
    void initPlayer();
    void connectSignalAndSlots();
    QJsonArray randomPiction();
    void initSqlite();
    void initMusicList();
private slots:
    void on_quit_clicked();
    void onBtFormClick(int pageId);

    void on_volume_clicked();

    void on_addLocal_clicked();

    void UpdateLikeMusicAndPage(bool isLike,const QString& musicId);

    //播放控制区的槽函数
    //播放按钮：歌曲暂停与播放
    void onPlayMusic();

    void onPlayerStateChanged();//QMediaPlayer中stateChanged信号对应槽函数
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode);
    void onCurrentIndexChanged(int index);//playlist中播放源发生改变，index表示正在播放的媒体索引

    //上一曲，下一曲
    void onPlayDownClicked();
    void onPlayUpClicked();

    //播放模式设置
    void onPlaybackModelClicked();

    void onPlayAll(PageType pageType);//播放全部按钮发射信号对应的槽函数

    void playAllMusicOfCommonPage(CommonPage* page,int index);

    void playMusicByIndex(CommonPage* page,int index);

    //VolumeTool类中setMusicMuted信号对应的槽函数
    void setPlayerMuted(bool isMuted);

    //VolumeTool类中setMusicVolume信号对应的槽函数
    void setPlayerVolume(int volume);
    void onDurationChanged(qint64 duration);//媒体切换，播放时间也随之改变
    void onPositionChanged(qint64 position);//播放进度改变

    void onMusicSliderChanged(float ration);//进度条改变，播放时间随之修改
    void onMetaDataAvailabelChanged(bool available);//元数据改变

    void onLrcWordClicked();
    void on_min_clicked();

    void on_max_clicked();

protected:
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
private:
    Ui::QQMusic *ui;

    QPoint dragPosition;

    VolumeTool* volumeTool;

    MusicList musicList;

    QMediaPlayer* player;
    QMediaPlaylist* playList;
    CommonPage* currentPage;//记录当前正在播放的commonPage页面
    qint64 totalTime;//记录媒体源总时间
    int currentIndex;//记录当前正在播放歌曲在媒体列表中的索引
    LrcPage* lrcpage;
    QPropertyAnimation* lrcpageAnimation;
    QSqlDatabase sqlite;
};
#endif // QQMUSIC_H
