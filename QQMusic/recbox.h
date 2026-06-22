#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include<QJsonArray>
namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();
    //初始化
    void initRecBoxUi(QJsonArray data,int row);


private slots:
    void on_btDown_clicked();

    void on_btUp_clicked();

private:
    void createRecBoxItem();

private:
    Ui::RecBox *ui;
    int row;
    int col;
    QJsonArray imageList;
    int currentIndex;//标记当前显示第几组图片
    int count;//标记图片总组数

};

#endif // RECBOX_H
