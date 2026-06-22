#include "recboxitem.h"
#include "ui_recboxitem.h"
#include <QDebug>
#include <qpropertyanimation.h>

RecBoxItem::RecBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBoxItem)
{
    ui->setupUi(this);
    ui->musicImageBox->installEventFilter(this);
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
            QPropertyAnimation* animation =new QPropertyAnimation(ui->musicImageBox,"geometry");
            animation->setDuration(150);//设置动画持续时间
            animation->setStartValue(QRect(9,9,ui->musicImageBox->width(),ui->musicImageBox->height()));//起始帧
            animation->setEndValue(QRect(9,0,ui->musicImageBox->width(),ui->musicImageBox->height()));//结束帧
            animation->start();//启动动画效果
            connect(animation,&QPropertyAnimation::finished,this,[=](){
                delete animation;
            });//槽函数，动画结束后释放new的对象，不然每次鼠标进入都new新对象不释放会浪费


        }
        else if(QEvent::Leave==event->type())//鼠标离开图片框
        {

            //添加图片下移动画
            QPropertyAnimation* animation =new QPropertyAnimation(ui->musicImageBox,"geometry");
            animation->setDuration(150);//设置动画持续时间
            animation->setStartValue(QRect(9,0,ui->musicImageBox->width(),ui->musicImageBox->height()));//起始帧
            animation->setEndValue(QRect(9,9,ui->musicImageBox->width(),ui->musicImageBox->height()));//结束帧
            animation->start();//启动动画效果
            connect(animation,&QPropertyAnimation::finished,this,[=](){
                delete animation;
            });//槽函数，动画结束后释放new的对象，不然每次鼠标进入都new新对象不释放会浪费

        }
        return true;
    }
    return QObject::eventFilter(watched,event);
}

void RecBoxItem::setRecText(const QString &text)
{
    ui->recBoxItemText->setText(text);
}

void RecBoxItem::setRecImage(const QString &imagePath)
{
    QString style="background-image:url("+imagePath+");";
    ui->recMusicImage->setStyleSheet(style);
}
