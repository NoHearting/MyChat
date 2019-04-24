#include "persongroup.h"

PersonGroup::PersonGroup(QWidget *parent) : QWidget(parent)
{
    groupName = new QLabel(this);
    icon = new QLabel(this);
    personNum = new QLabel(this);
    init();
    name = QString("");
    iconPath = QString("");
    Num = 0;
}

PersonGroup::PersonGroup(QString gName,int g_num):name(gName),Num(g_num)
{
    groupName = new QLabel(this);
    icon = new QLabel(this);
    personNum = new QLabel(this);
    groupName->setText(gName);
    iconPath = QString("");
    init();
}

PersonGroup::PersonGroup(const PersonGroup &pg)
{

    /*QLabel * icon;              //图标
    QLabel * groupName;         //显示分组名
    QLabel * personNum;         //显示该组的人数
    int Num;                    //该组有多少人
    QString name;               //分组名
    QString iconPath;           //图标的路径
    bool is_hide_ = true;              ///< 分组是否隐藏  默认true(隐藏）*/

    icon = new QLabel(this);
    groupName = new QLabel(this);
    personNum = new QLabel(this);

    Num = pg.Num;
    name = pg.name;
    iconPath = pg.iconPath;
    is_hide_ = pg.is_hide_;
    init();
    groupName->setText(name);
    //qDebug()<<"------------------------------复制构造:PersonGroup   "<<name;
}

PersonGroup &PersonGroup::operator =(const PersonGroup &pg)
{
    if(*this==pg)
    {
        return *this;
    }

    /*QLabel * icon;              //图标
    QLabel * groupName;         //显示分组名
    QLabel * personNum;         //显示该组的人数
    int Num;                    //该组有多少人
    QString name;               //分组名
    QString iconPath;           //图标的路径
    bool is_hide_ = true;              ///< 分组是否隐藏  默认true(隐藏）*/

    QLabel * p_icon_old = icon;
    icon = new QLabel(this);
    delete p_icon_old;

    QLabel * p_groupName_old = groupName;
    groupName = new QLabel(this);
    delete p_groupName_old;

    QLabel * p_personNum_old = personNum;
    personNum = new QLabel(this);
    delete p_personNum_old;

    Num = pg.Num;
    name = pg.name;
    iconPath = pg.iconPath;
    is_hide_ = pg.is_hide_;

    init();
    groupName->setText(name);

}

// 比较条件  不要一些控件
bool PersonGroup::operator==(const PersonGroup &pg) const
{
    return (Num == pg.Num)&&(name==pg.name)&&(iconPath==pg.iconPath)&&(is_hide_==pg.is_hide_);
}

PersonGroup::~PersonGroup()
{
    qDebug()<<"PersonGroup析构：  "<<name;
}

void PersonGroup::init()
{
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    personNum->setPalette(color);

    icon->setFixedSize(20,20);
    personNum->setFixedSize(60,20);
    groupName->setFixedSize(60,20);


    icon->move(10,10);
    groupName->move(30,10);
    personNum->move(90,10);
}

bool PersonGroup::operator ==(const PersonGroup & perGroup)
{
    if((iconPath==perGroup.iconPath)&&(perGroup.name==name)&&(perGroup.Num==Num))
    {
        return true;
    }
    else
    {
        return false;
    }

}

