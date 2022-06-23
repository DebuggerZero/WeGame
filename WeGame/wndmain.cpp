#include "wndmain.h"
#include "ui_wndmain.h"

#include <QDebug>

WndMain::WndMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WndMain)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    _isOpen = false;

    this->setStyleSheet(Utility::getStyleSheet(":/image/wndmain.qss"));

    //2048游戏按钮
    connect(ui->TZFE, &QPushButton::clicked, this, [=](){
        if (!_isOpen) {
            GameStartWindows *gameWidget = new GameStartWindows();
            connect(gameWidget, &GameStartWindows::windowsClose, this, [=](){
                this->show();
                _isOpen = false;
            });
            gameWidget->show();
            this->hide();
        }
    });

    //五子棋游戏按钮
    connect(ui->Gobang, &QPushButton::clicked, this, [=](){
        if (!_isOpen) {
            GStartWindow *gameWidget = new GStartWindow();
            connect(gameWidget, &GStartWindow::windowsClose, this, [=](){
                this->show();
                _isOpen = false;
            });
            gameWidget->show();
            this->hide();
        }
    });

    //贪吃蛇游戏按钮
    connect(ui->Snake, &QPushButton::clicked, this, [=](){
        if (!_isOpen) {
            GStartWidght *gameWidget = new GStartWidght();
            connect(gameWidget, &GStartWidght::windowsClose, this, [=](){
                this->show();
                _isOpen = false;
            });
            gameWidget->show();
            this->hide();
        }
    });

    //color游戏按钮
    connect(ui->color, &QPushButton::clicked, this, [=](){
        if (!_isOpen) {
            Widget *gameWidget = new Widget();
            connect(gameWidget, &Widget::windowsClose, this, [=](){
                this->show();
                _isOpen = false;
            });
            gameWidget->show();
            this->hide();
        }
    });

    connect(ui->comingsoom, &QPushButton::clicked, this, [=](){
        QMessageBox::about(this, "提示", "新游戏正在开发中，敬请期待...");
    });

    //记录
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, [=](int index){
        int currentIndex = index;
        Archive archive(ui->tabWidget->tabText(currentIndex));
        QVector<struct GameTime> records = archive.getRecords();
        QStringList lists;
        for (int i = 0; i < records.length(); i++) {
            struct GameTime record = records.at(i);
            QString s = "        " + QString::number(record.number) + "\t|\t" +
                    QString::number(record.bestScore) + "\t|           " +
                    record.startTime + "\t|          " + record.endTime;
            lists << s;
        }
        if (currentIndex == 0) {
            ui->listWidget->clear();
            ui->listWidget->addItems(lists);
        }
        else if (currentIndex == 1) {
            ui->listWidget_2->clear();
            ui->listWidget_2->addItems(lists);
        }
        else if (currentIndex == 2) {
            ui->listWidget_3->clear();
            ui->listWidget_3->addItems(lists);
        }
        else if (currentIndex == 3) {
            ui->listWidget_4->clear();
            ui->listWidget_4->addItems(lists);
        }
    });
}

WndMain::~WndMain()
{
    delete ui;
}

void WndMain::on_btnGame_clicked()
{
    ui->MainWindow->setCurrentWidget(ui->AllGame);
}

void WndMain::on_btnAchieve_clicked()
{
    ui->MainWindow->setCurrentWidget(ui->achieve);
}

void WndMain::on_btnUser_clicked()
{
    ui->MainWindow->setCurrentWidget(ui->User);
}

void WndMain::on_btnHist_clicked()
{
    emit ui->tabWidget->tabBarClicked(0);
    ui->MainWindow->setCurrentWidget(ui->History);
}

void WndMain::on_btnInstal_clicked()
{
    ui->MainWindow->setCurrentWidget(ui->Instal);
}

void WndMain::on_btnDwi_clicked()
{
    this->showMinimized();
}

void WndMain::on_btnClose_clicked()
{
    this->close();
}
