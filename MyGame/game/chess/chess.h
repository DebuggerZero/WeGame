#ifndef CHESS_H
#define CHESS_H

#include <QPoint>
#include <QString>


const int BlackKing =29;
const int BlackQueen = 28;
const int BlackBishop = 27;
const int BlackKnight = 26;
const int BlackRook = 25;
const int BlackPawn = 24;

const int WhiteKing =19;
const int WhiteQueen =18;
const int WhiteBishop =17;
const int WhiteKnight =16;
const int WhiteRook =15;
const int WhitePawn=14;

const QString strValue[6]={"Pawn","Rook","Knight","Bishop","Queen","King"};

const int numValue[6]={4,5,6,7,8,9};

const int numu[8]={0,1,2,3,4,5,6,7};


class Chess
{
public:

     Chess();
     virtual ~Chess(){}
    // can piece move to target location ?
    virtual bool canMove(int,int(*)[8],int(**),int(**),int,int)=0;
     //
     virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**))=0;
    // can piece promtion after this move ?
    void promotion(int,int,int (*)[8]);
    int GetX();
    int GetY();
    int GetValue();
    int GetStep();
    bool GetMove_();
    void SetStep(int);

protected:
    int value_;
    int x_;
    int y_;
    int valStep_;
    bool move_;
};

class Pawn:public Chess{
public:
    Pawn(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~Pawn(){}
};

class King:public Chess{
public:
    King(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~King(){}
};

class Queen:public Chess{
public:
    Queen(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~Queen(){}
};

class Bishop:public Chess{
public:
    Bishop(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~Bishop(){}
};

class Rook:public Chess{
public:
    Rook(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~Rook(){}
};

class Knight:public Chess{
public:
    Knight(int,int,int,int);
    virtual  bool canMove(int,int(*)[8],int(**),int(**),int,int);
    virtual bool isHaveMoveRoad(int,int(*)[8],int(**),int(**));
    virtual~Knight(){}
};

#endif // CHESS_H
