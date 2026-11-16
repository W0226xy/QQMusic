#ifndef RECBOX_H
#define RECBOX_H

#include "onlinetrack.h"

#include <QWidget>
namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();
    void initRecBoxUi(int row);
    void setTracks(const QList<OnlineTrack> &tracks);

signals:
    void playRequested(const OnlineTrack &track);
private slots:
    void on_btDown_clicked();

    void on_btUp_clicked();

private:
    void createRecBoxItem();

private:
    Ui::RecBox *ui;
    int row;
    int col;
    QList<OnlineTrack> tracks;
    int currentIndex;//标记当前显示第几组图片
    int count;//标记图片总组数

};

#endif // RECBOX_H
