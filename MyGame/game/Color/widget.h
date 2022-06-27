#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QColor>
#include <QStyleOption>
#include <QCloseEvent>
#include <QPixmap>
#include <QDialog>
#include <QFont>
#include <QPainter>

#include "archive/archive.h"
#include "color.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    int score;//分数
    int n;//倒计时时间
    Archive *arc;//文件
    color *cr;//随机生成颜色
    QColor cr_;//模板
    QColor _cr;//需匹配的模板
    QTimer *timer;//倒计时指针
    QTimer *m_timer;//匹配度时间指针
    void change(QColor);//模板显示
    void change_(QColor);//匹配模板显示
    void time();//倒计时
    bool check();//匹配颜色差
    ~Widget();

    void paintEvent(QPaintEvent* event);

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void windowsClose();

private slots:
    void on_horizontalSlider_R_valueChanged(int value);
    void on_spinBox_R_valueChanged(int arg1);
    void on_horizontalSlider_G_valueChanged(int value);
    void on_spinBox_G_valueChanged(int arg1);
    void on_horizontalSlider_B_valueChanged(int value);
    void on_spinBox_B_valueChanged(int arg1);
    void on_start_game_clicked();
    void on_exit_game_clicked();
    void on_prepare_clicked();
    void on_confirm_clicked();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
