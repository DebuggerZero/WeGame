#ifndef GAMEWNDSTRAT_H
#define GAMEWNDSTRAT_H

#include <QWidget>
#include "game/chess/GameView/gamewndplayng.h"

namespace Ui {
class GameWndStrat;
}

class GameWndStrat : public QWidget
{
    Q_OBJECT

public:
    explicit GameWndStrat(QWidget *parent = nullptr);
    ~GameWndStrat();
    void closeEvent(QCloseEvent* );

signals:
    void windowsClose();

private slots:

private:
    Ui::GameWndStrat *ui;
    GameWndPlayng *Gamewndplay;
};

#endif // GAMEWNDSTRAT_H
