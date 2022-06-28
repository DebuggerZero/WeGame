#include "game/chess/chess.h"


int boardBackground[8][8]={{0}};//提示作用
bool KillKing=false;
Chess::Chess()
{

}




int Chess::GetX()
{
    return x_;
}


int Chess::GetY()
{
    return y_;
}


int Chess::GetValue()
{
    return value_;
}

int Chess::GetStep()
{
    return valStep_;
}

bool Chess::GetMove_()
{
    return move_;
}

void Chess::SetStep(int step)
{
    valStep_=step;
}

Pawn::Pawn(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;
}

 bool Pawn::canMove(int player,int(*board)[8],int(**PawnStep),int(**Step),int x,int y)
{
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;

    //move function


    int u1=player==1?-1:1;
    int u2=player==1?-2:2;

    //1 .step==0
    if(!valStep_&&(x==x_))
    {
        if((y==y_+u1&&!board[x][y])
                ||(y==y_+u2&&!board[x][y_+u1]&&!board[x][y_+u2])) {
            board[x][y] =board[x_][y_];
            board[x_][y_]=0;
            ++PawnStep[player-1][value_%10];
            move_=true;

            return true;
        }
    }
    //2. step>0
     if((y==y_+u1&&x==x_&&!board[x][y])){
        board[x][y] =board[x_][y_];
        board[x_][y_]=0;
         ++PawnStep[player-1][value_%10];

        move_=true;
        return true;
    }
    //3. eat other piece which other character piece
    //3.1 normal
     if((y==y_+u1&&(x==x_+1||x==x_-1)
        &&board[x][y]&&board[x][y]/100!=player)) {

        if(board[x][y]==290||board[x][y]==190) KillKing=true;

        board[x][y] =board[x_][y_];
        board[x_][y_]=0;
        ++PawnStep[player-1][value_%10];


        move_=true;

        return true;
    }
    //3.2 special
    if(y==y_+u1&&(x==x_-1||x==x_+1)&&
            PawnStep[player==1?2-1:1-1][x]==1&&board[x][y_]&&board[x][y_]/100!=player){

        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        board[x][y_]=0;
        ++PawnStep[player-1][value_%10];
        move_=true;
        return true;
    }

    return false;
 }

 bool Pawn::isHaveMoveRoad(int player, int (*board)[8],int(**PawnStep),int(**Step))
 {

     int u1=player==1?-1:1;
     int u2=player==1?-2:2;
     int utemp=0;
     if(!board[x_][y_+u1]){
        boardBackground[x_][y_+u1]=1;
        ++utemp;
     }
     if(!valStep_&&!board[x_][y_+u1]&&!board[x_][y_+u2]){
         boardBackground[x_][y_+u2]=1;
         ++utemp;
     }

     if(x_+1<8&&PawnStep[player==1?2-1:1-1][x_+1]==1&&board[x_+1][y_]&&board[x_+1][y_]/100!=player){
        boardBackground[x_+1][y_+u1]=1;
        ++utemp;
     }
     if(x_-1>=0&&PawnStep[player==1?2-1:1-1][x_-1]==1&&board[x_-1][y_]&&board[x_-1][y_]/100!=player){
         boardBackground[x_-1][y_+u1]=1;
         ++utemp;
     }
     if(board[x_-1][y_+u1]&&board[x_-1][y_+u1]/100!=player)
     {
         boardBackground[x_-1][y_+u1]=1;
         ++utemp;
     }
     if(board[x_+1][y_+u1]&&board[x_+1][y_+u1]/100!=player){
         boardBackground[x_+1][y_+u1]=1;
         ++utemp;
    }

     if(!utemp) return false;
     else return true;
 }



King::King(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;
}

 bool King::canMove(int player,int(*board)[8],int(**KingStep),int(**RookStep),int x,int y)
{

    //exclude any
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;

    //move function

    // if step==0 :have speical protection method
    //判断 路径被吃王，正在被吃王 不可
    int u=x<x_?0:1;
    if(!valStep_&&y==y_&&(x==x_-2||x==x_+2)&&!KingStep[player-1][0]
            &&!RookStep[player-1][u]){
        for(int i=u==0?x_-1:x_+1;u==0?i>0:i<7;u==0?--i:++i)
              if(board[i][y])  return false;

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        board[u==0?x+1:x-1][y]=board[u==0?0:7][y];
        board[u==0?0:7][y]=0;
        ++KingStep[player-1][0];
        move_=true;
        return true;
    }
    // step !=0
    if((x>=x_-1&&x<=x_+1)&&(y>=y_-1&&y<=y_+1)&&player!=board[x][y]/100)
    {

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++KingStep[player-1][0];

        move_=true;
        return true;
    }
    else return false;

 }

 bool King::isHaveMoveRoad(int player, int (*board)[8],int(**KingStep),int(**RookStep))
 {
     int utemp=0;
     int i=0;

     if(!valStep_&&!KingStep[player-1][0]&&!RookStep[player-1][0])
     {
         for(i=x_;i<7;++i)
         {
             if(!(board[i][y_]/100==player)){
                 boardBackground[i][y_]=1;
                 ++utemp;
                 if(board[i][y_]) break;
             }
             else break;
         }
         for(i=x_;i>0;--i)
         {
             if(!(board[i][y_]/100==player)){
                 boardBackground[i][y_]=1;
                  ++utemp;
                 if(board[i][y_]) break;
             }
             else break;
         }
     }

     for(int i=x_-1;i<=x_+1;++i)
     {
         for(int j=y_-1;j<=y_+1;++j)
         {
             if((i>=0&&i<8)&&(j>=0&&j<8)&&!(board[i][j]/100==player)){
                 boardBackground[i][j]=1;
                 ++utemp;
             }
         }
     }

    if(!utemp) return false;
    else return true;

 }



Queen::Queen(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;

}

bool Queen::canMove(int player, int(*board)[8],int(**QueenStep),int(**Step),int x,int y)
{
    //exclude any
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;


    //move function
    int ux=x>x_?x-x_:x_-x;
    int uy=y>y_?y-y_:y_-y;
    int uplayer=player==1?2:1;
    if(ux==uy)
    {
        int uux=x>x_?-1:1;
        int uuy=y>y_?-1:1;
        for(int u=0,i=x,j=y;u<ux;j+=uuy,i+=uux,++u)
             if(board[i][j]/100==player){
                 return false;
             }
        for(int u=1,i=x+uux,j=y+uuy;u<ux;j+=uuy,i+=uux,++u)
             if(board[i][j]/100==uplayer){
                 return false;
             }

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++QueenStep[player-1][value_%10];

        move_=true;
        return true;
    }
    if(y==y_){
        for(int i=x;x<x_?i<x_:i>x_;x<x_?++i:--i)
             if(board[i][y]/100==player) return false;

        int uplayer= player==1?2:1;
        int ux=x<x_?x+1:x-1;

        for(int i=ux;ux<x_?i<x_:i>x_;ux<x_?++i:--i)
             if(board[i][y]/100==uplayer) return false;

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++QueenStep[player-1][value_%10];

        move_=true;
        return true;
    }
     if(x==x_)
    {
         for(int i=y;y<y_?i<y_:i>y_;y<y_?++i:--i)
             if(board[x][i]/100==player) return false;

         int uplayer= player==1?2:1;
         int uy=y<y_?y+1:y-1;

         for(int i=uy;uy<y_?i<y_:i>y_;uy<y_?++i:--i)
              if(board[x][i]/100==uplayer) return false;

         if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++QueenStep[player-1][value_%10];

        move_=true;
        return true;
    }

     else return false;
}

bool Queen::isHaveMoveRoad(int player, int(*board)[8],int(**QueenStep),int(**Step))
{
    int utemp=0;
    for(int i=x_-1,j=y_-1;j>=0&&i>=0;--i,--j){ //1
        if(i<8&&j<8&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

        }
       else break;
    }
    for(int i=x_-1,j=y_+1;i>=0&&j<8;--i,++j){//2
        if(i<8&&j>=0&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

           }

       else break;
    }
    for(int i=x_+1,j=y_-1;i<8&&j>=0;++i,--j){//3
        if(i>=0&&j<8&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;


        }
       else break;
    }
    for(int i=x_+1,j=y_+1;i<8&&j<8;++i,++j){//4
        if(i>=0&&j>=0&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

        }
       else break;
    }
    for(int i=x_+1;i<8;++i)
    {
        if(i>=0&&!(board[i][y_]/100==player))
        {
            boardBackground[i][y_]=1;
            ++utemp;

            if(board[i][y_]) break;

        }
       else break;
    }

    for(int i=x_-1;i>=0;--i)
    {
        if(i<8&&!(board[i][y_]/100==player))
        {
            boardBackground[i][y_]=1;
            ++utemp;

            if(board[i][y_]) break;

        }
       else break;
    }

    for(int i=y_-1;i>=0;--i)
    {
        if(i<8&&!(board[x_][i]/100==player))
        {
            boardBackground[x_][i]=1;
            ++utemp;

            if(board[x_][i]) break;

         }

       else break;

    }
    for(int i=y_+1;i<8;++i)
    {
        if(i>=0&&!(board[x_][i]/100==player))
        {
            boardBackground[x_][i]=1;
            ++utemp;

            if(board[x_][i]) break;

        }
       else break;
    }

    if(!utemp) return false;
    else return true;
}



Bishop::Bishop(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;

}

bool Bishop::canMove(int player, int(*board)[8],int(**BishopStep),int(**Step),int x,int y)
{


    //exclude any
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;


    //move function

    int ux=x>x_?x-x_:x_-x;
    int uy=y>y_?y-y_:y_-y;
    int uplayer=player==1?2:1;
    if(ux==uy)
    {
        int uux=x>x_?-1:1;
        int uuy=y>y_?-1:1;
        for(int u=0,i=x,j=y;u<ux;j+=uuy,i+=uux,++u)
             if(board[i][j]/100==player){
                 return false;
             }
        for(int u=1,i=x+uux,j=y+uuy;u<ux;j+=uuy,i+=uux,++u)
             if(board[i][j]/100==uplayer){
                 return false;
             }

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++BishopStep[player-1][value_%10];

        move_=true;
        return true;
    }

    else return false;
}

bool Bishop::isHaveMoveRoad(int player, int(*board)[8],int(**BishopStep),int(**Step))
{
    int utemp=0;
    for(int i=x_-1,j=y_-1;j>=0&&i>=0;--i,--j){ //1
        if(i<8&&j<8&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

        }
       else break;
    }
    for(int i=x_-1,j=y_+1;i>=0&&j<8;--i,++j){//2
        if(i<8&&j>=0&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

           }

       else break;
    }
    for(int i=x_+1,j=y_-1;i<8&&j>=0;++i,--j){//3
        if(i>=0&&j<8&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;

           if(board[i][j]) break;

        }
       else break;
    }
    for(int i=x_+1,j=y_+1;i<8&&j<8;++i,++j){//4
        if(i>=0&&j>=0&&!(board[i][j]/100==player)){
           boardBackground[i][j]=1;
           ++utemp;
           if(board[i][j]) break;

        }
       else break;
    }

    if(utemp==0) return false;
    else return true;

}


Rook::Rook(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;

}

bool Rook::canMove(int player, int(*board)[8],int(**RookStep),int(**Step),int x,int y)
{
    //exclude any
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;
    //move function


    if(y==y_){
        for(int i=x;x<x_?i<x_:i>x_;x<x_?++i:--i)
             if(board[i][y]/100==player) return false;

        int uplayer= player==1?2:1;
        int ux=x<x_?x+1:x-1;

        for(int i=ux;ux<x_?i<x_:i>x_;ux<x_?++i:--i)
             if(board[i][y]/100==uplayer) return false;

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++RookStep[player-1][value_%10];

        move_=true;
        return true;
    }
     if(x==x_)
    {
         for(int i=y;y<y_?i<y_:i>y_;y<y_?++i:--i)
             if(board[x][i]/100==player) return false;

         int uplayer= player==1?2:1;
         int uy=y<y_?y+1:y-1;

         for(int i=uy;uy<y_?i<y_:i>y_;uy<y_?++i:--i)
              if(board[x][i]/100==uplayer) return false;

         if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;
        ++RookStep[player-1][value_%10];

        move_=true;
        return true;
    }
     return false;
}

bool Rook::isHaveMoveRoad(int player, int(*board)[8],int(**RookStep),int(**Step))
{

    int utemp=0;
    for(int i=x_+1;i<8;++i)
    {
        if(i>=0&&!(board[i][y_]/100==player))
        {
            boardBackground[i][y_]=1;
            ++utemp;

            if(board[i][y_]) break;

        }
       else break;
    }

    for(int i=x_-1;i>=0;--i)
    {
        if(i<8&&!(board[i][y_]/100==player))
        {
            boardBackground[i][y_]=1;
            ++utemp;

            if(board[i][y_]) break;

        }
       else break;
    }

    for(int i=y_-1;i>=0;--i)
    {
        if(i<8&&!(board[x_][i]/100==player))
        {
            boardBackground[x_][i]=1;
            ++utemp;

            if(board[x_][i]) break;

         }

       else break;

    }
    for(int i=y_+1;i<8;++i)
    {
        if(i>=0&&!(board[x_][i]/100==player))
        {
            boardBackground[x_][i]=1;
            ++utemp;

            if(board[x_][i]) break;

        }
       else break;
    }

    if(!utemp) return false;
    else return true;
}



Knight::Knight(int x, int y,int value,int valStep)
{
    x_=x;
    y_=y;
    value_=value;
    valStep_=valStep;
    move_=false;

}

bool Knight::canMove(int player,int(*board)[8],int(**RookStep),int(**Step),int x,int y)
{

    //exclude any
    if((x_==x&&y_==y)||player==board[x][y]/100) return false;
    //move function

    int ux=x>x_?x-x_:x_-x;
    int uy=y>y_?y-y_:y_-y;

    if(ux*uy==2&&board[x][y]/100!=player){

        if(board[x][y]==290||board[x][y]==190) KillKing=true;
        board[x][y]=board[x_][y_];
        board[x_][y_]=0;

        move_=true;
        return true;
    }
    else return false;
}

bool Knight::isHaveMoveRoad(int player,int(*board)[8],int(**RookStep),int(**Step))
{
    int utemp=0;
    if((x_+2>=0&&x_+2<8)&&(y_-1>=0&&y_-1<8)&&board[x_+2][y_-1]/100!=player){
        boardBackground[x_+2][y_-1]=1;
        ++utemp;
    }
    if((x_+2>=0&&x_+2<8)&&(y_+1>=0&&y_+1<8)&&board[x_+2][y_+1]/100!=player){
        boardBackground[x_+2][y_+1]=1;
        ++utemp;
    }

    if((x_-1>=0&&x_-1<8)&&(y_+2>=0&&y_+2<8)&&board[x_-1][y_+2]/100!=player){
        boardBackground[x_-1][y_+2]=1;
        ++utemp;
    }
    if((x_+1>=0&&x_+1<8)&&(y_+2>=0&&y_+2<8)&&board[x_+1][y_+2]/100!=player){
        boardBackground[x_+1][y_+2]=1;
        ++utemp;
    }
    if((x_-2>=0&&x_-2<8)&&(y_-1>=0&&y_-1<8)&&board[x_-2][y_-1]/100!=player){
        boardBackground[x_-2][y_-1]=1;
        ++utemp;
    }
    if((x_-2>=0&&x_-2<8)&&(y_+1>=0&&y_+1<8)&&board[x_-2][y_+1]/100!=player){
        boardBackground[x_-2][y_+1]=1;
        ++utemp;
    }
    if((x_-1>=0&&x_-1<8)&&(y_-2>=0&&y_-2<8)&&board[x_-1][y_-2]/100!=player){
        boardBackground[x_-1][y_-2]=1;
        ++utemp;

    }
    if((x_+1>=0&&x_+1<8)&&(y_-2>=0&&y_-2<8)&&board[x_+1][y_-2]/100!=player){
        boardBackground[x_+1][y_-2]=1;
        ++utemp;
    }

    if(!utemp) return false;
    else return true;
}

