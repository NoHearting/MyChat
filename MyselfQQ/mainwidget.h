#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <QDebug>
#include "loginwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


    //无边框窗口需要重写鼠标点击和移动时间
   void mouseMoveEvent(QMouseEvent *);
   void mousePressEvent(QMouseEvent *);
   void mouseReleaseEvent(QMouseEvent *);
   void initWindowResouce();            //初始化窗口的资源配置



private slots:
   void on_toolButton_2_clicked();

private:
    Ui::MainWidget *ui;
    QPoint z;
    LoginWidget * loginWin;



    void setMainWinShadow();
};

#endif // MAINWIDGET_H
