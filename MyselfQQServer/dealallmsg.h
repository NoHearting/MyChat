#ifndef DEALALLMSG_H
#define DEALALLMSG_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QEventLoop>
#include <QThreadPool>
#include <QTimer>

#include "getinfo.h"
#include "dealloginmsg.h"
#include "resource.h"

/// @enum msgType
/// @brief 客户端发送来的消息类型
enum msgType{LOGIN,   ///< 登录
             LOGIN_OK, ///< 登录成功
             OFFLINE, ///< 离线
             ADD,     ///< 添加
             DELETE,  ///< 删除
             GETINFORMATION,  ///< 获取好友信息
             UPDATA,   ///< 更新信息，包括创建，删除分组、群
             OK_GETINFO   ///< 好友信息发送完成时发送此消息
            };



class DealAllMsg : public QObject
{
    Q_OBJECT
public:
    explicit DealAllMsg(QObject *parent = 0);
    DealAllMsg(int port);


    /// @brief 初始化资源
    void init();
    /// @brief 线程开始IDE信号
    void beginThread();
private:
    int port;     // 该线程udpSocket绑定的端口号
    QUdpSocket * udpSocket;
    QMap<QString,msgType> msg_type_map_;


    QThreadPool threadPool;  ///< 线程池  最大数量设置为10
signals:
    void login(QString,quint16);
public slots:


};

#endif // DEALALLMSG_H
