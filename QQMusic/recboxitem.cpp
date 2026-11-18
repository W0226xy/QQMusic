#include "recboxitem.h"
#include "ui_recboxitem.h"
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmapCache>
#include <QPropertyAnimation>

RecBoxItem::RecBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBoxItem)
{
    ui->setupUi(this);
    ui->musicImageBox->installEventFilter(this);
    setCursor(Qt::PointingHandCursor);
    ui->recMusicBtn->setIcon(QIcon(QStringLiteral(":/images/play.png")));
    ui->recMusicBtn->setIconSize(QSize(42, 42));
    connect(ui->recMusicBtn, &QPushButton::clicked, this, [this]() {
        if (!currentTrack.id.isEmpty())
            emit playRequested(currentTrack);
    });
}

RecBoxItem::~RecBoxItem()
{
    delete ui;
}

bool RecBoxItem::eventFilter(QObject *watched, QEvent *event)//watched被观察的组件，event触发的事件
{
    if(watched==ui->musicImageBox)
    {
        if(QEvent::Enter==event->type())//鼠标进入图片框
        {

            //添加图片上移动画
            QPropertyAnimation* animation =new QPropertyAnimation(ui->musicImageBox,"geometry", this);
            animation->setDuration(150);//设置动画持续时间
            animation->setStartValue(QRect(9,9,ui->musicImageBox->width(),ui->musicImageBox->height()));//起始帧
            animation->setEndValue(QRect(9,0,ui->musicImageBox->width(),ui->musicImageBox->height()));//结束帧
            animation->start(QAbstractAnimation::DeleteWhenStopped);


        }
        else if(QEvent::Leave==event->type())//鼠标离开图片框
        {

            //添加图片下移动画
            QPropertyAnimation* animation =new QPropertyAnimation(ui->musicImageBox,"geometry", this);
            animation->setDuration(150);//设置动画持续时间
            animation->setStartValue(QRect(9,0,ui->musicImageBox->width(),ui->musicImageBox->height()));//起始帧
            animation->setEndValue(QRect(9,9,ui->musicImageBox->width(),ui->musicImageBox->height()));//结束帧
            animation->start(QAbstractAnimation::DeleteWhenStopped);

        }
        else if (QEvent::MouseButtonRelease == event->type())
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton && !currentTrack.id.isEmpty())
                emit playRequested(currentTrack);
            return true;
        }
        if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
            return true;
    }
    return QObject::eventFilter(watched,event);
}

void RecBoxItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !currentTrack.id.isEmpty())
        emit playRequested(currentTrack);
    QWidget::mouseReleaseEvent(event);
}

//把一首在线歌曲的数据填进一个推荐卡片 RecBoxItem，显示歌名、歌手和封面；封面优先从缓存读取，缓存没有才异步下载。
void RecBoxItem::setTrack(const OnlineTrack &track)
{
    //先保存当前卡片对应的歌曲。
    currentTrack = track;
    //接口没返回歌手名，就用“未知歌手”兜底。
    const QString artist = track.artist.isEmpty() ? QStringLiteral("未知歌手") : track.artist;
    QLabel *artistLabel = findChild<QLabel *>(QStringLiteral("recBoxItemArtist"));
    ui->recBoxItemText->setText(artistLabel
            ? track.name : QStringLiteral("%1\n%2").arg(track.name, artist));
    ui->recBoxItemText->setToolTip(track.name);
    if (artistLabel) {
        artistLabel->setText(artist);
        artistLabel->setToolTip(track.artist);
    }
    //设置默认封面图，因为网络封面是异步加载的。如果不先重置，用户刷新推荐卡片后，卡片可能暂时显示上一首歌的旧封面
    ui->recMusicImage->setPixmap(QPixmap(QStringLiteral(":/images/rec/001.png")));
    ui->recMusicImage->setScaledContents(true);

    //如果接口没有给有效封面地址，就保留默认图，直接结束。
    if (!track.coverUrl.isValid())
        return;

    //cacheKey 用封面 URL 作为键；
    //若之前已下载过同一个 URL 的封面，直接从缓存读取；
    const QString cacheKey = track.coverUrl.toString();
    QPixmap cached;
    if (QPixmapCache::find(cacheKey, &cached)) {
        ui->recMusicImage->setPixmap(cached);
        return;
    }

    //保存“本次请求封面时对应的歌曲 ID”。
    const QString requestedTrackId = track.id;
    //创建图片下载请求，设置 10 秒超时。
    QNetworkRequest request(track.coverUrl);
    request.setTransferTimeout(10000);
    //发送 GET 请求，开始异步下载封面
    QNetworkReply *reply = coverManager.get(request);
    //图片下载结束后执行这个 lambda。
    connect(reply, &QNetworkReply::finished, this, [this, reply, requestedTrackId, cacheKey]() {
        //读取下载回来的图片二进制数据；
        const QByteArray imageData = reply->readAll();
        //检查网络请求是否成功；
        const bool succeeded = reply->error() == QNetworkReply::NoError;
        //请求对象交给 Qt 稍后删除，避免内存泄漏。
        reply->deleteLater();
        //下载失败：不更新界面；
        //当前卡片已经显示其他歌曲：也不更新界面。
        if (!succeeded || currentTrack.id != requestedTrackId)
            return;
        //将网络下载到的字节数据解析为图片。
        QPixmap pixmap;
        if (pixmap.loadFromData(imageData)) {
            QPixmapCache::insert(cacheKey, pixmap);//将封面放入缓存，后面相同图片无需再次下载；
            ui->recMusicImage->setPixmap(pixmap);//将封面显示到当前推荐卡片上。
        }
    });
}
