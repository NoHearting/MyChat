#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initDatabase();
    init();

    /*
        两个bug：
        1.readyread不是每次接收到消息都会触发，情况是接收第一次后都不再触发
            解决方案：调用hasPendingDatagrams()函数，该函数检查如果该socket有至少一个数据报，返回true，否则返回false
                    调用后逻辑上形成只要收到消息就处理
        2.udpSocket无法作为形参传递给新线程，会出现跨界（跨线程）调用，出现错误（简单解决）

    */






//    iscon = connect(udpSocket,&QUdpSocket::readyRead,this,[=](){
//        while(udpSocket->hasPendingDatagrams())
//        {
//            QHostAddress addr;
//            quint16 port = 0;
//            QByteArray datagram;
//            datagram.resize(udpSocket->pendingDatagramSize());
//            udpSocket->readDatagram(datagram.data(),datagram.size(),&addr,&port);
//            QString oriStr = datagram.data();
//            switch(msgTypeMap[oriStr.section("##",1,1)])
//            {
//            case LOGIN:
//                //QMessageBox::about(this," ",datagram.data());
//            {
//                ui->textBrowser->append(datagram.data());
//                ui->textBrowser->append("有新消息");
//                //QMessageBox::about(this," ","有新消息");
//                DealLoginMsg * d = new DealLoginMsg(datagram.data(),addr,port);
//                threadPool.start(d);     //将此线程添加到线程池
//            }
//                break;
//            case OFFLINE:
//                break;
//            case ADD:
//                break;
//            case DELETE:
//                break;
//            case GETINFORMATION:
//            {
//                ui->textBrowser->append("获取好友分组信息");
//                GetInfo * g = new GetInfo(datagram.data(),addr,port);
//                threadPool.start(g);
//            }
//                break;
//            case UPDATA:
//                break;
//            }



//        }

//    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initDatabase()
{

    if(Widget::connectDatabase())
    {
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->setCurrentFont(QFont("楷体",12));
        ui->textBrowser->append("连接数据库成功");
    }
    else
    {
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->setCurrentFont(QFont("楷体",12));
        ui->textBrowser->append("连接数据库失败");
    }

}

void Widget::init()
{

    /*LOGIN,   //登录信息类型
             OFFLINE, //离线信息类型
             ADDFRIEND,  //添加朋友
             DELETEFRIEND, // 删除朋友
             GETINFORMATION,  //获取好友信息
             UPDATA   //更新信息，包括创建，删除分组、群
             */
    msgTypeMap["LOGIN"] = LOGIN;
    msgTypeMap["OFFLINE"] = OFFLINE;
    msgTypeMap["ADDFRIEND"] = ADD;
    msgTypeMap["DELETEFRIEND"] = DELETE;
    msgTypeMap["GETINFORMATION"] = GETINFORMATION;
    msgTypeMap["UPDATA"] = UPDATA;
    msgTypeMap["OK_GETINFO"] = OK_GETINFO;

    threadPool.setMaxThreadCount(10);
    thread_verctor_.resize(5);   ///<  设置5个接收线程  接收客户端发来的消息
    dealallmsg_vector_.resize(5);
    qDebug()<<"主线程id:  "<<QThread::currentThreadId();
    for(int i = 0;i<5;i++)
    {

        thread_verctor_[i] = new QThread();
        dealallmsg_vector_[i] =  new DealAllMsg(10001+i);
        dealallmsg_vector_[i]->moveToThread(thread_verctor_[i]);
        thread_verctor_[i]->start();
        connect(this,&Widget::startThread,dealallmsg_vector_[i],&DealAllMsg::beginThread);
        emit startThread();
        connect(dealallmsg_vector_[i],&DealAllMsg::login,this,[=](QString ha,quint16 port){
            ui->textBrowser->append(ha+":"+QString::number(port));
        });
    }


}





void Widget::slotDealMsg()
{


}

QSqlDatabase Widget::db = QSqlDatabase::addDatabase("QMYSQL");

bool Widget::connectDatabase()
{
    //dealClientMsg::db = QSqlDatabase::addDatabase("QMYSQL");   //添加mysql数据库

    Widget::db.setHostName("127.0.0.1");          //设置主机ip
    Widget::db.setUserName("root");               //给一个root用户
    Widget::db.setPassword("z1762861794");        //密码
    Widget::db.setDatabaseName("chatinfo");       //设置数据库
    if(!Widget::db.open())
    {
        //ui->label->setText("数据库打开失败"+db.lastError().text());
        //QMessageBox::warning(0,"错误","数据库打开失败",QMessageBox::Ok);
        return false;
    }
    else
    {
        //QMessageBox::information(0,"信息","数据库打开成功",QMessageBox::Ok);
        return true;
    }
}

void Widget::on_pushButton_clicked()
{


}

void Widget::on_pushButton_2_clicked()
{

}
