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
#include "loginwidget.h"
#include "chatwidget.h"
#include "personlist.h"

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
   void initUdpSocket();               //初始化udp
   void initConnect();



private slots:


   void on_toolButtonMsg_clicked();

   void on_toolButtonLinkMan_clicked();

   void on_toolButtonMove_clicked();

   void on_toolButtonCLose_clicked();

   void on_toolButtonMin_clicked();

private:
    Ui::MainWidget *ui;
    QPoint z;
    personList * groupList;    //显示群组


    LoginWidget * loginWin;   //登录界面
    ChatWidget * chatWin;     //聊天界面
    QTcpServer * tcpServer;     //监听套接字
    QTcpSocket * tcpSocket;      //通信（发文件）套接字
    QUdpSocket * udpSocket;      //通信（聊天）套接字


    void setMainWinShadow();
};

#endif // MAINWIDGET_H
