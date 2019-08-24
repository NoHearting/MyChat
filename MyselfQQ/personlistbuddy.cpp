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

personListBuddy::personListBuddy(QString & id,QString & n,QString & s,bool sex,int age,bool is_vip)
    :id_(id),nick_name_(n),sign_name_(s),sex_(sex),age_(age),is_vip_(is_vip)
{
    headPath = "://C:/Users/ASUS/Pictures/ImageMaterials/circleHeadMain.png";   //先给一个图片
    head = new QWidget(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    initUi();
    setSign(s);
    setName(n);
}

personListBuddy::personListBuddy(const personListBuddy & plb)
{
    qDebug()<<"----------------------复制构造：personListBuddy";
    /*
    QWidget * head;  //创建一个QWidget放头像
    QLabel * name;   //用户名
    QLabel * sign;   //个性签名

    QString sign_name_;  //签名
    QString nick_name_;  //昵称
    QString headPath;  //头像的路径
    QString id_;     //账号
    bool sex_;      //性别
    int age_;       //年龄
    bool is_vip_;    //是否vip

*/
    head = new QWidget(this);    //Qwidget  不允许复制构造函数
    //head = new QWidget();
    name = new QLabel(this);
    sign = new QLabel(this);

    sign_name_ = plb.sign_name_;
    nick_name_ = plb.nick_name_;
    headPath = plb.headPath;
    id_ = plb.id_;
    sex_ = plb.sex_;
    age_ = plb.age_;
    is_vip_ = plb.is_vip_;

    initUi();

    name->setText(nick_name_);
    sign->setText(sign_name_);

    //qDebug()<<"----------------------复制构造：personListBuddy"<<nick_name_;
}

personListBuddy &personListBuddy::operator=(const personListBuddy &plb)
{
    if(plb==*this)   //自己给自己赋值  不处理
    {
        return *this;
    }

    /*
    QWidget * head;  //创建一个QWidget放头像
    QLabel * name;   //用户名
    QLabel * sign;   //个性签名

    QString sign_name_;  //签名
    QString nick_name_;  //昵称
    QString headPath;  //头像的路径
    QString id_;     //账号
    bool sex_;      //性别
    int age_;       //年龄
    bool is_vip_;    //是否vip
    */

    //  此做法参照 Effective C++  page:55   异常安全性
    QWidget * p_head_old = head;
    head = new QWidget();
    delete p_head_old;

    QLabel * p_name_old = name;
    name = new QLabel();
    delete p_name_old;

    QLabel * p_sign_old = sign;
    sign = new QLabel();
    delete p_sign_old;

    sign_name_ = plb.sign_name_;
    nick_name_ = plb.nick_name_;
    headPath = plb.headPath;
    id_ = plb.id_;
    sex_ = plb.sex_;
    age_ = plb.age_;
    is_vip_ = plb.is_vip_;
}

bool personListBuddy::operator==(const personListBuddy &plb)const
{
    return (head==plb.head)&&(name==plb.name)&&(sign==plb.sign)
            &&(sign_name_ == plb.sign_name_)&&(nick_name_ == plb.nick_name_)
            &&(headPath==plb.headPath)&&(id_ == plb.id_)
            &&(sex_ == plb.sex_)&&(age_ == plb.age_)&&(is_vip_ == plb.is_vip_);
}

personListBuddy::~personListBuddy()
{
    qDebug()<<"personListBuddy析构: "<<nick_name_;
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

QString personListBuddy::get_all_info()
{
    QString t = id_+nick_name_+sign_name_+QString::number(sex_)+QString::number(age_)+QString::number(is_vip_);
    return t;
}

