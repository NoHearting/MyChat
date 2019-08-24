/**
  * @file
  * @brief 包含处理登录消息的类的定义
  *
  *     处理客户端发来的登录信息，处理验证并返回
  *
  * @author zsj
  * @version 1.0
  * @date 2019年4月20日13:50:47
  *
  *
 */

#ifndef DEALLOGINMSG_H
#define DEALLOGINMSG_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMetaObject>
#include <QRunnable>

#include "resource.h"

/// @class dealCilentMsg
/// @brief 处理客户端信息中的LOGIN消息
///   用于处理客户端的登录信息，验证并返回客户端一个结果
///   验证到数据库验证，返回消息利用UDP返回
///   继承与QRunnable，实现多线程调用
/// @author zsj
/// @note
///     类名与实际用法有出入
///
class DealLoginMsg : public QRunnable
{
public:
    /// @brief 构造一个dealClientMsg对象
    explicit DealLoginMsg():QRunnable(){}

    /// @brief 构造一个dealClientMsg对象
    DealLoginMsg(QString msg,QHostAddress Addr,quint16 p);    //在此函数里面进行关键操作

    /// @brief 判断该用户是否合法
    ///
    ///     接收一个账户的账号的id和password，在数据库验证后返回结果
    /// @param id 账号
    /// @param password 密码
    /// @return @c false 验证失败，账号或者密码不满足条件
    ///         @c true 验证成功
    bool isTrueUser(QString id,QString password);        //验证用户是否存在




protected:
    /// @brief 重写run方法
    ///
    ///     实现验证一个账号是否合法
    ///
    void run()override;
private:
    QUdpSocket * udpSocket;        ///< UDP套接字，实现返回客户端消息

    QString msg;    ///< 客户端发来的消息

    QHostAddress addr;  ///< 客户端ip地址
    quint16 port;       ///< 客户端端口

};

#endif // DEALLOGINMSG_H
