#include "gstartwidght.h"
#include "ui_gstartwidght.h"

GStartWidght::GStartWidght(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GStartWidght)
{
    ui->setupUi(this);

    this->setWindowTitle("贪吃蛇");
    this->setFixedSize(QSize(805, 556));
    this->setAttribute(Qt::WA_DeleteOnClose);

    _backGround.load(":/game/assets/Snake/backGround.png");
    _title.load(":/game/assets/Snake/title.png");

    connect(ui->startButton, &QPushButton::clicked, this, [=](){
        _gMainWidget = new GMainWidget();
        connect(_gMainWidget, &GMainWidget::closeWindows, this, [=](){
            this->show();
        });
        _gMainWidget->show();
        this->hide();
    });

    connect(ui->exitButton, &QPushButton::clicked, this, [=]{
        this->close();
    });

}

GStartWidght::~GStartWidght()
{
    emit windowsClose();
    ui->startButton->disconnect();
    ui->exitButton->disconnect();
    delete ui;
}

void GStartWidght::paintEvent(QPaintEvent *)
{
    QPainter g(this);
    g.setRenderHint(QPainter::SmoothPixmapTransform);
    g.drawPixmap(0, 0, _backGround);
    g.drawPixmap(120, 114, _title);
}
