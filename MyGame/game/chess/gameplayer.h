#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H


class GamePlayer
{
public:
    GamePlayer();

    int thisShow;
    bool waction;
    bool baction;
    //pieces step
    int **PawnStep;
    int **KingStep;
    int **QueenStep;
    int **BishopStep;
    int **KnightStep;
    int **RookStep;
    //
    int **Step;

};

#endif // GAMEPLAYER_H
