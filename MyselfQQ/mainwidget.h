/**
  * @file
  * @brief 客户端主界面
  *
  *		包括客户端的一系列基本操作
  *
  *
*/


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <QDebug>
#include <QListWidgetItem>
#include <QPainter>
#include <QPixmap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QMap>
#include <QListWidgetItem>
#include <typeinfo>
#include <memory>   // 智能指针
#include <cstdlib>
#include <ctime>

#include "loginwidget.h"
#include "chatwidget.h"
#include "personlist.h"
#include "makeqss.h"

namespace Ui {
class MainWidget;
}

/// @enum MsgType
///
/// @brief 消息类型
///
///     客户端和服务器交互发送的消息类型

enum MsgType{LOGIN,   ///< 登录信息类型
             OFFLINE, ///< 离线信息类型
             ADD,  ///< 添加
             DELETE, ///<  删除
             GETINFORMATION,  ///< 获取好友信息
             UPDATA,   ///< 更新信息，包括创建，删除分组、群
             OK_GETINFO ///< 获取好友列表的信息
            };

/// @class MainWidget
///
/// @brief 客户端主类
///
///     包含客户端的基本操作
///
/// @version 1.0
/// @note


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
   void initUdpSocket();               //初始化udp
   void initConnect();

   //以下为调试函数


private slots:


   /// @brief 转到消息界面
   ///
   void on_toolButtonMsg_clicked();


   /// @brief 转到联系人界面
   void on_toolButtonLinkMan_clicked();


   /// @brief 转到动态界面
   void on_toolButtonMove_clicked();

   /// @brief 关闭窗口
   void on_toolButtonCLose_clicked();

   /// @brief 最小化窗口
   void on_toolButtonMin_clicked();


   /// @brief 处理点击事件槽函数
   void slotDealClicked(QListWidgetItem * );

   /// @brief 处理双击事件槽函数
   void deal_double_clicked(QListWidgetItem * item);

   /// @brief 关闭聊天窗口槽函数
   ///
   ///  删除已经关闭的聊天框
   ///
   void close_chat_window();




private:
    Ui::MainWidget *ui;
    QPoint z;


    /*
        ui中的tabWidget包含两个界面
        1.好友联系人界面：ui->listWidgeMsg
        2.群组界面 groupList

        当前群组分页没有东西
    */
    personList * groupList;    ///< 群组分页的list


    LoginWidget * loginWin;   ///< 登录界面
    ChatWidget * chatWin;     ///< 聊天界面

    QList<shared_ptr<ChatWidget>> list_chat_window_;   /// 聊天窗口
    int chat_window_num_ = 0;   /// 聊天窗口的个数

    QTcpServer * tcpServer;     //监听套接字
    QTcpSocket * tcpSocket;      //通信（发文件）套接字
    QUdpSocket * udpSocket;      //通信（聊天）套接字
    int udp_port_ = 0;            ///< 连接的服务器端端口
    int local_port = 0;         ///< 本机客户端端口


    QString uId;                ///< 用户的账号
    QString password;           ///< 用户密码

    QMap<QString,MsgType> msg_type_map_;  ///< 消息类型map

    QList<QPair<PersonGroup*,QList<personListBuddy*>*>> origin_list_;  ///< 用户好友列表的信息


    void setMainWinShadow();

    /// @brief 设置好友列表的信息
    ///
    ///     将从服务器接收的消息放到列表信息中
    /// @param data 从服务器接收到的字符串消息，此字符串包含的是一个好友的所有信息
    void set_friend_list_info(QString & data);

    /// @brief 显示好友列表信息
    ///
    ///     将已有的信息更新显示到界面
    /// @param pg 选中的分组选项的指针，若此分组选项显示，则隐藏；若隐藏，则显示
    void showFriendListInfo(PersonGroup * pg = nullptr);
};

#endif // MAINWIDGET_H
