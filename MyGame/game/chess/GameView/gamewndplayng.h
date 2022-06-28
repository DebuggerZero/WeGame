#ifndef GAMEWNDPLAYNG_H
#define GAMEWNDPLAYNG_H

#include <QWidget>

#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QMouseEvent>
#include "game/chess/gamemanager.h"

#include "Archive/archive.h"
namespace Ui {
class GameWndPlayng;
}

class GameWndPlayng : public QWidget,public GameManager
{
    Q_OBJECT

public:
   explicit GameWndPlayng(QWidget *parent = nullptr);
    ~GameWndPlayng();

    void Init();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent* );

signals:
    void windowsClose();

private:
    Ui::GameWndPlayng *ui;

    Archive _archive;
};

#endif // GAMEWNDPLAYNG_H
