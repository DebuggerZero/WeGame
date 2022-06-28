#include "gamewndplayng.h"
#include "ui_gamewndplayng.h"


extern int boardBackground[8][8];

GameWndPlayng::GameWndPlayng(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWndPlayng)
{
    ui->setupUi(this);

      pw= new GamePlayer();

     _archive.setGameName("国际象棋");
     _archive.readGameStorage();
     _archive.setStartTime(QDateTime::currentDateTime());


}

GameWndPlayng::~GameWndPlayng()
{

    _archive.setEndTime(QDateTime::currentDateTime());
    _archive.writeGameStorage();

    delete ui;
}


void GameWndPlayng::Init()
{

    InitBoard();
}

void GameWndPlayng::paintEvent(QPaintEvent *)
{
    if(piece){
        if(piece->GetMove_()){
        for(int i=0;i<8;++i)
            {
                for(int j=0;j<8;++j)
                {//j列 i 行
                   boardBackground[i][j]=0;
                }
            }
        }
     }

        QPainter *p=new QPainter(this);
        p->drawPixmap(0,0,384,384,QPixmap(":/game/assets/chess/checker.png"));
         for(int i=0;i<8;++i)
         {
             for(int j=0;j<8;++j)
             {//j列 i 行

                 p->drawPixmap(48*j,48*i,48,48,QPixmap(":/game/assets/chess/"+
                        QString::number(boardBackground[j][i])+".png"));
                 p->drawPixmap(48*j,48*i,48,48,QPixmap(":/game/assets/chess/"+
                        QString::number(board[j][i])+".png"));
             }
         }

      delete p;
}

void GameWndPlayng::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<piece;
   int x=e->pos().x()/48;
   int y=e->pos().y()/48;

   if((x>7||y>7)||(!(pw->waction||pw->baction)&&!board[x][y]))
   {
       qDebug()<<"here is NULL";
       return;
   }

   if(piece)
   {
       if(x==piece->GetX()&&y==piece->GetY()){
       if(pw->thisShow==1)
       {
           pw->waction=false;
           delete piece;

           qDebug()<<piece;
           for(int i=0;i<8;++i)
           {
               for(int j=0;j<8;++j)
               {//j列 i 行
                  boardBackground[i][j]=0;
               }
           }
           update();
           return;
       }
       else {
           pw->baction=false;
           delete piece;

           qDebug()<<piece;
           for(int i=0;i<8;++i)
           {
               for(int j=0;j<8;++j)
               {//j列 i 行
                  boardBackground[i][j]=0;
               }
           }

           update();
           return;
       }
     }
  }

    qDebug()<<pw->thisShow;
   if(pw->thisShow==1)
   {
       if(!pw->waction){
          if(board[x][y]/100==1){

            pw->waction=true;
            //Init piece
             piece= GetChaPiece(board[x][y],x,y);

             qDebug()<<piece;
            if(piece->isHaveMoveRoad(piece->GetValue()/100,&board[0],
                                     arrStep(PieceName(piece->GetValue()/100,piece->GetValue())),
                                     nextarrStep(PieceName(piece->GetValue()/100,piece->GetValue())))){
                                     update();
                                     return;
                                     }
                                    delete piece;
                                    pw->waction=false;
                                    }
     }
   }else if(pw->thisShow==2){
       if(!pw->baction){
          if(board[x][y]/100==2){
//            qDebug()<<"here is b show";
            pw->baction=true;
            //Init piece
           piece= GetChaPiece(board[x][y],x,y);
           qDebug()<<piece;
           if(piece->isHaveMoveRoad(piece->GetValue()/100,&board[0],
                                    arrStep(PieceName(piece->GetValue()/100,piece->GetValue())),
                                    nextarrStep(PieceName(piece->GetValue()/100,piece->GetValue())))){
                                    update();
                                    return;
                                    }
                                    delete piece;
                                    pw->baction=false;
                                }
                     }
   }

  if(piece) PlayerMove(piece->GetValue(),x,y);
  update();
}

void GameWndPlayng::closeEvent(QCloseEvent *)
{
    emit windowsClose();
}
