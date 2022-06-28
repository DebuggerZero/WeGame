#include "gamewndstrat.h"
#include "ui_gamewndstrat.h"

GameWndStrat::GameWndStrat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWndStrat)
{
    ui->setupUi(this);
    connect(ui->btnStrat,&QPushButton::clicked,this,[=](){
        Gamewndplay=new GameWndPlayng();
        Gamewndplay->Init();
        connect(Gamewndplay, &GameWndPlayng::windowsClose, this, [=](){
            this->show();
        });
        Gamewndplay->show();
        this->hide();
    });
    connect(ui->btnexit,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

GameWndStrat::~GameWndStrat()
{
    delete ui;
}

void GameWndStrat::closeEvent(QCloseEvent *)
{

    emit windowsClose();
}
