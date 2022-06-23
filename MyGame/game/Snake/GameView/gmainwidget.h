#ifndef GMAINWIDGET_H
#define GMAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QDateTime>
#include <QMessageBox>
#include <QPainterPath>
#include <QTimer>

#include "game/Snake/Area.h"

namespace Ui {
class GMainWidget;
}

class GMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GMainWidget(QWidget *parent = nullptr);
    ~GMainWidget();

    void paintEvent(QPaintEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void closeWindows();

private:
    Ui::GMainWidget *ui;

    QPixmap _backGround;

    QPixmap createMap(int width, int height);

    Area *area;

    QDateTime _moveStartTime;

    QDateTime _foodStartTime;

    void init();

    Utility _utility;

    QTimer *_timer;

    int _speed;
};

#endif // GMAINWIDGET_H
