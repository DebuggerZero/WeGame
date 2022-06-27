#ifndef GMAINWINDOW_H
#define GMAINWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include <QPainterPath>
#include <QListWidget>
#include <QMessageBox>
#include <QTimer>

#include "game/Gobang/piece.h"
#include "game/Utility/utility.h"
#include "archive/archive.h"

namespace Ui {
class GMainWindow;
}

class GMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GMainWindow(QWidget *parent = nullptr);
    ~GMainWindow();

    const int MSGLIST_X = 630;
    const int MSGLIST_Y = 20;
    const int MSGLIST_WIDTH = 140;
    const int MSGLIST_HEIGHT = 200;

    const int GAMEMAP_WIDTH = 602;
    const int GAMEMAP_HEIGHT = 600;

    const int STEPMSG_X = 700;
    const int STEPMSG_Y = 230;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void initWindow();

    QPixmap drawGameMap(int x, int y);

signals:
    void windowClose();

private:
    Ui::GMainWindow *ui;

    Piece _piece;

    QPixmap _frame;

    QPixmap _rim;

    int _mouseX, _mouseY, _step;

    Archive _archive;

    QTimer* _timer;

    QListWidget* _messageList;
};
#endif // GMAINWINDOW_H
