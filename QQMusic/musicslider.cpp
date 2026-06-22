#include "musicslider.h"
#include "ui_musicslider.h"
#include<QMouseEvent>
MusicSlider::MusicSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicSlider)
{
    ui->setupUi(this);
    maxWidth=this->width();
    currentPos=0;
    moveSlider();
}

MusicSlider::~MusicSlider()
{
    delete ui;
}

void MusicSlider::setStep(float ratio)
{
    currentPos=maxWidth*ratio;
    moveSlider();
}

void MusicSlider::mousePressEvent(QMouseEvent *event)
{
    currentPos=event->pos().x();
    moveSlider();
}


void MusicSlider::mouseMoveEvent(QMouseEvent *event)
{
    QRect musicSliderRect=QRect(0,0,geometry().width(),geometry().height());
    if(!musicSliderRect.contains(event->pos()))
    {
        return;
    }


    //鼠标移动的时候，event->pos()必须在MusicSlider窗口内，才能支持拖拽功能
    if(event->buttons()==Qt::LeftButton)
    {
        currentPos=event->pos().x();
        if(currentPos<0)
        {
            currentPos=0;
        }
        if(currentPos>maxWidth)
        {
            currentPos=maxWidth;
        }
        moveSlider();
    }

}


void MusicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    currentPos=event->pos().x();
    moveSlider();
    emit setMusicSliderPosition(ui->outLine->width()/(float)maxWidth);
}

void MusicSlider::moveSlider()
{
    ui->outLine->setGeometry(ui->outLine->x(),ui->outLine->y(),currentPos,ui->outLine->height());
}
