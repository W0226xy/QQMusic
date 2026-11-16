#include "qqmusic.h"
#include "ui_qqmusic.h"
#include<QPushButton>
#include<QPushButton>
#include<QDebug>
#include<QGraphicsDropShadowEffect>
#include<QJsonObject>
#include<QJsonArray>
#include<QFileDialog>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QMediaMetaData>
#include<QRandomGenerator>
#include<QNetworkReply>
#include<QTimer>
QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
    , player(nullptr)
    , audioOutput(nullptr)
    , totalTime(0)
    , currentIndex(-1)
    , onlineMusicService(nullptr)
    , refreshRecommendationsButton(nullptr)
    , recommendationStatusLabel(nullptr)
{
    ui->setupUi(this);
    initui();
    connectSignalAndSlots();
    initPlayer();
    initSqlite();
    initMusicList();
}

QQMusic::~QQMusic()
{
    delete ui;
}

void QQMusic::initui()
{
    //设置窗口无标题栏
    this->setWindowFlag(Qt::FramelessWindowHint);
    //设置窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon(":/images/tubiao.png"));

    //窗口设置阴影
    QGraphicsDropShadowEffect* shadowEffect=new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0,0);
    shadowEffect->setColor("#000000");//设置颜色
    shadowEffect->setBlurRadius(10);//设置圆角
    this->setGraphicsEffect(shadowEffect);

    //设置BtForm图标和文本信息
    ui->rec->setIconAndText(":/images/rec.png","推荐",0);
    ui->radio->setIconAndText(":/images/radio.png","电台",1);
    ui->music->setIconAndText(":/images/music.png","音乐馆",2);
    ui->like->setIconAndText(":/images/like.png","我喜欢",3);
    ui->local->setIconAndText(":/images/local.png","本地下载",4);
    ui->recent->setIconAndText(":/images/recent.png","最近播放",5);

    //本地下载BtForm动画默认显示，ps：原先所有的btform都有动画，但是在btform.cpp中隐藏了（ui->lineBox->hide();
    //只显示本地下载的btform的动画效果
    ui->local->showAnimal();
    //将localPage设置为当前页面
    ui->stackedWidget->setCurrentIndex(4);
    currentPage=ui->localPage;

    ui->recMusicBox->initRecBoxUi(1);
    ui->supplyMusicBox->initRecBoxUi(2);
    onlineMusicService = new OnlineMusicService(this);
    refreshRecommendationsButton = new QPushButton(QStringLiteral("刷新推荐"), this);
    refreshRecommendationsButton->setCursor(Qt::PointingHandCursor);
    refreshRecommendationsButton->setMinimumWidth(100);
    refreshRecommendationsButton->setStyleSheet(QStringLiteral(
        "QPushButton { padding: 7px 16px; border: none; border-radius: 4px; "
        "background: #1ECD97; color: white; }"
        "QPushButton:disabled { background: #A8DCCB; }"));
    recommendationStatusLabel = new QLabel(QStringLiteral("正在准备在线推荐…"), this);
    recommendationStatusLabel->setStyleSheet(QStringLiteral("color: #777777;"));
    recommendationStatusLabel->setWordWrap(true);
    ui->verticalLayout_7->insertWidget(1, refreshRecommendationsButton, 0, Qt::AlignRight);
    ui->verticalLayout_7->insertWidget(2, recommendationStatusLabel);

    //设置CommonPage信息
    ui->likePage->setMusicListType(PageType::LIKEE_PAGE);
    ui->likePage->setCommonPageUi("我喜欢",":/images/ilikebg.png");

    ui->localPage->setMusicListType(PageType::LOCAL_PAGE);
    ui->localPage->setCommonPageUi("本地音乐",":/images/localbg.png");

    ui->recentPage->setMusicListType(PageType::HISTORY_PAGE);
    ui->recentPage->setCommonPageUi("最近播放",":/images/recentbg.png");

    //播放控制区按钮图标设置
    ui->play->setIcon(QIcon(":images/play_2.png"));
    ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));
    volumeTool =new VolumeTool(this);

    //实例化LrcWord对象
    lrcpage=new LrcPage(this);
    lrcpage->setGeometry(this->rect());
    lrcpage->hide();

    //初始化上移动画对象
    lrcpageAnimation =new QPropertyAnimation(lrcpage,"geometry",this);
    lrcpageAnimation->setDuration(250);//设置动画时间
    lrcpageAnimation->setStartValue(QRect(10,10+lrcpage->height(),lrcpage->width(),lrcpage->height()));//起始时间
    lrcpageAnimation->setEndValue(QRect(10,10,lrcpage->width(),lrcpage->height()));
}

void QQMusic::initPlayer()
{
    //1.初始化媒体播放类
    player=new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    playbackMode = PlaybackMode::Random;

    //2.设置默认播放模式
    // Qt 6 不再提供 QMediaPlaylist，因此由 QQMusic 保存播放顺序。

    //3.设置默认音量大小,默认设置20%
    audioOutput->setVolume(0.2f);

    //关联QMediaPlayer的信号
    connect(player, &QMediaPlayer::playbackStateChanged, this,
            &QQMusic::onPlayerStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia)
            playNext();
    });

    //关联QMediaPlayer::durationChanged信号
    connect(player,&QMediaPlayer::durationChanged,this,&QQMusic::onDurationChanged);

    //关联QMediaPlayer::positionChanged信号
    connect(player,&QMediaPlayer::positionChanged,this,&QQMusic::onPositionChanged);

    connect(player, &QMediaPlayer::metaDataChanged, this,
            &QQMusic::onMetaDataChanged);
    connect(player, &QMediaPlayer::errorOccurred, this,
            [this](QMediaPlayer::Error, const QString &errorString) {
        qWarning() << "媒体播放失败:" << errorString;
        if (recommendationStatusLabel && currentIndex >= 0
                && currentIndex < currentQueue.size()
                && currentQueue.at(currentIndex).source == MusicSource::Online) {
            recommendationStatusLabel->setText(QStringLiteral("在线播放失败：%1").arg(errorString));
        }
    });
}

void QQMusic::connectSignalAndSlots()
{
    //关联BtForm的信号和处理该信号的槽函数
    //槽函数：专门用来接收信号（signal）并执行相应处理代码的函数
    //用户点击了btform，切换页面
    connect(ui->rec,&BtForm::btClick,this,&QQMusic::onBtFormClick);//参数1：谁发射信号 参数2：发射了什么信号 参数3：谁处理 参数4：处理的槽函数
    connect(ui->radio,&BtForm::btClick,this,&QQMusic::onBtFormClick);
    connect(ui->music,&BtForm::btClick,this,&QQMusic::onBtFormClick);
    connect(ui->like,&BtForm::btClick,this,&QQMusic::onBtFormClick);
    connect(ui->local,&BtForm::btClick,this,&QQMusic::onBtFormClick);
    connect(ui->recent,&BtForm::btClick,this,&QQMusic::onBtFormClick);

    //收藏或者不收藏处理
    connect(ui->localPage,&CommonPage::updateLikeMusic,this,&QQMusic::UpdateLikeMusicAndPage);
    connect(ui->likePage,&CommonPage::updateLikeMusic,this,&QQMusic::UpdateLikeMusicAndPage);
    connect(ui->recentPage,&CommonPage::updateLikeMusic,this,&QQMusic::UpdateLikeMusicAndPage);

    //播放控制区的信号与槽函数关联
    connect(ui->play,&QPushButton::clicked,this,&QQMusic::onPlayMusic);
    connect(ui->playUp,&QPushButton::clicked,this,&QQMusic::onPlayUpClicked);
    connect(ui->playDown,&QPushButton::clicked,this,&QQMusic::onPlayDownClicked);
    connect(ui->playMode,&QPushButton::clicked,this,&QQMusic::onPlaybackModelClicked);

    //likePage localPage recentPage都有播放所有按钮
    connect(ui->likePage,&CommonPage::playAll,this,&QQMusic::onPlayAll);
    connect(ui->localPage,&CommonPage::playAll,this,&QQMusic::onPlayAll);
    connect(ui->recentPage,&CommonPage::playAll,this,&QQMusic::onPlayAll);

    //处理likePage localPage recentPage中ListItemBox双击
    connect(ui->likePage,&CommonPage::playMusicByIndex,this,&QQMusic::playMusicByIndex);
    connect(ui->localPage,&CommonPage::playMusicByIndex,this,&QQMusic::playMusicByIndex);
    connect(ui->recentPage,&CommonPage::playMusicByIndex,this,&QQMusic::playMusicByIndex);

    //处理静音
    connect(volumeTool,&VolumeTool::setMusicMuted,this,&QQMusic::setPlayerMuted);

    //处理音量大小
    connect(volumeTool,&VolumeTool::setMusicVolume,this,&QQMusic::setPlayerVolume);

    connect(ui->progressBar,&MusicSlider::setMusicSliderPosition,this,&QQMusic::onMusicSliderChanged);

    //歌词按钮点击
    connect(ui->lrcWord,&QPushButton::clicked,this,&QQMusic::onLrcWordClicked);

    connect(refreshRecommendationsButton, &QPushButton::clicked,
            this, &QQMusic::refreshOnlineRecommendations);
    connect(ui->recMusicBox, &RecBox::playRequested,
            this, &QQMusic::onOnlineTrackRequested);
    connect(ui->supplyMusicBox, &RecBox::playRequested,
            this, &QQMusic::onOnlineTrackRequested);
    connect(onlineMusicService, &OnlineMusicService::tracksReady,
            this, &QQMusic::onOnlineTracksReady);
    connect(onlineMusicService, &OnlineMusicService::requestFailed, this,
            [this](const QString &message) {
        recommendationStatusLabel->setText(message);
    });
    connect(onlineMusicService, &OnlineMusicService::loadingChanged, this,
            [this](bool loading) {
        refreshRecommendationsButton->setEnabled(!loading);
        refreshRecommendationsButton->setText(loading
                ? QStringLiteral("加载中…") : QStringLiteral("刷新推荐"));
        if (loading)
            recommendationStatusLabel->setText(QStringLiteral("正在从 Jamendo 获取在线歌曲…"));
    });
    QTimer::singleShot(0, this, &QQMusic::refreshOnlineRecommendations);
}

void QQMusic::initSqlite()
{
    //1.进行数据库驱动加载
    QSqlDatabase sqlite=QSqlDatabase::addDatabase("QSQLITE");
    //2.设置数据库名称
    sqlite.setDatabaseName("QQMusic.db");
    //3.打开数据库
    if(!sqlite.open())
    {
        //打开失败
        QMessageBox::critical(this,"QQMusic","数据库打开失败");
        return ;
    }
    qDebug()<<"QQMusic数据库连接成功";

    //4.创建表
    QString sql="create table if not exists MusicInfo(\
                id integer primary key autoincrement,\
                musicId varchar(50) unique,\
                musicName varchar(100),\
                musicSinger varchar(100),\
                albumName varchar(50),\
                musicUrl varchar(256),\
                duration BIGNIT,\
                isLike INTEGER,\
                isHistory INTEGER\
            )";
   QSqlQuery query;
   if(!query.exec(sql))
   {
       QMessageBox::critical(this,"QQMusic","初始化错误");
       return ;
   }
   qDebug()<<"QQMusic表创建成功";
}

void QQMusic::initMusicList()
{
    musicList.readFromDB();

    ui->likePage->setMusicListType(PageType::LIKEE_PAGE);
    ui->likePage->reFresh(musicList);

    ui->localPage->setMusicListType(PageType::LOCAL_PAGE);
    ui->localPage->reFresh(musicList);

    ui->recentPage->setMusicListType(PageType::HISTORY_PAGE);
    ui->recentPage->reFresh(musicList);
}


void QQMusic::on_quit_clicked()
{
    //歌曲信息写入数据库
    musicList.writeToMusicDB();
    sqlite.close();
    close();
}

void QQMusic::onBtFormClick(int pageId)
{
    //清除之前btForm按钮的背景颜色
    //获取所有btform按钮
    QList<BtForm*> btFormList=this->findChildren<BtForm*>();
    for(auto btForm:btFormList)
    {
        if(btForm->getPageId()!=pageId)
        {
            btForm->cleanBackground();
        }
    }
    ui->stackedWidget->setCurrentIndex((pageId));//层叠窗口切换对应页面
    qDebug()<<"切换页面"<<pageId;
}

void QQMusic::mouseMoveEvent(QMouseEvent *event)
{
    if(Qt::LeftButton==event->buttons())//如果当前移动过程中左键还处于按下状态，就移动窗口。buttons()，表示当前所有正在按下的按键状态
    {
        move(event->globalPosition().toPoint()-dragPosition);//移动窗口
        qDebug()<<"move";
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void QQMusic::mousePressEvent(QMouseEvent *event)
{


    if(Qt::LeftButton==event->button())//如果这次按下的是左键，就执行下面的拖动准备工作。button()，表示是哪个键
    {
        //获取鼠标相对于屏幕左上角的全局坐标
        dragPosition=event->globalPosition().toPoint()-geometry().topLeft();//鼠标点击点相对于窗口左上角的偏移量
        //geometry().topLeft()当前窗口左上角在屏幕上的坐标
        return;
    }
    QWidget::mousePressEvent(event);

}


void QQMusic::on_volume_clicked()
{
    //1.获取ui->volume控件左上角的坐标，转换为基于屏幕的全局坐标
    QPoint point=ui->volume->mapToGlobal(QPoint(0,0));
    QPoint volumeLeftTop=point- QPoint( volumeTool->width()/2,volumeTool->height());



    volumeLeftTop.setX(volumeLeftTop.x()+15);
    volumeLeftTop.setY(volumeLeftTop.y()+30);

    //计算volumeTool需要移动到的位置，即ui->volume的正上方偏左一半
    volumeTool->move(volumeLeftTop);
    //窗口显示
    volumeTool->show();
}

void QQMusic::on_addLocal_clicked()
{
    QFileDialog fileDialog(this);//创建文件对话框

    //设置窗口的标题
    fileDialog.setWindowTitle("添加本地下载音乐");

    QDir dir(QDir::currentPath());
    dir.cdUp();//获取上层目录

    //设置文件对话框默认打开路径
    QString projectPath=dir.path();
    projectPath+="/QQMusic/musics/";
    qDebug()<<projectPath;
    fileDialog.setDirectory(projectPath);


    //设置一次打开多个
    fileDialog.setFileMode(QFileDialog::ExistingFiles);

    //通过文件的MIME类型进行过滤
    QStringList mimeTypeFilters;
    mimeTypeFilters<<"application/octet-stream";
    fileDialog.setMimeTypeFilters(mimeTypeFilters);

    if(QDialog::Accepted==fileDialog.exec())//fileDialog.exec();//打开窗口
    {
        //获取选中的文件
        QList<QUrl> fileUrls=fileDialog.selectedUrls();
        //fileUrls：内部存放的是刚刚选中的文件的url路径
        //需要将文件信息填充到本地下载
        //将所有音乐添加到音乐列表中(MusicList)
        musicList.addMusicsByUrl(fileUrls);

        //将歌曲信息更新到CommonPage页面中的listWidget
        //将CommonPage切换到本地下载的页面
        ui->stackedWidget->setCurrentIndex(4);

        ui->localPage->reFresh(musicList);

    }

}

void QQMusic::UpdateLikeMusicAndPage(bool isLike, const QString &musicId)
{
    //1.修改状态
    auto it=musicList.findMusicByMusicId(musicId);
    if(it!=musicList.end())
    {
        it->setIsLike(isLike);
    }
    //2.更新page页面的歌曲列表
    ui->likePage->reFresh(musicList);
    ui->localPage->reFresh(musicList);
    ui->recentPage->reFresh(musicList);
}

//播放控制

//播放暂停
void QQMusic::onPlayMusic()
{
    if(QMediaPlayer::PlayingState==player->playbackState())
    {
        //播放中点击，暂停播放
        player->pause();

    }
    else if(QMediaPlayer::PausedState==player->playbackState())
    {
        //暂停状态中点击按钮，则继续播放
        player->play();

    }
    else if(QMediaPlayer::StoppedState==player->playbackState())
    {
        //启动后从数据库恢复的歌曲尚未写入运行时播放列表时，
        //直接点击底部播放键也应能播放，而不是对空媒体源调用 play()。
        if (currentQueue.isEmpty()) {
            playAllMusicOfCommonPage(ui->localPage, 0);
        } else {
            if (currentIndex < 0 || currentIndex >= currentQueue.size())
                playAt(0);
            else
                player->play();
        }

    }
    else
    {
        qDebug()<<player->errorString();
    }
}

void QQMusic::onPlayerStateChanged()
{
    if(player->playbackState()==QMediaPlayer::PlayingState)
    {
        ui->play->setIcon((QIcon(":/images/play_on.png")));
    }
    else
    {
        ui->play->setIcon((QIcon(":/images/play3.png")));
    }
}

void QQMusic::onPlayDownClicked()
{
    playNext(true);
}

void QQMusic::onPlayUpClicked()
{
    playNext();
}

void QQMusic::onPlaybackModelClicked()
{
    switch (playbackMode) {
        case PlaybackMode::Loop:
            playbackMode = PlaybackMode::Random;
            ui->playMode->setToolTip("随机播放");
            break;
        case PlaybackMode::Random:
            playbackMode = PlaybackMode::CurrentItemInLoop;
            ui->playMode->setToolTip("单曲循环");
            break;
        case PlaybackMode::CurrentItemInLoop:
            playbackMode = PlaybackMode::Loop;
            ui->playMode->setToolTip("列表循环");
            break;
    }

    if(playbackMode == PlaybackMode::Loop)
    {
        ui->playMode->setIcon(QIcon(":/images/list_play.png"));
    }
    else if(playbackMode == PlaybackMode::Random)
    {
        ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));
    }
    else
    {
        ui->playMode->setIcon(QIcon(":/images/single_play.png"));
    }
}

void QQMusic::onCurrentIndexChanged(int index)
{
    if (index < 0 || index >= currentQueue.size())
        return;

    currentIndex=index;
    const PlaybackItem &item = currentQueue.at(index);
    if (item.source == MusicSource::Local) {
        auto it=musicList.findMusicByMusicId(item.id);
        if(it!=musicList.end())
            it->setIsHistory(true);
        ui->recentPage->reFresh(musicList);
    }
}

void QQMusic::onPlayAll(PageType pageType)
{
    //播放page对应的CommonPage页面的所有歌曲，默认从第1首开始
    //筛选pageType找到对应的CommonPage页面
    CommonPage* page=ui->localPage;
    switch (pageType) {
    case PageType::LIKEE_PAGE:
            page=ui->likePage;
            break;
    case PageType::LOCAL_PAGE:
            page=ui->localPage;
            break;
    case PageType::HISTORY_PAGE:
            page=ui->recentPage;
            break;
    default:
        qDebug()<<"暂不支持该页面";
    }


    //page中记录的就是要播放的页面
    playAllMusicOfCommonPage(page,0);
}

void QQMusic::playAllMusicOfCommonPage(CommonPage *page, int index)
{
    currentPage=page;
    currentQueue.clear();
    const QList<QUrl> urls = page->musicUrls(musicList);
    for (int i = 0; i < urls.size(); ++i) {
        const QString id = page->getMusicIdByIndex(i);
        auto it = musicList.findMusicByMusicId(id);
        if (it == musicList.end())
            continue;
        PlaybackItem item;
        item.source = MusicSource::Local;
        item.id = id;
        item.name = it->getMusicName();
        item.artist = it->getMusicSinger();
        item.url = it->getMusicUrl();
        item.duration = it->getMusicDuration();
        currentQueue.append(item);
    }
    playAt(index);

}

void QQMusic::playMusicByIndex(CommonPage *page, int index)
{
    playAllMusicOfCommonPage(page,index);
}

void QQMusic::refreshOnlineRecommendations()
{
    if (onlineMusicService->isLoading())
        return;
    // 多取一些候选，以便刷新时优先避开最近展示过的歌曲。
    onlineMusicService->fetchTracks(36);
}

void QQMusic::onOnlineTracksReady(const QList<OnlineTrack> &tracks)
{
    QList<OnlineTrack> selected;
    QSet<QString> selectedIds;
    for (const OnlineTrack &track : tracks) {
        if (!recentlyRecommendedIds.contains(track.id) && !selectedIds.contains(track.id)) {
            selected.append(track);
            selectedIds.insert(track.id);
            if (selected.size() == 12)
                break;
        }
    }
    // 曲库响应不足时适当放宽跨批次去重，但同一批次仍不重复。
    for (const OnlineTrack &track : tracks) {
        if (selected.size() == 12)
            break;
        if (!selectedIds.contains(track.id)) {
            selected.append(track);
            selectedIds.insert(track.id);
        }
    }

    if (selected.isEmpty()) {
        recommendationStatusLabel->setText(QStringLiteral("本次没有可播放的在线歌曲，已保留原推荐。"));
        return;
    }

    onlineTracks = selected;
    if (recentlyRecommendedIds.size() > 120)
        recentlyRecommendedIds.clear();
    for (const OnlineTrack &track : onlineTracks)
        recentlyRecommendedIds.insert(track.id);

    ui->recMusicBox->setTracks(onlineTracks.mid(0, 4));
    ui->supplyMusicBox->setTracks(onlineTracks.mid(4, 8));
    recommendationStatusLabel->setText(onlineTracks.size() >= 12
            ? QStringLiteral("已加载 12 首 Jamendo 在线歌曲")
            : QStringLiteral("Jamendo 本次仅返回 %1 首可播放歌曲").arg(onlineTracks.size()));
}

void QQMusic::onOnlineTrackRequested(const OnlineTrack &track)
{
    currentQueue.clear();
    currentPage = nullptr;
    int requestedIndex = -1;
    for (const OnlineTrack &onlineTrack : onlineTracks) {
        PlaybackItem item;
        item.source = MusicSource::Online;
        item.id = onlineTrack.id;
        item.name = onlineTrack.name;
        item.artist = onlineTrack.artist;
        item.url = onlineTrack.audioUrl;
        item.coverUrl = onlineTrack.coverUrl;
        item.duration = onlineTrack.duration;
        if (onlineTrack.id == track.id)
            requestedIndex = currentQueue.size();
        currentQueue.append(item);
    }
    if (requestedIndex >= 0)
        playAt(requestedIndex);
}

void QQMusic::updateCurrentTrackUi()
{
    if (currentIndex < 0 || currentIndex >= currentQueue.size())
        return;

    const PlaybackItem &item = currentQueue.at(currentIndex);
    ui->musicName->setText(item.name.isEmpty() ? QStringLiteral("未知歌曲") : item.name);
    ui->musicSinger->setText(item.artist.isEmpty() ? QStringLiteral("未知歌手") : item.artist);
    ui->musicCover->setPixmap(QPixmap(QStringLiteral(":/images/rec/001.png")));
    ui->musicCover->setScaledContents(true);
    ++coverRequestSerial; // 使上一首歌尚未完成的封面请求失效。

    if (item.source == MusicSource::Online) {
        lrcpage->clearLyrics();
        loadCurrentCover(item.coverUrl);
        return;
    }

    auto it = musicList.findMusicByMusicId(item.id);
    if (it != musicList.end())
        lrcpage->parseLrcFile(it->getLrcFilePath());
    else
        lrcpage->clearLyrics();
}

void QQMusic::loadCurrentCover(const QUrl &url)
{
    if (!url.isValid())
        return;

    const quint64 serial = coverRequestSerial;
    QNetworkRequest request(url);
    request.setTransferTimeout(10000);
    QNetworkReply *reply = coverManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, serial]() {
        const QByteArray data = reply->readAll();
        const bool succeeded = reply->error() == QNetworkReply::NoError;
        reply->deleteLater();
        if (!succeeded || serial != coverRequestSerial)
            return;
        QPixmap pixmap;
        if (pixmap.loadFromData(data))
            ui->musicCover->setPixmap(pixmap);
    });
}

void QQMusic::setPlayerMuted(bool isMuted)
{
    audioOutput->setMuted(isMuted);
}

void QQMusic::setPlayerVolume(int volume)
{
    audioOutput->setVolume(volume / 100.0f);
}

void QQMusic::onDurationChanged(qint64 duration)
{
    totalTime=duration;
    //duration为歌曲总时长,单位毫秒
    //需要将整形总时长转换为min:sec
    //duration/1000/60;//min
    //duration/1000%60;//sec
    ui->totalTime->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0'))
                                           .arg(duration/1000%60,2,10,QChar('0')));

}

void QQMusic::onPositionChanged(qint64 position)
{
    //更新播放时间
    ui->currentTime->setText(QString("%1:%2").arg(position/1000/60,2,10,QChar('0'))
                             .arg(position/1000%60,2,10,QChar('0')));
    //更新进度条位置
    ui->progressBar->setStep(totalTime > 0 ? position / static_cast<float>(totalTime) : 0.0f);
    //在歌词界面同步显示歌词

    if(currentIndex>=0)
    {
        lrcpage->showLrcWordLine(position);
    }

}

void QQMusic::onMusicSliderChanged(float ration)
{
    //根据进度条与总宽度比例，更新播放时间
    qint64 duration=totalTime*ration;
    ui->currentTime->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0'))
                             .arg(duration/1000%60,2,10,QChar('0')));
    //时间修改后，播放时间也跟着修改
    player->setPosition(duration);
}

void QQMusic::onMetaDataChanged()
{
    if (currentIndex < 0 || currentIndex >= currentQueue.size()
            || currentQueue.at(currentIndex).source == MusicSource::Online)
        return;

    //获取歌曲封面
    QVariant coverimage = player->metaData().value(QMediaMetaData::CoverArtImage);
    if(coverimage.isValid())
    {
        QImage image=coverimage.value<QImage>();
        ui->musicCover->setPixmap(QPixmap::fromImage(image));
        if (currentPage)
            currentPage->setMusicImage(QPixmap::fromImage(image));
    }
    else
    {
        qDebug()<<"歌曲无封面";
        //设置默认图片
        QString path=":/images/rec/001.png";
        ui->musicCover->setPixmap(path);
        if (currentPage)
            currentPage->setMusicImage(path);
    }
    ui->musicCover->setScaledContents(true);

}

void QQMusic::playAt(int index)
{
    if (currentQueue.isEmpty()) {
        currentIndex = -1;
        return;
    }

    currentIndex = qBound(0, index, currentQueue.size() - 1);
    player->setSource(currentQueue.at(currentIndex).url);
    onCurrentIndexChanged(currentIndex);
    updateCurrentTrackUi();
    player->play();
}

void QQMusic::playNext(bool previous)
{
    if (currentQueue.isEmpty())
        return;

    if (playbackMode == PlaybackMode::CurrentItemInLoop && !previous) {
        player->setPosition(0);
        player->play();
        return;
    }

    int nextIndex = currentIndex;
    if (playbackMode == PlaybackMode::Random && currentQueue.size() > 1) {
        do {
            nextIndex = QRandomGenerator::global()->bounded(currentQueue.size());
        } while (nextIndex == currentIndex);
    } else {
        const int step = previous ? -1 : 1;
        nextIndex = (currentIndex + step + currentQueue.size()) % currentQueue.size();
    }
    playAt(nextIndex);
}

void QQMusic::onLrcWordClicked()
{
    lrcpage->show();
    lrcpageAnimation->start();
}

void QQMusic::on_min_clicked()
{
    showMinimized();
}

void QQMusic::on_max_clicked()
{
    showMaximized();
}
