#ifndef GSTARTWIDGHT_H
#define GSTARTWIDGHT_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>

#include "game/Snake/GameView/gmainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GStartWidght; }
QT_END_NAMESPACE

class GStartWidght : public QWidget
{
    Q_OBJECT

public:
    GStartWidght(QWidget *parent = nullptr);
    ~GStartWidght();

    void paintEvent(QPaintEvent* event);

signals:
    void windowsClose();

private:
    Ui::GStartWidght *ui;

    GMainWidget *_gMainWidget;

    QPixmap _backGround;
    QPixmap _title;
};
#endif // GSTARTWIDGHT_H
