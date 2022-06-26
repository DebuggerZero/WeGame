#include "wndmain.h"
#include "ui_wndmain.h"

#include <QDebug>

WndMain::WndMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WndMain)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    this->setStyleSheet(Utility::getStyleSheet(":/image/wndmain.qss"));

    initWindows();
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

    ui->nameList->clear();
    ui->numberList_2->clear();
    ui->scoreList_2->clear();
    ui->gameTimeList->clear();

    ui->UserNameLabel->setText("UserName：" + Archive::userName);
    ui->AccountLabel->setText("Account：" + Archive::account);

    ui->nameList->addItem("2048");
    ui->nameList->addItem("五子棋");
    ui->nameList->addItem("贪吃蛇");
    ui->nameList->addItem("色彩达人");

    Archive gobangRecord("五子棋");
    gobangRecord.readGameStorage();
    Archive snakeRecord("贪吃蛇");
    snakeRecord.readGameStorage();
    Archive tzfeRecord("2048");
    tzfeRecord.readGameStorage();
    Archive colorRecord("色彩达人");
    colorRecord.readGameStorage();

    ui->numberList_2->addItem(QString::number(tzfeRecord.getNumber()));
    ui->numberList_2->addItem(QString::number(gobangRecord.getNumber()));
    ui->numberList_2->addItem(QString::number(snakeRecord.getNumber()));
    ui->numberList_2->addItem(QString::number(colorRecord.getNumber()));

    ui->scoreList_2->addItem(QString::number(tzfeRecord.getBestScore()));
    ui->scoreList_2->addItem("-");
    ui->scoreList_2->addItem(QString::number(snakeRecord.getBestScore()));
    ui->scoreList_2->addItem(QString::number(colorRecord.getBestScore()));

    ui->gameTimeList->addItem(QString::number(tzfeRecord.getGameTime() / 1000) + " s");
    ui->gameTimeList->addItem(QString::number(gobangRecord.getGameTime() / 1000) + " s");
    ui->gameTimeList->addItem(QString::number(snakeRecord.getGameTime() / 1000) + " s");
    ui->gameTimeList->addItem(QString::number(colorRecord.getGameTime() / 1000) + " s");

}

void WndMain::on_btnHist_clicked()
{
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


void WndMain::contextMenuEvent(QContextMenuEvent *event)
{
    m_openAction->disconnect();
    View_records->disconnect();
    View_achievements->disconnect();

    if (ui->TZFE->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openTZFE);
        connect(View_records, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->History);
            showList("2048");
        });
        connect(View_achievements, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->achieve);
            ui->achieveWidget->setCurrentWidget(ui->tzfeAchieve);
        });
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->Snake->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openSnake);
        connect(View_records, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->History);
            showList("贪吃蛇");
        });
        connect(View_achievements, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->achieve);
            ui->achieveWidget->setCurrentWidget(ui->snakeAchieve);
        });
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->Gobang->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openGobang);
        connect(View_records, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->History);
            showList("五子棋");
        });
        connect(View_achievements, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->achieve);
            ui->achieveWidget->setCurrentWidget(ui->gobangAchieve);
        });
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->color->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openColor);
        connect(View_records, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->History);
            showList("色彩达人");
        });
        connect(View_achievements, &QAction::triggered, this, [=](){
            ui->MainWindow->setCurrentWidget(ui->achieve);
            ui->achieveWidget->setCurrentWidget(ui->colorAchieve);
        });
        m_rightClieckMenu->exec(event->globalPos());
    }
}

void WndMain::showList(QString gameName)
{
    Archive archive(gameName);
    QVector<struct GameTime> records = archive.getRecords();
    QStringList numberLists;
    QStringList scoreLists;
    QStringList startTimeLists;
    QStringList endTimeLists;
    for (int i = 0; i < records.length(); i++) {
        struct GameTime record = records.at(i);
        numberLists.append(QString::number(record.number));
        scoreLists.append(QString::number(record.bestScore));
        startTimeLists.append(record.startTime);
        endTimeLists.append(record.endTime);
    }
    ui->numberList->clear();
    ui->numberList->addItems(numberLists);
    ui->scoreList->clear();
    ui->scoreList->addItems(scoreLists);
    ui->startTimeList->clear();
    ui->startTimeList->addItems(startTimeLists);
    ui->endTimeList->clear();
    ui->endTimeList->addItems(endTimeLists);
}

void WndMain::openTZFE()
{
    if (!_isOpen) {
        GameStartWindows *gameWidget = new GameStartWindows();
        connect(gameWidget, &GameStartWindows::windowsClose, this, [=](){
            this->show();
            _isOpen = false;
        });
        gameWidget->show();
        this->hide();
    }
}

void WndMain::openGobang()
{
    if (!_isOpen) {
        GStartWindow *gameWidget = new GStartWindow();
        connect(gameWidget, &GStartWindow::windowsClose, this, [=](){
            this->show();
            _isOpen = false;
        });
        gameWidget->show();
        this->hide();
    }
}

void WndMain::openSnake()
{
    if (!_isOpen) {
        GStartWidght *gameWidget = new GStartWidght();
        connect(gameWidget, &GStartWidght::windowsClose, this, [=](){
            this->show();
            _isOpen = false;
        });
        gameWidget->show();
        this->hide();
    }
}

void WndMain::openColor()
{
    if (!_isOpen) {
        Widget *gameWidget = new Widget();
        connect(gameWidget, &Widget::windowsClose, this, [=](){
            this->show();
            _isOpen = false;
        });
        gameWidget->show();
        this->hide();
    }
}

void WndMain::initWindows()
{
    _isOpen = false;

    ui->headPortraitLabel->setPixmap(Archive::headPath);

    ui->MainWindow->setCurrentWidget(ui->AllGame);

    //===================================================================================
    //游戏界面按钮事件

    //2048游戏按钮
    connect(ui->TZFE, &QPushButton::clicked, this, &WndMain::openTZFE);

    //五子棋游戏按钮
    connect(ui->Gobang, &QPushButton::clicked, this, &WndMain::openGobang);

    //贪吃蛇游戏按钮
    connect(ui->Snake, &QPushButton::clicked, this, &WndMain::openSnake);

    //color游戏按钮
    connect(ui->color, &QPushButton::clicked, this, &WndMain::openColor);

    connect(ui->comingsoom, &QPushButton::clicked, this, [=](){
        QMessageBox::about(this, "提示", "新游戏正在开发中，敬请期待...");
    });

    m_rightClieckMenu = new QMenu(this);
    //设置菜单样式
    /**************************************/
    //创建菜单项
    m_openAction = new QAction("打开",this);
    View_achievements = new QAction("查看成就",this);
    View_records = new QAction("查看记录",this);

    //将创建好的菜单项加入到菜单中
    m_rightClieckMenu->addAction(m_openAction);
    m_rightClieckMenu->addAction(View_achievements);
    m_rightClieckMenu->addAction(View_records);

    m_openAction->setIcon(QIcon(":/image/image/gameIcon.png"));
    View_achievements->setIcon(QIcon(":/image/image/achiIcon.png"));
    View_records->setIcon(QIcon(":/image/image/histIcon.png"));
    //关联菜单项按钮和对应的槽函数

//    connect(View_achievements, &QAction::triggered, this, &WndMain::doAction);
    //====================================================================================

    //====================================================================================
    //记录界面按钮事件======================================================================
    //记录
    connect(ui->tzfeRecordButton, &QPushButton::clicked, this, [=](){
        showList("2048");
    });

    connect(ui->snakeRecordButton, &QPushButton::clicked, this, [=](){
        showList("贪吃蛇");
    });

    connect(ui->gobangRecordButton, &QPushButton::clicked, this, [=](){
        showList("五子棋");
    });

    connect(ui->colorRecordButton, &QPushButton::clicked, this, [=](){
        showList("色彩达人");
    });
    //====================================================================================

    //====================================================================================
    //成就界面按钮事件
    connect(ui->gobangRecordButton_2, &QPushButton::clicked, this, [=](){
        ui->achieveWidget->setCurrentWidget(ui->gobangAchieve);
    });

    connect(ui->tzfeRecordButton_2, &QPushButton::clicked, this, [=](){
        ui->achieveWidget->setCurrentWidget(ui->tzfeAchieve);
    });

    connect(ui->snakeRecordButton_2, &QPushButton::clicked, this, [=](){
        ui->achieveWidget->setCurrentWidget(ui->snakeAchieve);
    });

    connect(ui->colorRecordButton_2, &QPushButton::clicked, this, [=](){
        ui->achieveWidget->setCurrentWidget(ui->colorAchieve);
    });
    //====================================================================================

    //====================================================================================
    //设置按钮事件
    connect(ui->btnchead, &QPushButton::clicked, this, [=](){
        QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("TextFiles(*.png, *.jpg)"));
        if (path != "") {
            Archive::headPath = path;
            ui->headPortraitLabel->setPixmap(Archive::headPath);
            QMessageBox::about(this, "提示", "头像上传成功...");
        }
        else {
            QMessageBox::about(this, "提示", "未选择任何图片...");
        }
    });
}
