#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <QPainter>
#include "game/chess/chess.h"
#include "game/chess/gameplayer.h"
#include <QMessageBox>


class GameManager
{

public:
    GameManager();

protected:
    void InitBoard();
    void PlayerMove(int,int,int);
    void pp(int (*board)[8]);
    void canWin(int);
    QString PieceName(int,int);
    int** arrStep(QString);
    int** nextarrStep(QString);
    bool SelectMove(int,int,int);
    Chess* GetChaPiece(int,int,int);

    Chess *piece=nullptr;
    GamePlayer *pw=nullptr;
    int board[8][8];


};

#endif // GAMEMANAGER_H
