#include "recbox.h"
#include "ui_recbox.h"
#include "recboxitem.h"
#include <QLabel>
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

void RecBox::initRecBoxUi(int row)
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
    currentIndex=0;
    count=0;
    createRecBoxItem();
}

void RecBox::setTracks(const QList<OnlineTrack> &tracks)
{
    this->tracks = tracks;
    currentIndex = 0;
    count = tracks.isEmpty() ? 0 : (tracks.size() + col - 1) / col;
    ui->btUp->setVisible(count > 1);
    ui->btDown->setVisible(count > 1);
    createRecBoxItem();
}

void RecBox::createRecBoxItem()
{
    auto clearLayout = [](QLayout *layout) {
        while (QLayoutItem *layoutItem = layout->takeAt(0)) {
            delete layoutItem->widget();
            delete layoutItem;
        }
    };
    clearLayout(ui->recListUpHlayout);
    clearLayout(ui->recListDownLayout);

    if (tracks.isEmpty()) {
        QLabel *emptyLabel = new QLabel(QStringLiteral("暂无在线推荐"), ui->recListUp);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet(QStringLiteral("color: #888888;"));
        ui->recListUpHlayout->addWidget(emptyLabel);
        return;
    }

    int index=0;
    const int begin = currentIndex * col;
    const int end = qMin(begin + col, tracks.size());
    for(int i = begin; i < end; ++i)
    {
        RecBoxItem* item=new RecBoxItem(this);
        item->setTrack(tracks.at(i));
        connect(item, &RecBoxItem::playRequested, this, &RecBox::playRequested);
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
    if (count <= 1)
        return;
    currentIndex = (currentIndex + 1) % count;
    createRecBoxItem();
}

void RecBox::on_btUp_clicked()
{
    if (count <= 1)
        return;
    currentIndex = (currentIndex - 1 + count) % count;
    createRecBoxItem();
}
