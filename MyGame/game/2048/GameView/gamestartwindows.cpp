#include "gamestartwindows.h"
#include "ui_gamestartwindows.h"

GameStartWindows::GameStartWindows(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameStartWindows)
{
    ui->setupUi(this);

    this->setFixedSize(400, 500); //设置窗口尺寸
    this->setWindowTitle("2048"); //设置窗口标题
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setStyleSheet(Utility::getStyleSheet(":/game/assets/2048/start/start.css"));

    connect(ui->StartGame, &QPushButton::clicked, this, [=](){
        gameMainWindows_ = new GameMainWindows();
        connect(gameMainWindows_, &GameMainWindows::windowsClose, this, [=](){
            this->show();
        });
        QMessageBox::about(this, "提示", "按 W、A、S、D 或 ↑、↓、←、→<br>移动方块。<br>按 Esc 重新开始游戏...");
        gameMainWindows_->show();
        this->hide();
    });

    connect(ui->ExitGame, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

GameStartWindows::~GameStartWindows()
{
    ui->StartGame->disconnect();
    ui->ExitGame->disconnect();
    emit windowsClose();
    delete ui;
}

void GameStartWindows::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
