#include "btform.h"
#include "ui_btform.h"
#include<QPropertyAnimation>
BtForm::BtForm(QWidget *parent) ://定义 BtForm 的构造函数。创建 BtForm 对象时，可传入其父组件 parent
    QWidget(parent),//调用父类 QWidget 的构造函数，把 parent 传进去。这样 Qt 会建立父子对象关系：父组件销毁时，会自动销毁其子组件。
    ui(new Ui::BtForm)//初始化成员变量 ui，为 Qt Designer 自动生成的界面类 Ui::BtForm 创建对象。
{
    ui->setupUi(this);

    //隐藏所有btform的动画效果
    ui->lineBox->hide();

   //设置line1动画效果
    line1Animal=new QPropertyAnimation(ui->line1,"geometry",this);//参数1：给line1设置动画效果 参数2：将来如何变化 参数3：当前对象的父对象
    line1Animal->setDuration(1500);//设置持续时间（毫秒）
    line1Animal->setKeyValueAt(0,QRect(0,15,2,0));//起始状态
    line1Animal->setKeyValueAt(0.5,QRect(0,2,2,15));//中间状态
    line1Animal->setKeyValueAt(1,QRect(0,15,2,0));//结束状态
    line1Animal->setLoopCount(-1);//循环
    line1Animal->start();

    //设置line2动画效果
     line2Animal=new QPropertyAnimation(ui->line2,"geometry",this);
     line2Animal->setDuration(1600);//设置持续时间（毫秒）
     line2Animal->setKeyValueAt(0,QRect(7,15,2,0));//起始状态
     line2Animal->setKeyValueAt(0.5,QRect(7,2,2,15));//中间状态
     line2Animal->setKeyValueAt(1,QRect(7,15,2,0));//结束状态
     line2Animal->setLoopCount(-1);//循环
     line2Animal->start();

     //设置line3动画效果
      line3Animal=new QPropertyAnimation(ui->line3,"geometry",this);
      line3Animal->setDuration(1700);//设置持续时间（毫秒）
      line3Animal->setKeyValueAt(0,QRect(14,15,2,0));//起始状态
      line3Animal->setKeyValueAt(0.5,QRect(14,2,2,15));//中间状态
      line3Animal->setKeyValueAt(1,QRect(14,15,2,0));//结束状态
      line3Animal->setLoopCount(-1);//循环
      line3Animal->start();

      //设置line4动画效果
       line4Animal=new QPropertyAnimation(ui->line4,"geometry",this);
       line4Animal->setDuration(1800);//设置持续时间（毫秒）
       line4Animal->setKeyValueAt(0,QRect(21,15,2,0));//起始状态
       line4Animal->setKeyValueAt(0.5,QRect(21,2,2,15));//中间状态
       line4Animal->setKeyValueAt(1,QRect(21,15,2,0));//结束状态
       line4Animal->setLoopCount(-1);//循环
       line4Animal->start();
}

BtForm::~BtForm()
{
    delete ui;
}

void BtForm::setIconAndText(const QString &btIcon, const QString &btText,int pageId)
{
    //设置按钮图标
    ui->btIcon->setPixmap(QPixmap(btIcon));

    //设置按钮文本
    ui->btTex->setText(btText);

    //将按钮和page页面进行关联
    this->pageId=pageId;
}

int BtForm::getPageId() const
{
    return pageId;
}

void BtForm::cleanBackground()
{
    //btStyle
    //点击其他btfrom按钮时，当前按钮颜色清除，但是保留鼠标悬停时的浅色
    ui->btStyle->setStyleSheet("#btStyle:hover{background-color:#E4F7F0;}");
}

//显示动画
void BtForm::showAnimal()
{
    ui->lineBox->show();
}

void BtForm::mousePressEvent(QMouseEvent *event)
{
    //当按钮按下，修改背景颜色
    ui->btStyle->setStyleSheet("#btStyle{background-color:#21CFA3;}");

    //当按钮按下，修改bodyRight中的page页面
    //1.什么时候切换？
    //2.由谁切换？
    //3.按钮和page页面的对应关系？
    emit btClick(pageId);//鼠标点击btform，发送信号切换页面

}
