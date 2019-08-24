/**
  * @file
  * @brief 处理客户端的获取好友数据请求
  *
  *     识别并处理GETINFO消息
  *     将该用户的好友数据发送到其客户端
  *
  * @author zsj
  * @version 1.0
  * @date 2019年4月20日15:18:40
*/

#ifndef GETINFO_H
#define GETINFO_H

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
#include <QList>
#include <QPair>
#include <memory>

#include "resource.h"

using namespace std;

/// @class GetInfo
/// @brief 处理GETINFO消息
///
///     继承于QRunnable，实现多线程处理
///     识别处理GETINFO消息，返回客户端需要的数据
///
class GetInfo : public QRunnable
{
public:
    /// @brief 创建一个GetInfo对象
    explicit GetInfo():QRunnable(){}

    /// @brief 创建一个GetInfo对象
    /// @param d 发送此消息的客户端发送来的消息
    /// @param a 发送此消息的客户端的IP地址
    /// @param p 发送此消息的客户端的端口
    GetInfo(QString d,QHostAddress a,quint16 p):addr(a),port(p),dealData(d){}


    /// @brief 重写run函数
    ///     实现发送客户端需要的消息
    ///     发送其所有好友分组群组信息
    void run() override;

    /// @brief 获取该用户的好友分组和好友信息数据
    void getFriendInfo();


private:

    QHostAddress addr;
    quint16 port;
    QString dealData; ///< 客户端发送的待处理的数据
    QList<QPair<QString,QList<QString>* >> groupDataList;    ///< 保存一个用户的所有好友和分组信息

    /// @brief 将获取到的好友信息发送回该用户
    void sendFriendInfo();
};

#endif // GETINFO_H
