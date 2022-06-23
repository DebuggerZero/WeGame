#ifndef GSTARTWINDOW_H
#define GSTARTWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QStyleOption>

#include "game/Gobang/GameView/gmainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GStartWindow; }
QT_END_NAMESPACE

class GStartWindow : public QWidget
{
    Q_OBJECT

public:
    GStartWindow(QWidget *parent = nullptr);
    ~GStartWindow();

    void paintEvent(QPaintEvent* event) override;

signals:
    void windowsClose();

private:
    Ui::GStartWindow *ui;

    GMainWindow *gMainWindow;
};
#endif // GSTARTWINDOW_H
