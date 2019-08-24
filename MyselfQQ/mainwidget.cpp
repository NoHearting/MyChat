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


    connect(ui->listWidgeMsg,&QListWidget::itemClicked,this,&MainWidget::slotDealClicked);
    connect(ui->listWidgeMsg,&QListWidget::itemDoubleClicked,this,&MainWidget::deal_double_clicked);
    Cout<<udp_port_<<"*************************";
    Cout<<local_port<<" local_port";
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
    srand(time(0));
    local_port = rand()%5+20001;
    udp_port_ = rand()%5+10001;
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    chatWin = nullptr;
    groupList = new personList;
    msg_type_map_["LOGIN"] = LOGIN;
    msg_type_map_["OFFLINE"] = OFFLINE;
    msg_type_map_["ADD"] = ADD;
    msg_type_map_["DELETE"] = DELETE;
    msg_type_map_["GETINFORMATION"] = GETINFORMATION;
    msg_type_map_["UPDATA"] = UPDATA;
    msg_type_map_["OK_GETINFO"] = OK_GETINFO;

//            enum msgType{LOGIN,   //登录信息类型
//                         OFFLINE, //离线信息类型
//                         ADD,  //添加
//                         DELETE, // 删除
//                         GETINFORMATION,  //获取好友信息
//                         UPDATA   //更新信息，包括创建，删除分组、群
//                        };
//    //最开始为登录界面

    ui->widgetInner->hide();
    loginWin = new LoginWidget;
    loginWin->show();
    initUdpSocket();

    connect(loginWin,&LoginWidget::loginOk,[=](QString id,QString pwd){    //接收到登录的消息
        //操作
        uId = id;
        password = pwd;
        Cout<<"收到响应";
        QString loginData = QString("##%1##%2##%3##").arg("LOGIN").arg(id).arg(pwd);


        qint64 len = udpSocket->writeDatagram(loginData.toUtf8(),QHostAddress("127.0.0.1"),udp_port_);   //发送到服务器进行验证
        Cout<<"发送了"<<len<<"字节";

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
    udpSocket->bind(local_port);           //绑定到端口
    connect(udpSocket,&QUdpSocket::readyRead,this,[=](){     //发送消息之后必须接受消息
       while(udpSocket->hasPendingDatagrams())
       {
           //QMessageBox::about(this," ","收到回复消息");
           Cout<<"收到回复消息";
           char buff[1024] = {0};
           QHostAddress serverAddr;     //对方地址
           quint16 port;

           qint64 len = udpSocket->readDatagram(buff,sizeof(buff),&serverAddr,&port);

           if(len<0)
           {
               continue;
           }
           QString oriStr = QString(buff);
           Cout<<oriStr;
           switch(msg_type_map_[oriStr.section("##",1,1)])   //判断消息头代表何种消息类型
           {
           case LOGIN:
               //QMessageBox::about(this," ",datagram.data());
           {
               if(QString("true") == oriStr.section("##",2,2))
               {
                   loginWin->setIsLogin(true);
                   Cout<<"开始获取消息";
                   udpSocket->writeDatagram(QString("##LOGIN_OK##").arg(uId).arg(password).toUtf8(),QHostAddress("127.0.0.1"),udp_port_);
                   udpSocket->writeDatagram(QString("##GETINFORMATION##%1##%2##").arg(uId).arg(password).toUtf8(),QHostAddress("127.0.0.1"),udp_port_);   //发送到服务器进行验证
               }


               // 应该放到接收完消息后显示
               //  测试   不关闭窗口
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
               break;
           case OFFLINE:
               break;
           case ADD:
               break;
           case DELETE:
               break;
           case GETINFORMATION:
           {
//               Cout<<oriStr;
               set_friend_list_info(oriStr);
           }
               break;
           case UPDATA:
               break;
           case OK_GETINFO:
           {
               Cout<<"-----------------------------------";
               Cout<<"\n\n\n\n";
               showFriendListInfo();
//               temp();
               //assignTemp();
           }
               break;
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

void MainWidget::set_friend_list_info(QString &data)
{
    //分离data字符串中的数据
    Cout<<"set_friend_list_info";
    QString group_name = data.section("##",2,2);
    int group_num = data.section("##",3,3).toInt();
    QString friend_id = data.section("##",4,4);
    QString friend_nickname = data.section("##",5,5);
    QString friend_sign_name = data.section("##",6,6);
    QString friend_head_path = data.section("##",7,7);   //头像信息有问题  暂时不用
    bool friend_is_vip = data.section("##",8,8).toInt();
    int friend_age = data.section("##",9,9).toInt();
    bool friend_sex = data.section("##",10,10).toInt();

    if(origin_list_.size()<=0)   //当前分组列表里面没有分组则添加一个
    {
        origin_list_.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(
                                   new PersonGroup(group_name,group_num),
                                   new QList<personListBuddy*>()));

    }

    bool insert_flag = false;
    for(auto iter = origin_list_.begin();iter!=origin_list_.end();iter++)
    {
        if(iter->first->getGroupName() == group_name)   //如果存在此组  就将好友加到此组
        {
            insert_flag = true;
            iter->second->push_back(new personListBuddy(friend_id,friend_nickname,friend_sign_name,friend_sex,friend_age,friend_is_vip));
        }

    }
    if(!insert_flag)
    {
        origin_list_.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(
                                   new PersonGroup(group_name,group_num),
                                   new QList<personListBuddy*>()));
        set_friend_list_info(data);
    }
}

void MainWidget::showFriendListInfo(PersonGroup * pg)
{

    //QList<QPair<PersonGroup*,QList<personListBuddy*>*>> origin_list_
    for(auto iter = origin_list_.begin();iter!=origin_list_.end();iter++)
    {


        QListWidgetItem * item = new QListWidgetItem();
        ui->listWidgeMsg->addItem(item);
        /*
            问题：void QListWidget::setItemWidget(QListWidgetItem * item, QWidget * widget)
            函数传入的参数是指针，如果清空QListWidget，会释放其指向的内存
            恰好，这个程序需要多次释放，出现重大bug，现在稍微解决了一下

        */
        ui->listWidgeMsg->setItemWidget(item,new PersonGroup(*(iter->first)));
        item->setSizeHint(QSize(ui->listWidgeMsg->width(),36));

        if(pg!=nullptr&&(*pg)==*(iter->first))   // 选中的是分组
        {
            iter->first->reverseIsHiden();
        }
        if(!iter->first->get_is_hide())
        {
            for(auto itList = iter->second->begin();itList!=iter->second->end();itList++)
            {
                QListWidgetItem * itemL = new QListWidgetItem();
                ui->listWidgeMsg->addItem(itemL);
                ui->listWidgeMsg->setItemWidget(itemL,new personListBuddy(*(*itList)));
                itemL->setSizeHint(QSize(ui->listWidgeMsg->width(),60));

            }
        }
    }
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

void MainWidget::slotDealClicked(QListWidgetItem * current)
{
    QWidget * currWidget = current->listWidget()->itemWidget(current);
    PersonGroup * temp = nullptr;
    if(typeid(*currWidget)==typeid(PersonGroup))   //如果点击的是分组选项
    {
        Cout<<"PersonGroup";
        temp = (dynamic_cast<PersonGroup*>(currWidget));
        PersonGroup * t = new PersonGroup(*temp);
        //temp->setHidden(true);
        disconnect(ui->listWidgeMsg,&QListWidget::itemClicked,this,&MainWidget::slotDealClicked);
        ui->listWidgeMsg->clear();
        showFriendListInfo(t);
        connect(ui->listWidgeMsg,&QListWidget::itemClicked,this,&MainWidget::slotDealClicked);

    }
    else if(typeid(*currWidget)==typeid(personListBuddy))  //如果是好友选项
    {
        Cout<<"personListBuddy";
        return;
    }


}

void MainWidget::deal_double_clicked(QListWidgetItem * item)
{
    Cout<<"size:   "<<list_chat_window_.size();
    if(list_chat_window_.size()>50)   //50个窗口开始清理
    {
        close_chat_window();
    }

    QWidget * currWidget = item->listWidget()->itemWidget(item);
    if(typeid(*currWidget)==typeid(personListBuddy))   //如果点击的是分组选项
    {
        personListBuddy * temp = (dynamic_cast<personListBuddy*>(currWidget));

        list_chat_window_.push_back(shared_ptr<ChatWidget>(new ChatWidget(temp)));
    }



}

void MainWidget::close_chat_window()
{
    for(auto iter = list_chat_window_.begin();iter!=list_chat_window_.end();)
    {
        if((*iter)->get_is_close())
        {
            list_chat_window_.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}
