#include "getinfo.h"




void GetInfo::run()
{
    qDebug()<<"GetInfo 线程号："<<QThread::currentThreadId();
    getFriendInfo();
    sendFriendInfo();
}

void GetInfo::getFriendInfo()
{
    QSqlQuery query;
    QString id = dealData.section("##",2,2);  //获取账号

    //获取分组的名称和好友数量
    QString sqlGetGroupName = QString("select friendName,friendNum from friendInfo where friendOwnerId = %1").arg(id);
    query.exec(sqlGetGroupName);
    while(query.next())   //获取到分组信息
    {
        //分组信息和人数放入  first成员
        groupDataList.push_back( QPair<QString,QList<QString>*>(QString("##%1##%2").
                                                                arg(query.value(0).toString()).
                                                                arg(query.value(1).toString()),new QList<QString>()) );
        //qDebug()<<query.value(0).toString();
    }

    QString sqlGetFriendInfo = QString("select UserInfo.*,tt.friendName "
                                       " from UserInfo "
                                       " join "
                                       "(select user_friend.user_id,t.friendId,t.friendName"
                                       "    from user_friend"
                                       "    join (select friendId,friendName from friendInfo where friendOwnerId = %1) t "
                                       "    on user_friend.friend_id = t.friendId"
                                       ") tt "
                                       " on UserInfo.userId = tt.user_id ").arg(id);
    //query.clear();   //清除结果集

    QSqlQuery queryInfo;
    queryInfo.exec(sqlGetFriendInfo);
    while(queryInfo.next())
    {
        for(auto iter = groupDataList.begin();iter!=groupDataList.end();iter++)
        {
            QString fInfo = QString("##%1##%2##%3##%4##%5##%6##%7##").
                    arg(queryInfo.value(0).toString()).
                    arg(queryInfo.value(2).toString()).
                    arg(queryInfo.value(3).toString()).
                    arg(queryInfo.value(4).toString()).
                    arg(queryInfo.value(5).toString()).
                    arg(queryInfo.value(6).toString()).
                    arg(queryInfo.value(7).toString());

            //将该用户好友信息放入groupDataList中
            if(iter->first.section("##",1,1) == queryInfo.value(8).toString())
            {
                iter->second->push_back(fInfo);
                break;
            }
        }
    }

}

void GetInfo::sendFriendInfo()
{
    shared_ptr<QUdpSocket> pUdpsocket(new QUdpSocket());
    for(auto iter = groupDataList.begin();iter!=groupDataList.end();iter++)
    {
        QString group = iter->first;   //拿到头
        for(auto it = iter->second->begin();it!=iter->second->end();it++)
        {
            QString Msg = "##GETINFORMATION"+group+(*it);
            //qDebug()<<Msg;
            int len = pUdpsocket->writeDatagram(Msg.toUtf8(),addr,port);
            if(len<0)
            {
                qDebug()<<"发送失败";
            }
        }
    }
    int len = pUdpsocket->writeDatagram(QString("##OK_GETINFO##").toUtf8(),addr,port);

}
