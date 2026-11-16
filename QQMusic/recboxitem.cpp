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

bool RecBoxItem::eventFilter(QObject *watched, QEvent *event)
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

void RecBoxItem::setTrack(const OnlineTrack &track)
{
    currentTrack = track;
    const QString artist = track.artist.isEmpty() ? QStringLiteral("未知歌手") : track.artist;
    QLabel *artistLabel = findChild<QLabel *>(QStringLiteral("recBoxItemArtist"));
    ui->recBoxItemText->setText(artistLabel
            ? track.name : QStringLiteral("%1\n%2").arg(track.name, artist));
    ui->recBoxItemText->setToolTip(track.name);
    if (artistLabel) {
        artistLabel->setText(artist);
        artistLabel->setToolTip(track.artist);
    }
    ui->recMusicImage->setPixmap(QPixmap(QStringLiteral(":/images/rec/001.png")));
    ui->recMusicImage->setScaledContents(true);

    if (!track.coverUrl.isValid())
        return;

    const QString cacheKey = track.coverUrl.toString();
    QPixmap cached;
    if (QPixmapCache::find(cacheKey, &cached)) {
        ui->recMusicImage->setPixmap(cached);
        return;
    }

    const QString requestedTrackId = track.id;
    QNetworkRequest request(track.coverUrl);
    request.setTransferTimeout(10000);
    QNetworkReply *reply = coverManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, requestedTrackId, cacheKey]() {
        const QByteArray imageData = reply->readAll();
        const bool succeeded = reply->error() == QNetworkReply::NoError;
        reply->deleteLater();
        if (!succeeded || currentTrack.id != requestedTrackId)
            return;

        QPixmap pixmap;
        if (pixmap.loadFromData(imageData)) {
            QPixmapCache::insert(cacheKey, pixmap);
            ui->recMusicImage->setPixmap(pixmap);
        }
    });
}
