#include "recbox.h"
#include "ui_recbox.h"
#include "recboxitem.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox),
    row(1),
    col(4)
{
    ui->setupUi(this);

}

RecBox::~RecBox()
{
    delete ui;
}

void RecBox::initRecBoxUi(QJsonArray data, int row)
{
    if(row==2)
    {
        this->row=2;
        col=8;
    }
    else
    {
        ui->recListDown->hide();
    }

    imageList=data;

    currentIndex=0;
    count=imageList.size()/col;

    //在RecBox添加控件RecBoxItem
    createRecBoxItem();

}

void RecBox::createRecBoxItem()
{
    //删除RecBox之前的元素
    QList<RecBoxItem*> recUpList= ui->recListUp->findChildren<RecBoxItem*>();
    for(auto e:recUpList)
    {
        ui->recListUpHlayout->removeWidget(e);//从界面移除
        delete e;//new的对象释放掉
    }

    QList<RecBoxItem*> recDownList= ui->recListDown->findChildren<RecBoxItem*>();
    for(auto e:recDownList)
    {
        ui->recListDownLayout->removeWidget(e);//从界面移除
        delete e;//new的对象释放掉
    }

    //创建RecBoxItem对象，往RecBox添加
    //今日为你推荐：row=1,col=4,只显示1行
    //音乐补给站：row=2,col=8
    int index=0;
    for(int i=currentIndex*col;i<col+currentIndex*col;i++)
    {
        RecBoxItem* item=new RecBoxItem();
        //设置音乐图片与对应文本
        QJsonObject obj= imageList[i].toObject();//拿到imageList中第i个json对象
        item->setRecText(obj.value("text").toString());//设置对象文本
        item->setRecImage(obj.value("path").toString());//设置对象图片
        if(index>=col/2&&row==2)
        {
            ui->recListDownLayout->addWidget(item);

        }
        else
        {
            ui->recListUpHlayout->addWidget(item);
        }
        index++;

    }
}



void RecBox::on_btDown_clicked()
{
    //点击后显示下组图片，如果是最后一组图片显示第1组(下标0)
    currentIndex++;
    if(currentIndex>=count)
    {
        currentIndex=0;
    }
    currentIndex++;
    currentIndex%=count;
    createRecBoxItem();
}

void RecBox::on_btUp_clicked()
{
    currentIndex--;
    if(currentIndex<0)
    {
        currentIndex=count-1;
    }
    createRecBoxItem();
}
