#include "gstartwindow.h"
#include "ui_gstartwindow.h"

GStartWindow::GStartWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GStartWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(500, 700));
    this->setWindowTitle("五子棋");
    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->GameStart, &QPushButton::clicked, this, [=]() {
        gMainWindow = new GMainWindow();
        connect(gMainWindow, &GMainWindow::windowClose, this, [=](){
            this->show();
        });
        gMainWindow->show();
        this->hide();
    });

    connect(ui->GameExit, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

GStartWindow::~GStartWindow()
{
    emit windowsClose();
    ui->GameStart->disconnect();
    ui->GameExit->disconnect();
    delete ui;
}

void GStartWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}


