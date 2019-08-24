/**
  * @file
  * @brief 登录界面
  *
  *     登录界面，主要以账号密码登录
  * @author zsj
  * @version 1.0
  * @date 2019年4月24日23:26:13
  *
  *
  *
  *
  *
  *
*/


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

#include "makeqss.h"
#include "registerwidget.h"

namespace Ui {
class LoginWidget;
}

/// @class LoginWidget
/// @brief 登录界面
///
///     登录和注册
/// @version 1.0
/// @note 当前只实现了登录按钮，注册并未实现  2019年4月30日09:53:32


class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

     //无边框窗口需要重写鼠标点击和移动时间
    /// @brief 重写mouseMoveEvent函数
    ///
    ///     用户点击有可能点击LoginWidget页面之上的小部件然后拖动
    ///会出现抖动，此函数解决此问题
    void mouseMoveEvent(QMouseEvent *);

    /// @brief 重写mousePressEvent函数
    ///
    ///  鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的差值
    void mousePressEvent(QMouseEvent *);

    /// @brief 重写mouseReleaseEvent函数
    void mouseReleaseEvent(QMouseEvent *);


    /// @brief 初始化各类资源
    ///
    ///     初始化各类资源，包括窗口阴影，播放GIF动画
    void initWindowResouce();            //初始化窗口的资源配置

    /// @brief 设置登录标志
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
	/// @brief 设置窗口布置
	///  
	///  包括窗口阴影
    void setLoginWidgetShadow();          //设置登录窗口阴影


    Ui::LoginWidget *ui;
    QPoint z;             ///< 鼠标点击位置和窗口左上角的差值
    bool isLogin;         ///< 是否登录  登录为true

    RegisterWidget * regis;   ///< 注册窗账号的窗口


};

#endif // LOGINWIDGET_H
