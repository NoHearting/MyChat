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

#include "loginwidget.h"
#include "chatwidget.h"
#include "personlist.h"

namespace Ui {
class MainWidget;
}

enum MsgType{LOGIN,   //登录信息类型
             OFFLINE, //离线信息类型
             ADD,  //添加
             DELETE, // 删除
             GETINFORMATION,  //获取好友信息
             UPDATA,   //更新信息，包括创建，删除分组、群
             OK_GETINFO
            };


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


   void on_toolButtonMsg_clicked();

   void on_toolButtonLinkMan_clicked();

   void on_toolButtonMove_clicked();

   void on_toolButtonCLose_clicked();

   void on_toolButtonMin_clicked();


   /// @brief 处理点击事件槽函数
   void slotDealClicked(QListWidgetItem * );


private:
    Ui::MainWidget *ui;
    QPoint z;
    /*
        ui中有一个消息列表   这是存放第二个消息列表
        聊天信息界面的消息列表未写出来

    */
    personList * groupList;    //显示群组


    LoginWidget * loginWin;   //登录界面
    ChatWidget * chatWin;     //聊天界面
    QTcpServer * tcpServer;     //监听套接字
    QTcpSocket * tcpSocket;      //通信（发文件）套接字
    QUdpSocket * udpSocket;      //通信（聊天）套接字

    QString uId;
    QString password;

    QMap<QString,MsgType> msg_type_map_;  ///< 存放消息信息
    QList<QPair<PersonGroup*,QList<personListBuddy*>*>> origin_list_;  ///< 列表信息根本信息  由于刷新列表的一些操作  设置一个根本字符串;


    void setMainWinShadow();

    /// @brief 设置好友列表的信息
    void set_friend_list_info(QString & data);
    void showFriendListInfo(PersonGroup * pg = nullptr);
};

#endif // MAINWIDGET_H
