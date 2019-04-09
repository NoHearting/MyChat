#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QMovie>
#include <QDebug>
#include <QString>
#include <QMessageBox>

#include "registerwidget.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

     //无边框窗口需要重写鼠标点击和移动时间
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void initWindowResouce();            //初始化窗口的资源配置
    void setIsLogin(bool flag);
    inline bool getIsLogin(){return isLogin;}


    /*
        登录界面不放数据，也不连接数据库。点击登录按钮后发送信号到主窗口
        信号包含了登录人的id和密码，然后主窗口验证完成后发回来一个信号，
        用以验证是否登录
    */
signals:
    void loginOk(QString,QString);     //登录成功则发出一个信号

private slots:
    void on_toolButtonClose_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

private:
    void setLoginWidgetShadow();          //设置登录窗口阴影


    Ui::LoginWidget *ui;
    QPoint z;             //鼠标点击位置和窗口左上角的差值
    bool isLogin;         //是否登录  登录为true

    RegisterWidget * regis;   //注册窗账号的窗口


};

#endif // LOGINWIDGET_H
