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
#include<algorithm>
#include<random>
QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
    , currentIndex(-1)
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

    srand(time(NULL));
    ui->recMusicBox->initRecBoxUi(randomPiction(),1);
    ui->supplyMusicBox->initRecBoxUi(randomPiction(),2);

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
}

QJsonArray QQMusic::randomPiction()
{
    //推荐文本+推荐图片路径
    QVector<QString> vecImageName;
    vecImageName<<"001.png"<<"003.png"<<"004.png"<<"005.png"<<"006.png"<<"007.png"<<"008.png"<<"009.png"
               <<"010.png"<<"011.png"<<"012.png"<<"013.png"<<"014.png"<<"015.png"<<"016.png"<<"017.png"
              <<"018.png"<<"019.png"<<"020.png"<<"021.png"<<"022.png"<<"023.png"<<"024.png"<<"025.png"
              <<"026.png"<<"027.png"<<"028.png"<<"029.png"<<"030.png"<<"031.png"<<"032.png"<<"033.png"
                <<"034.png"<<"035.png"<<"036.png"<<"037.png"<<"038.png"<<"039.png"<<"040.png";
    std::mt19937 generator(std::random_device{}());
    std::shuffle(vecImageName.begin(), vecImageName.end(), generator);

    //path:"/images/rec/"+vecImageName[i];
    //text:推荐-001

    QJsonArray objArray;
    for(int i=0;i<vecImageName.size();i++)
    {
        QJsonObject obj;
        obj.insert("path",":/images/rec/"+vecImageName[i]);//键值对，path 和 text
        QString strText = QString("推荐-%1").arg(i + 1, 3, 10, QChar('0'));//i占3位，10进制,如果不够3位，左边用字符串0填充
        obj.insert("text",strText);
        objArray.append(obj);
    }
    return objArray;
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

        //localPage中的歌曲添加到媒体播放列表中
        playList = ui->localPage->musicUrls(musicList);
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
        if (playList.isEmpty()) {
            playList = currentPage->musicUrls(musicList);
            if (playList.isEmpty()) {
                currentPage = ui->localPage;
                playList = currentPage->musicUrls(musicList);
            }
        }

        if (!playList.isEmpty()) {
            if (currentIndex < 0 || currentIndex >= playList.size())
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
    if (index < 0 || index >= playList.size() || currentPage == nullptr)
        return;

    currentIndex=index;
    //由于CommonPage页面中的歌曲和正在播放的播放列表中的歌曲索引相同
    //知道歌曲在playlist中的索引后，到CommonPage中获取
    //playlist中的歌曲就是根据CommonPage中的musicOfPage加载

    //通过索引找到歌曲，然后修改歌曲的isHistory属性
    QString musicId =currentPage->getMusicIdByIndex(index);
    auto it=musicList.findMusicByMusicId(musicId);
    if(it!=musicList.end())
    {
        it->setIsHistory(true);
    }
    ui->recentPage->reFresh(musicList);
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
    playList = page->musicUrls(musicList);
    playAt(index);

}

void QQMusic::playMusicByIndex(CommonPage *page, int index)
{
    playAllMusicOfCommonPage(page,index);
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
    ui->progressBar->setStep(position/(float)totalTime);
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
    //歌曲名称、歌曲作者直接到Music对象中获取
    //此时需要知道媒体源在播放列表中的索引
    QString musicId=currentPage->getMusicIdByIndex(currentIndex);
    auto it=musicList.findMusicByMusicId(musicId);
    QString musicName("未知歌曲");
    QString musicSinger("歌手");

    if(it!=musicList.end())
    {
        musicName=it->getMusicName();
        musicSinger=it->getMusicSinger();
    }
    ui->musicName->setText(musicName);
    ui->musicSinger->setText(musicSinger);

    //获取歌曲封面
    QVariant coverimage = player->metaData().value(QMediaMetaData::CoverArtImage);
    if(coverimage.isValid())
    {
        QImage image=coverimage.value<QImage>();
        ui->musicCover->setPixmap(QPixmap::fromImage(image));
        currentPage->setMusicImage(QPixmap::fromImage(image));
    }
    else
    {
        qDebug()<<"歌曲无封面";
        //设置默认图片
        QString path=":/images/rec/001.png";
        ui->musicCover->setPixmap(path);
        currentPage->setMusicImage(path);
    }
    ui->musicCover->setScaledContents(true);

    //解析歌曲lrc歌词
    if(it!=musicList.end())
    {
        //获取lrc文件路径
        QString lrcPath=it->getLrcFilePath();
        //解析lrc文件
        lrcpage->parseLrcFile(lrcPath);
    }

}

void QQMusic::playAt(int index)
{
    if (playList.isEmpty()) {
        currentIndex = -1;
        return;
    }

    currentIndex = qBound(0, index, playList.size() - 1);
    player->setSource(playList.at(currentIndex));
    onCurrentIndexChanged(currentIndex);
    player->play();
}

void QQMusic::playNext(bool previous)
{
    if (playList.isEmpty())
        return;

    if (playbackMode == PlaybackMode::CurrentItemInLoop && !previous) {
        player->setPosition(0);
        player->play();
        return;
    }

    int nextIndex = currentIndex;
    if (playbackMode == PlaybackMode::Random && playList.size() > 1) {
        do {
            nextIndex = QRandomGenerator::global()->bounded(playList.size());
        } while (nextIndex == currentIndex);
    } else {
        const int step = previous ? -1 : 1;
        nextIndex = (currentIndex + step + playList.size()) % playList.size();
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
