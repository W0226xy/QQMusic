#ifndef QQMUSIC_H
#define QQMUSIC_H
#include "volumetool.h"
#include "onlinemusicservice.h"
#include <QWidget>
#include <QMouseEvent>
#include"music.h"
#include"musiclist.h"
#include<QMediaPlayer>
#include<QAudioOutput>
#include"commonpage.h"
#include"lrcpage.h"
#include<QPropertyAnimation>
#include<QSqlDatabase>
#include<QNetworkAccessManager>
#include<QSet>
class QLabel;
class QPushButton;
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
    void initSqlite();
    void initMusicList();
private slots:
    void on_quit_clicked();
    void onBtFormClick(int pageId);

    void on_volume_clicked();//音量按钮点击后显示VolumeTool窗口

    void on_addLocal_clicked();

    void UpdateLikeMusicAndPage(bool isLike,const QString& musicId);

    //播放控制区的槽函数
    //播放按钮：歌曲暂停与播放
    void onPlayMusic();

    void onPlayerStateChanged();//QMediaPlayer中stateChanged信号对应槽函数
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
    void onMetaDataChanged();//元数据改变
    void onOnlineTracksReady(const QList<OnlineTrack> &tracks);
    void onOnlineTrackRequested(const OnlineTrack &track);
    void refreshOnlineRecommendations();

    void onLrcWordClicked();
    void on_min_clicked();

    void on_max_clicked();

protected:
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
private:
    Ui::QQMusic *ui;

    QPoint dragPosition;

    VolumeTool* volumeTool;//音量控制

    MusicList musicList;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    enum class MusicSource { Local, Online };
    struct PlaybackItem {//音乐播放器统一使用的数据
        MusicSource source = MusicSource::Local;//播放来源
        QString id;//歌曲id
        QString name;//歌曲名
        QString artist;//歌手
        QUrl url;//音频地址
        QUrl coverUrl;//封面地址
        qint64 duration = 0;//歌曲时长
    };
    QList<PlaybackItem> currentQueue;
    enum class PlaybackMode { Loop, Random, CurrentItemInLoop };
    PlaybackMode playbackMode;
    CommonPage* currentPage;//记录当前正在播放的commonPage页面
    qint64 totalTime;//记录媒体源总时间
    int currentIndex;//记录当前正在播放歌曲在媒体列表中的索引
    LrcPage* lrcpage;
    QPropertyAnimation* lrcpageAnimation;
    QSqlDatabase sqlite;
    OnlineMusicService *onlineMusicService;
    QList<OnlineTrack> onlineTracks;
    QSet<QString> recentlyRecommendedIds;//最近推荐过的歌曲id
    QPushButton *refreshRecommendationsButton;
    QLabel *recommendationStatusLabel;
    QNetworkAccessManager coverManager;//用于下载在线音乐封面
    quint64 coverRequestSerial = 0;

    void playAt(int index);
    void playNext(bool previous = false);
    void updateCurrentTrackUi();
    void loadCurrentCover(const QUrl &url);
};
#endif // QQMUSIC_H
