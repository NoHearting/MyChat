#include "personlistbuddy.h"

personListBuddy::personListBuddy(QWidget *parent) : QWidget(parent)
{
    head = new QWidget(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    initUi();
}

personListBuddy::personListBuddy(QString picPath):headPath(picPath)
{
    head = new QWidget(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    initUi();
}

personListBuddy::personListBuddy(QString picPath, QString n, QString s)
{
    headPath = picPath;
    head = new QWidget(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    initUi();
    setSign(s);
    setName(n);
}

void personListBuddy::initUi()
{
    //设置头像大小
    head->setFixedSize(40,40);

    //设置个性签名颜色为灰色
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    sign->setPalette(color);

    //简单布局
    head->move(7,7);
    name->move(54,10);
    sign->move(54,27);

    //装载事件过滤器
    head->installEventFilter(this);
}

bool personListBuddy::eventFilter(QObject * obj, QEvent *event)
{
    if(head==obj)
    {
        if(event->type()==QEvent::Paint)
        {
            QPainter painter(head);
            painter.drawPixmap(head->rect(),QPixmap(headPath));
        }
    }
    return QWidget::eventFilter(obj,event);   //响应其他事件
}

