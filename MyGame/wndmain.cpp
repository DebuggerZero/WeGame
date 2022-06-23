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

    connect(View_records, &QAction::triggered, this, &WndMain::doAction);
    connect(View_achievements, &QAction::triggered, this, &WndMain::doAction);
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


void WndMain::contextMenuEvent(QContextMenuEvent *event)
{
    m_openAction->disconnect();
    if (ui->TZFE->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openTZFE);
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->Snake->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openSnake);
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->Gobang->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openGobang);
        m_rightClieckMenu->exec(event->globalPos());
    }
    else if (ui->color->underMouse()) {
        connect(m_openAction, &QAction::triggered, this, &WndMain::openColor);
        m_rightClieckMenu->exec(event->globalPos());
    }
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

void WndMain::doAction()			//doAction()是一个槽函数
{
    QAction *action =  qobject_cast<QAction*>(sender());			//获取是由那个按钮发出的信号
    if (action == m_openAction)	//如果点击的是“打开”菜单按钮
        QMessageBox::information(this, "Tips","你点击了打开按钮", QMessageBox::Yes);
    else if (action == this->View_records) //如果打开的是“关闭”菜单按钮
        QMessageBox::information(this, "Tips","你点击了关闭按钮", QMessageBox::Yes);
}
