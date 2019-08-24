/**
  * @file Widget.cpp
  * @brief 数据库服务器的只要操作
  *
  *     接收所有客户端发来的消息，并处理后返回结果
  * @author zsj
  * @version 1.0
  * @date 2019年4月20日15:42:54
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QMetaObject>
#include <QMap>
#include <QString>
#include <QThreadPool>
#include <QVector>
#include <QThread>

#include "dealloginmsg.h"
#include "getinfo.h"
#include "dealallmsg.h"
#include "resource.h"

/// @namespace Ui
/// @brief Qt的Ui界面名称空间
///
namespace Ui {
class Widget;
}

// /// @enum msgType
// /// @brief 客户端发送来的消息类型
//enum msgType{LOGIN,   ///< 登录
//             OFFLINE, ///< 离线
//             ADD,     ///< 添加
//             DELETE,  ///< 删除
//             GETINFORMATION,  ///< 获取好友信息
//             UPDATA,   ///< 更新信息，包括创建，删除分组、群
//             OK_GETINFO   ///< 好友信息发送完成时发送此消息
//            };


/// @class Widget
/// @brief 数据库服务器主要操作
///
///     处理所有客户端发送的消息，创建一个线程池QThreadPool维护所有的处理消息程序
///     线程池最大容量为10
///     派生于QWidget
/// @author zsj
/// @version 1.0
class Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Widget(QWidget *parent = 0);
    ~Widget();

    /// @brief 初始化数据库
    void initDatabase();

    /// @brief 初始化基本的成员变量
    void init();


    /// @brief 连接数据库
    ///
    ///     静态函数，连接数据库
    /// @return @c false 连接失败
    ///         @c true  连接成功
    static bool connectDatabase();                                //连接数据库

signals:
    void startThread();   // 开始线程


private slots:
//    void on_pushButton_clicked();
    void slotDealMsg();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    QUdpSocket * udpSocket;   ///< udp套接字 用于接收客户端信息

    QMetaObject::Connection iscon;     //检查槽函数的连接是否成功

    QMap<QString,msgType> msgTypeMap;   ///< 接收的消息类型

    QThreadPool threadPool;        ///< 线程池 最大为10个  这里是允许多用户同时登陆

    static QSqlDatabase db;        ///< 数据库


    QThread * thread;
    DealAllMsg * dealallmsg;
    QVector<QThread *>thread_verctor_;
    QVector<DealAllMsg * >dealallmsg_vector_;
};

#endif // WIDGET_H
