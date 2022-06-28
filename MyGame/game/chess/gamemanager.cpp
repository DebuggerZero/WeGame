#include "game/chess/gamemanager.h"

extern int boardBackground[8][8];

extern bool KillKing;

GameManager::GameManager()
{
}


void GameManager::InitBoard()
{
    KillKing=false;
    board[0][0]=BlackRook*10+numu[0];board[7][0]=BlackRook*10+numu[1];
    board[1][0]=BlackKnight*10+numu[0];board[6][0]=BlackKnight*10+numu[1];
    board[2][0]=BlackBishop*10+numu[0];board[5][0]=BlackBishop*10+numu[1];
    board[3][0]=BlackQueen*10;
    board[4][0]=BlackKing*10;
    for(int i=0;i<8;++i)
        board[i][1]=BlackPawn*10+numu[i];

    board[0][7]=WhiteRook*10+numu[0];board[7][7]=WhiteRook*10+numu[1];
    board[1][7]=WhiteKnight*10+numu[0];board[6][7]=WhiteKnight*10+numu[1];
    board[2][7]=WhiteBishop*10+numu[0];board[5][7]=WhiteBishop*10+numu[1];
    board[3][7]=WhiteQueen*10;
    board[4][7]=WhiteKing*10;
   for(int i=0;i<8;++i)
       board[i][6]=WhitePawn*10+numu[i];

   for(int i=0;i<8;++i){
       board[i][2]=0;
       board[i][3]=0;
       board[i][4]=0;
       board[i][5]=0;

       if(pw) {
           delete pw;
           pw= new GamePlayer();
       }
   }
}

// piece value
// new x y
void GameManager::PlayerMove(int value,int x,int y)
{
    int pl=value/100;//player

    if(pw->waction){
        // w player move
      if(!SelectMove(x,y,pl)) return;
     pw->waction=false;
     pw->thisShow=2;
     canWin(pl);
     delete piece;

     qDebug()<<piece;
    }else if(pw->baction){

     //b player move
     if(!SelectMove(x,y,pl)) return;

     pw->baction=false;
     pw->thisShow=1;
     canWin(pl);
     delete piece;
    }
}

void GameManager::canWin(int player)
{

    if(KillKing){
       QMessageBox::information(NULL,QString("end"),player==1?QString("WhiteKing WIN"):QString("BlackKing WIN"));
       InitBoard();
        //死亡
    }else{
        qDebug()<<"continue";
    }
}

QString GameManager::PieceName(int player,int value)
{
    QString prefix="";
    int i=0;
    for(i=0;i<6;++i)
    {
        if(numValue[i]==value/10%10){
           prefix=strValue[i];
            break;
        }
    }
    return prefix;
}

int** GameManager::arrStep(QString prefix)
{
    int **a=nullptr;
    if(prefix=="") return a;
    int i=0;
    for(i=0;i<6;++i)
    {
        if(prefix==strValue[i])break;
    }
    switch (i) {
    case 0:
        a=pw->PawnStep;
        break;
    case 1:
        a=pw->RookStep;
        break;
    case 2:
        a=pw->KnightStep;
        break;
    case 3:
        a=pw->BishopStep;
        break;
    case 4:
        a=pw->QueenStep;
        break;
    case 5:
        a=pw->KingStep;
        break;
    default :
        return a;
        break;
    }
    return a;
}

int **GameManager::nextarrStep(QString prefix)
{
    int **a=nullptr;
    if(prefix=="") return a;
    int i=0;
    for(i=0;i<6;++i)
    {
        if(prefix==strValue[i])break;
    }
    switch (i) {
    case 0:
        a=pw->Step;
        break;
    case 1:
        a=pw->Step;
        break;
    case 2:
        a=pw->Step;
        break;
    case 3:
        a=pw->Step;
        break;
    case 4:
        a=pw->Step;
        break;
    case 5:
        a=pw->RookStep;
        break;
    default :
        return a;
        break;
    }
    return a;
}

// new value
bool GameManager::SelectMove(int x, int y, int pl)
{
    qDebug()<<"piece："<<piece;
    qDebug()<<"pl："<<pl;

    if(!arrStep(PieceName(pl,piece->GetValue()))) return false;
    if(!nextarrStep(PieceName(pl,piece->GetValue()))) return false;

    if(piece->canMove(pl,&board[0],arrStep(PieceName(pl,piece->GetValue()))
            ,nextarrStep(PieceName(pl,piece->GetValue())),x,y))

        return true;
    else
    {
        qDebug()<<"can't move";
        return false;
        }


}

Chess* GameManager::GetChaPiece(int value,int x,int y)
{


    // if piece isnot nullptr: return piece else Init piece
    if(value%100/10==9){
       return new King(x,y,value,pw->KingStep[value/100-1][0]);
    }else if(value%100/10==8) {
        new Queen(x,y,value,pw->QueenStep[value/100-1][0]);
    }else if(value%100/10==7){
       return new Bishop(x,y,value,pw->BishopStep[value/100-1][value%10]);
    }else if(value%100/10==6){
      return  new Knight(x,y,value,pw->KnightStep[value/100-1][value%10]);
    }else if(value%100/10==5){
        return  new Rook(x,y,value,pw->RookStep[value/100-1][value%10]);
    }else{
       return new Pawn(x,y,value,pw->PawnStep[value/100-1][value%10]);
    }
}
