#include "lrcpage.h"
#include "ui_lrcpage.h"
#include<QFile>
#include<QDebug>
LrcPage::LrcPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LrcPage)
{
    ui->setupUi(this);
    //设置窗口无标题栏
    setWindowFlag(Qt::FramelessWindowHint);
    //下拉按钮关联clicked
    connect(ui->hideBtn,&QPushButton::clicked,this,[=]{
        this->hide();
    });

    ui->hideBtn->setIcon(QIcon(":/images/xiala.png"));

}

LrcPage::~LrcPage()
{
    delete ui;
}

bool LrcPage::parseLrcFile(const QString &lrcFilePath)
{
    clearLyrics();
    //1.打开文件
    QFile file(lrcFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开lrc文件"<<lrcFilePath<<"失败";
        return false;
    }

    //一次性读取一行歌词
    while(!file.atEnd())
    {
        QString lrclineWord= file.readLine(1024);
        //解析歌词，歌词类型如下
        //[0:17.94]那些失眠的人啊 你现在还好吗
        //[0:33.600.00]比2002年来的更晚一些

        //1.先解析出时间和歌词的字符串文本，按照']'分割
        int start=0,end=0;
        end=lrclineWord.indexOf(']',start);//找到‘]’的位置
        QString lrcTime= lrclineWord.mid(start,end-start+1);//截取时间0:17.94
        QString lrcWord= lrclineWord.mid(end+1,lrclineWord.size()-end-1-1);//截取文本
        //2.在时间中解析出分:秒.毫秒
        //分
        qint64 lineTime=0;
        start=1;
        end=lrcTime.indexOf(':',start);
        lineTime+=lrcTime.mid(start,end-start).toInt()*60*1000;//解析 分，并将其转换为毫秒

        //秒
        start=end+1;
        end=lrcTime.indexOf('.',start);
        lineTime+=lrcTime.mid(start,end-start).toInt()*1000;//解析 秒，并将其转换为毫秒

        //解析毫秒
        start=end+1;
        end=lrcTime.indexOf('.',start);
        lineTime+=lrcTime.mid(start,end-start).toInt();//解析毫秒


        //3.将该行再次保存
        lrcWordLines.push_back(LrcWordLine(lineTime,lrcWord));
    }

    for(auto e:lrcWordLines)
    {
        qDebug()<<e.lrcTime<<":"<<e.lrcText;
    }
    return true;
}

void LrcPage::clearLyrics()
{
    lrcWordLines.clear();
    showLrcWordLine(0);
}

void LrcPage::showLrcWordLine(qint64 time)
{
    //1.根据当前所唱歌曲时间来获取当前所唱歌曲在QVector中的索引
    int index=getLrcWordLineIndex(time);
    //2.更新当前行的前3行，当前播放行，后3行歌词到页面
    if(index==-1)
    {

        ui->line1->setText("");
        ui->line2->setText("");
        ui->line3->setText("");
        ui->lineCenter->setText("当前歌曲暂无歌词");
        ui->line4->setText("");
        ui->line5->setText("");
        ui->line6->setText("");
    }
    else
    {
        ui->line1->setText(getLrcWordByIndex(index-3));
        ui->line2->setText(getLrcWordByIndex(index-2));
        ui->line3->setText(getLrcWordByIndex(index-1));
        ui->lineCenter->setText(getLrcWordByIndex(index));
        ui->line4->setText(getLrcWordByIndex(index+1));
        ui->line5->setText(getLrcWordByIndex(index+2));
        ui->line6->setText(getLrcWordByIndex(index+3));
    }
}

int LrcPage::getLrcWordLineIndex(qint64 time)
{
    //将time和QVector中保存的LrcWordLine中的time进行对比
    if(lrcWordLines.isEmpty())//当前歌曲没有lrc歌词文件
    {
        return -1;
    }
    if(time<lrcWordLines[0].lrcTime)
    {
        return 0;
    }

    for(int i=1;i<lrcWordLines.size();i++)
    {
        if(time>lrcWordLines[i-1].lrcTime&&time<lrcWordLines[i].lrcTime)
        {
            //第i-1行还没有播放完
            return i-1;
        }
    }
    //最后一行唱完之后，歌曲结束了，还有后续音乐，让歌曲界面显示最后一行歌词
    return lrcWordLines.size()-1;
}

QString LrcPage::getLrcWordByIndex(int index)
{
    if(index<0||index>=lrcWordLines.size())
    {
        return "";
    }

    return lrcWordLines[index].lrcText;
}


