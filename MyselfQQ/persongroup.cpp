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

PersonGroup::PersonGroup(QString gName)
{
    groupName = new QLabel(this);
    icon = new QLabel(this);
    personNum = new QLabel(this);
    groupName->setText(gName);
    name = gName;
    iconPath = QString("");
    Num = 0;
    init();
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

