#include "game/chess/gameplayer.h"

GamePlayer::GamePlayer()
{
    thisShow=1;
    waction=false;
    baction=false;

    KingStep=new int*[2]();
    PawnStep=new int*[2]();
    BishopStep=new int*[2]();
    KnightStep=new int*[2]();
    RookStep=new int*[2]();
    QueenStep=new int*[2]();
    Step=new int *[2]();
    for(int i=0;i<2;++i){
    KingStep[i]={new int[1]()};
    QueenStep[i]={new int[1]()};
    RookStep[i]={new int[2]()};
    BishopStep[i]={new int[2]()};
    KnightStep[i]={new int[2]()};
    PawnStep[i]={new int[8]()};
    Step[i]={new int [0]};
    }
 //int *array = new int[m]; for(i) array[i] = new int[n];



}
