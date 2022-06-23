#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    arc=new Archive("色彩达人");
    arc->readGameStorage();
    QDateTime current_date_time =QDateTime::currentDateTime();
    arc->setStartTime(current_date_time);

    n=60;
    score=0;
    ui->novice->setChecked(true);
    //ui->results->hide();
    m_timer=new QTimer(this);
    cr=new color();
    cr->generateRandomNumber(cr_);
    change(cr_);
    change_(_cr);
    connect(m_timer,&QTimer::timeout,this,[=](){
        m_timer->stop();
        ui->results->hide();
    });
    QPixmap maskPixmap(":/game/assets/color/3.0.png");
    ui->confirm->setMask(maskPixmap.mask());
    ui->confirm->setStyleSheet("QPushButton{border-image: url(:/game/assets/color/3.0.png);}"
                               "QPushButton:hover{border-image: url(:/game/assets/color/3.00.png);}"
                               "QPushButton:pressed{border-image: url(:/game/assets/color/3.png);}");
    ui->confirm->setShortcut(Qt::Key_Return);
    ui->prepare->setShortcut(Qt::Key_Return);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void Widget::on_start_game_clicked()//开始游戏
{
    if(ui->simple->isChecked()){
        ui->login->hide();
        ui->simple->setAutoExclusive(false);
        ui->simple->setChecked(false);
        ui->simple->setAutoExclusive(true);
    }
    else if(ui->difficulty->isChecked())
    {
        ui->login->hide();
        ui->Template->setText("禁用"); //清空字体
        ui->Template->setStyleSheet("QLabel{background-color:rgb(131,131,131);}");  //设置样式表
    }
    if(ui->novice->isChecked()){
    ui->confirm->hide();
    }
    else
    {
        ui->prepare_box->hide();
        time();
    }
    ui->count_down->setDigitCount(3);
    ui->count_down->display(60);
}

void Widget::on_prepare_clicked()//准备，查看操作界面
{
    n=60;
    cr->generateRandomNumber(cr_);
    change(cr_);
    time();
    ui->prepare_box->hide();
    ui->confirm->show();
}

void Widget::on_confirm_clicked()//判断是否匹配
{
    if(check())
    {
        n=60;
        cr->generateRandomNumber(cr_);
        change(cr_);
        on_spinBox_R_valueChanged(0);
        on_spinBox_G_valueChanged(0);
        on_spinBox_B_valueChanged(0);
    }
}

void Widget::change(QColor cr)//模板显示
{
    QString sty = QString("background-color:%1").arg(cr.name());
    ui->template_matching->setStyleSheet(sty);//在显示框显示颜色
}

void Widget::change_(QColor cr)//匹配模板显示
{
    QString sty = QString("background-color:%1").arg(cr.name());
    if(!ui->difficulty->isChecked())ui->Template->setStyleSheet(sty);//在显示框显示颜色
}

void Widget::time()//倒计时
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        ui->count_down->display(QString::number(--n,10,0));
        if (n == 0) {
            timer->stop();
            if(arc->getBestScore()<score)arc->setBestScore(score);
//            QDateTime current_date_time =QDateTime::currentDateTime();
//            arc->setEndTime(current_date_time);
//            arc->writeGameStorage();
            QDialog *dlg=new QDialog();
            dlg->setMinimumSize(400,275);
            dlg->setMaximumSize(400,275);
            dlg->setWindowTitle("end");
            dlg->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
            QFont f;
            f.setPointSize(30);
            QLabel tip("挑战失败",dlg);
            tip.move(120,50);
            tip.setFont(f);
            QPushButton restart("重新挑战",dlg);
            QPushButton sign_out("退出游戏",dlg);
            restart.setGeometry(75,150,100,40);
            sign_out.setGeometry(215,150,100,40);
            connect(&restart,&QPushButton::clicked,dlg,[=](){
                dlg->close();
                ui->difficulty->setAutoExclusive(false);
                ui->difficulty->setChecked(false);
                ui->difficulty->setAutoExclusive(true);
                ui->prepare_box->show();
                ui->login->show();
                score=0;
                on_spinBox_R_valueChanged(0);
                on_spinBox_G_valueChanged(0);
                on_spinBox_B_valueChanged(0);
            });
            connect(&sign_out,&QPushButton::clicked,dlg,[=](){
                dlg->close();
                this->close();
            });

            dlg->exec();
        }
    });
    timer->start(1000);
}

void Widget::closeEvent(QCloseEvent *)//捕捉关闭窗口信号，执行操作
{
    emit windowsClose();
    QDateTime current_date_time = QDateTime::currentDateTime();
    arc->setEndTime(current_date_time);
    arc->writeGameStorage();
}

bool Widget::check()//匹配颜色差
{
    int color1[3];
    _cr.getRgb(&color1[0],&color1[1],&color1[2]);
    int color2[3];
    cr_.getRgb(&color2[0],&color2[1],&color2[2]);
    int color3[3];
    color3[0] = color2[0] > 255 - color2[0] ? color2[0]:255-color2[0];
    color3[1] = color2[1] > 255 - color2[1] ? color2[1] : 255 - color2[1];
    color3[2] = color2[2] > 255 - color2[2] ? color2[2] : 255 - color2[2];
    float result =100- (float)(abs(color1[0] - color2[0]) + abs(color1[1] - color2[1])  + abs(color1[2] - color2[2])) /
            (color3[0]+color3[1]+color3[2])*100;
    static float m=80;
    if(result>m)
    {
        ui->results->setText(QString::number(result,'f',2)+"%");
        ui->results->show();
        m_timer->start(1000);
        if(m<99)m+=2*(score+1);
        score++;
        ui->scores->display(QString::number(score));
        return true;
    }
    else return false;
}

void Widget::on_exit_game_clicked()//退出游戏
{
    this->close();
}

void Widget::on_horizontalSlider_R_valueChanged(int value)
{
    ui->spinBox_R->setValue(value);
    ui->horizontalSlider_R->setValue(value);
    _cr.setRed(value);
    change_(_cr);
}

void Widget::on_spinBox_R_valueChanged(int arg1)
{
    ui->horizontalSlider_R->setValue(arg1);
    ui->spinBox_R->setValue(arg1);
    _cr.setRed(arg1);
    change_(_cr);
}

void Widget::on_horizontalSlider_G_valueChanged(int value)
{
    ui->spinBox_G->setValue(value);
    ui->horizontalSlider_G->setValue(value);
    _cr.setGreen(value);
    change_(_cr);
}

void Widget::on_spinBox_G_valueChanged(int arg1)
{
    ui->horizontalSlider_G->setValue(arg1);
    ui->spinBox_G->setValue(arg1);
    _cr.setGreen(arg1);
    change_(_cr);
}

void Widget::on_horizontalSlider_B_valueChanged(int value)
{
    ui->spinBox_B->setValue(value);
    ui->horizontalSlider_B->setValue(value);
    _cr.setBlue(value);
    change_(_cr);
}

void Widget::on_spinBox_B_valueChanged(int arg1)
{
    ui->horizontalSlider_B->setValue(arg1);
    ui->spinBox_B->setValue(arg1);
    _cr.setBlue(arg1);
    change_(_cr);
}
