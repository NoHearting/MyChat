#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPoint>

#include "makeqss.h"

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = 0);
    ~RegisterWidget();
    //无边框窗口需要重写鼠标点击和移动时间
   void mouseMoveEvent(QMouseEvent *);
   void mousePressEvent(QMouseEvent *);
   void mouseReleaseEvent(QMouseEvent *);

    void initWindowResoure();   //初始化注册窗口的各项资源和QSS样式表美化
    void setRegisWindowShadow();   //设置注册窗口的阴影效果

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::RegisterWidget *ui;

    QPoint z;
};

#endif // REGISTERWIDGET_H
