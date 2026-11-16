#ifndef RECBOXITEM_H
#define RECBOXITEM_H

#include "onlinetrack.h"

#include <QNetworkAccessManager>
#include <QWidget>

namespace Ui {
class RecBoxItem;
}

class RecBoxItem : public QWidget
{
    Q_OBJECT

public:
    explicit RecBoxItem(QWidget *parent = nullptr);
    ~RecBoxItem();
    bool eventFilter(QObject *watched, QEvent *event);

    void setTrack(const OnlineTrack &track);

signals:
    void playRequested(const OnlineTrack &track);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::RecBoxItem *ui;
    OnlineTrack currentTrack;
    QNetworkAccessManager coverManager;
};

#endif // RECBOXITEM_H
