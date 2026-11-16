#include "commonpage.h"
#include "ui_commonpage.h"
#include "listitembox.h"
#include <QDebug>
CommonPage::CommonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonPage)
{
    ui->setupUi(this);
    ui->pageMusicList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(ui->playAllBtn,&QPushButton::clicked,this,[=](){
        //播放所有按钮点击后，通知QQMusic播放当前pageType标记的page的所有歌曲
        emit playAll(pageType);
    });
    connect(ui->pageMusicList,&QListWidget::doubleClicked,this,[=](const QModelIndex &index){
        //鼠标双击后，发射信号告诉QQMusic，播放this页面被双击的歌曲
        emit playMusicByIndex(this,index.row());
    });

}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setMusicListType(PageType pageType)
{
    this->pageType=pageType;
}



void CommonPage::setCommonPageUi(const QString &text, const QString &imagePath)
{
    ui->PageTittle->setText(text);
    ui->musicImageLabel->setPixmap(QPixmap(imagePath));//把图片设置到musicImageLabel组件
    ui->musicImageLabel->setScaledContents(true);
}

void CommonPage::addMusicToMusicPage(MusicList &musicList)
{
    //1.清除之前的歌曲内容(musicOfPage中之前显示的内容清空)
    musicOfPage.clear();

    for(auto music: musicList)
    {
        switch (pageType) {
        case LIKEE_PAGE:
            if(music.getIsLike())
            {
                musicOfPage.push_back(music.getMusicId());
            }
            break;
        case LOCAL_PAGE:
            musicOfPage.push_back(music.getMusicId());
            break;
        case HISTORY_PAGE:
            if(music.getIsHistory())
            {
                musicOfPage.push_back(music.getMusicId());
            }
            break;
        default:
            qDebug()<<"暂未支持";

        }
    }
}

//将歌曲的信息更新到界面
void CommonPage::reFresh(MusicList &musicList)
{
    //将QListWidget之前已经添加的内容清空
    ui->pageMusicList->clear();

    //添加新歌曲
    addMusicToMusicPage(musicList);
    for(auto musicId:musicOfPage)
    {
      auto it=  musicList.findMusicByMusicId(musicId);
      if(it==musicList.end())//没查到
      {
          continue;
      }
      //找到了，将music信息（歌曲名称、作者、专辑名称）更新到界面
      //测试
      //将ListBoxItem对象放到PageMusicList中
      ListItemBox* listItemBox=new ListItemBox(this);
      //歌曲名称、作者、专辑更新到界面
      listItemBox->setMusicName(it->getMusicName());
      listItemBox->setMusicSinger(it->getMusicSinger());
      listItemBox->setMusicAlbum(it->getMusicAlbum());
      listItemBox->setLikeMusic(it->getIsLike());
      QListWidgetItem* item=new QListWidgetItem(ui->pageMusicList);

      //qDebug()<<item->sizeHint();//获取控键大小
      item->setSizeHint(QSize(listItemBox->width(),listItemBox->height()));//设置控件大小
      ui->pageMusicList->setItemWidget(item,listItemBox);

      connect(listItemBox,&ListItemBox::setIsLike,this,[=](bool isLike){
          //更新歌曲状态
          //通知QQMusic，让likePage，localPage，recentPage更新页面歌曲信息
          emit updateLikeMusic(isLike,it->getMusicId());
      });
    }
    //触发窗口重绘
    //update();将paintEvent事件放在事件循环队列中，不立即处理
    repaint();//立即重绘(立即响应paintEvent事件)
}

QList<QUrl> CommonPage::musicUrls(MusicList &musicList) const
{
    QList<QUrl> urls;
    for(auto music:musicList)
    {
        switch (pageType) {
        case LIKEE_PAGE:
            if(music.getIsLike())
            {
                urls.append(music.getMusicUrl());
            }
            break;
        case LOCAL_PAGE:
            urls.append(music.getMusicUrl());
            break;
        case HISTORY_PAGE:
            if(music.getIsHistory())
            {
                urls.append(music.getMusicUrl());
            }
            break;
        default:
            qDebug()<<"未支持页面";
        }
    }
    return urls;
}

void CommonPage::setMusicImage(QPixmap pixmap)
{
    ui->musicImageLabel->setPixmap(pixmap);
    ui->musicImageLabel->setScaledContents(true);
}

QString CommonPage::getMusicIdByIndex(int index)
{
    if(index < 0 || index >= musicOfPage.size())
    {
        qDebug()<<"歌曲不存在";
        return {};
    }
    return musicOfPage[index];
}
