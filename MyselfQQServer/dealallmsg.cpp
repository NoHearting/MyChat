#include "dealallmsg.h"

DealAllMsg::DealAllMsg(QObject *parent) : QObject(parent)
{
    connect(udpSocket,&QUdpSocket::readyRead,this,[=](){
        while(udpSocket->hasPendingDatagrams())
        {
            QHostAddress addr;
            quint16 port = 0;
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(),datagram.size(),&addr,&port);
            QString oriStr = datagram.data();
            //qDebug()<<oriStr<<"   "<<this->port;
            switch(msg_type_map_[oriStr.section("##",1,1)])
            {
            case LOGIN:

            {

                DealLoginMsg * d = new DealLoginMsg(datagram.data(),addr,port);
                threadPool.start(d);     //将此线程添加到线程池
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
                GetInfo * g = new GetInfo(datagram.data(),addr,port);
                threadPool.start(g);
            }
                break;
            case UPDATA:
                break;
            }
        }
    });
}

DealAllMsg::DealAllMsg(int port)     //  此port为当前线程绑定的端口号
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port);
    this->port = port;
    //Cout<<"开始："<<port<<"|"<<QThread::currentThreadId();
    init();

}

void DealAllMsg::init()
{
    msg_type_map_["LOGIN"] = LOGIN;
    msg_type_map_["OFFLINE"] = OFFLINE;
    msg_type_map_["ADDFRIEND"] = ADD;
    msg_type_map_["DELETEFRIEND"] = DELETE;
    msg_type_map_["GETINFORMATION"] = GETINFORMATION;
    msg_type_map_["UPDATA"] = UPDATA;
    msg_type_map_["OK_GETINFO"] = OK_GETINFO;
    msg_type_map_["LOGIN_OK"] = LOGIN_OK;

    threadPool.setMaxThreadCount(10);
}

void DealAllMsg::beginThread()
{
    Cout<<"运行："<<port<<"|"<<QThread::currentThreadId();
    connect(udpSocket,&QUdpSocket::readyRead,this,[=](){
        int i = 0;
        while(udpSocket->hasPendingDatagrams())
        {
            qDebug()<<this->port<<"-------------"<<i++<<"------------";
            QHostAddress addr;
            quint16 client_port = 0;      // 客户端的端口号

            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(),datagram.size(),&addr,&client_port);

            QString oriStr = datagram.data();
            Cout<<oriStr;
            switch(msg_type_map_[oriStr.section("##",1,1)])
            {
            case LOGIN:
            {
                DealLoginMsg * d = new DealLoginMsg(datagram.data(),addr,client_port);
                threadPool.start(d);     //将此线程添加到线程池
            }
                break;
            case LOGIN_OK:
                emit login(addr.toString(),port);
            case OFFLINE:
                break;
            case ADD:
                break;
            case DELETE:
                break;
            case GETINFORMATION:
            {
                GetInfo * g = new GetInfo(datagram.data(),addr,client_port);
                threadPool.start(g);
            }
                break;
            case UPDATA:
                break;
            }
        }
    });
}

