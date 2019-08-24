#include "dealloginmsg.h"


DealLoginMsg::DealLoginMsg(QString msg,QHostAddress Addr,quint16 p):addr(Addr),port(p)
{
    //this->udpSocket = udpSocket;
    this->msg = msg;
}

void DealLoginMsg::run()
{
    Cout<<"DealLoginMsg 线程号："<<QThread::currentThreadId();
    udpSocket = new QUdpSocket();
    QString id = msg.section("##",2,2);
    QString password = msg.section("##",3,3);
    password.append(0);
    if(isTrueUser(id,password))
    {
        udpSocket->writeDatagram(QString("##LOGIN##true##").toUtf8(),addr,port);   //收到数据后返回
    }
    else
    {
        udpSocket->writeDatagram(QString("##LOGIN##false##").toUtf8(),addr,port);
    }
    delete udpSocket;
    udpSocket = nullptr;
}

bool DealLoginMsg::isTrueUser(QString id, QString password)
{
    Cout<<id<<"|"<<password;
    QSqlQuery query;      //数据库类是单例设计模式  这里的query会自动匹配该数据库类
    QString sql = QString("select * from userinfo where userId=%1 and userPassword='%2'").arg(id).arg(password);
    query.exec(sql);           //执行此命令

    if(query.next())
    {
        return true;
    }
    return false;

}



