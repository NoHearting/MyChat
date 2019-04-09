#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "makeqss.h"
#include "personlistbuddy.h"
#include "persongroup.h"
#include "personlist.h"
#include "chatwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initWindowResouce();
    ui->listWidgeMsg->setParent(ui->tabWidget->widget(0));    //设置父对象   属于哪一个选项
    groupList->setParent(ui->tabWidget->widget(1));
    groupList->setFixedSize(ui->tabWidget->width(),ui->tabWidget->height());



    connect(ui->listWidgeMsg,&personList::chooseFriend,this,[=](QString name,QString headPath)
    {
        if(chatWin==nullptr)
        {
            delete chatWin;
        }
        chatWin = new ChatWidget;
        chatWin->setWindowTitle(name);
        chatWin->show();
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mouseMoveEvent(QMouseEvent * e)
{
    QPoint afterMovePos = e->globalPos();
    if(z.x()!=0&&z.y()!=0)
    {
        QPoint moveDis = afterMovePos-z;
        move(moveDis);
    }

}

/*
    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的差值z

*/
void MainWidget::mousePressEvent(QMouseEvent * e)
{

    QPoint currGlobalPos = e->globalPos();   //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z = currGlobalPos-currLocPos;


}

/*
    鼠标放开事件，当鼠标放开时，将差值z初始化为0
*/
void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    z = QPoint(0,0);
}



/*
    initWindowResouce初始化主窗口的资源
    1.设置窗口的格式
    2.初始化一个连接   该连接用于接收登录界面的信号并处理
        2.1信号包含登录账号密码，发送到数据库服务器验证
*/
void MainWidget::initWindowResouce()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    chatWin = nullptr;
    groupList = new personList;

//    //最开始为登录界面

    ui->widgetInner->hide();
    loginWin = new LoginWidget;
    loginWin->show();
    initUdpSocket();
    connect(loginWin,&LoginWidget::loginOk,[=](QString id,QString pwd){    //接收到登录的消息
        //操作
        qDebug()<<"收到响应";
        QString loginData = QString("##%1##%2##").arg(id).arg(pwd);
        qint64 len = udpSocket->writeDatagram(loginData.toUtf8(),QHostAddress("127.0.0.1"),10001);   //发送到服务器进行验证
        qDebug()<<"发送了"<<len<<"字节";

    });

    setMainWinShadow();   //设置主窗口阴影

}

/*
    initUdpSocket函数作用：
    1.初始化udpSocket  申请内存  绑定到固定端口
    2.初始化一个连接  该连接用于读取从数据库服务器发来的数据
    3.用读取到的数据判断是否登录成功

*/
void MainWidget::initUdpSocket()   //初始化udpsocket
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(10000);           //绑定到10000端口
    connect(udpSocket,&QUdpSocket::readyRead,this,[=](){     //发送消息之后必须接受消息
       while(udpSocket->hasPendingDatagrams())
       {
           QMessageBox::about(this," ","收到回复消息");
           char buff[1024] = {0};
           QHostAddress serverAddr;     //对方地址
           quint16 port;
           qint64 len = udpSocket->readDatagram(buff,sizeof(buff),&serverAddr,&port);
           if(len>0)
           {

               if(QString("true") == buff)
               {
                   loginWin->setIsLogin(true);
               }
               if(loginWin->getIsLogin())
               {
                   loginWin->close();
                   ui->widgetInner->show(); //显示出主窗口
                   this->show();
               }
               else
               {
                   QMessageBox::warning(this,"警告","登录错误",QMessageBox::Ok);
               }

           }
       }
    });

}

void MainWidget::setMainWinShadow()
{
    this->setStyleSheet(makeQSS::getStyleSheet(":/Qss/MainWidgetQSS.qss")+makeQSS::getStyleSheet(":/Qss/ListWidgetQSS.qss"));
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);         //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->widgetInner->setGraphicsEffect(shadow);
}


void MainWidget::on_toolButtonMsg_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButtonMove->setChecked(false);    //设置按钮为未被选中
    ui->toolButtonLinkMan->setChecked(false);
}

void MainWidget::on_toolButtonLinkMan_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButtonMove->setChecked(false);
    ui->toolButtonMsg->setChecked(false);

}

void MainWidget::on_toolButtonMove_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButtonLinkMan->setChecked(false);
    ui->toolButtonMsg->setChecked(false);
}

void MainWidget::on_toolButtonCLose_clicked()
{
    close();
}

void MainWidget::on_toolButtonMin_clicked()
{
    showMinimized();   //最小化显示窗口

}
