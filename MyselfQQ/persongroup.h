#ifndef PERSONGROUP_H
#define PERSONGROUP_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>


/*
 * 实现qq聊天界面中的分组信息
 *
 *
 *
 */


class PersonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit PersonGroup(QWidget *parent = 0);
    explicit PersonGroup(QString gName);
    inline QString getGroupName(){return name;}
    inline int getPersonNum(){return Num;}
    inline QString getIconPath(){return iconPath;}
    inline void setGroupName(QString n){name = n;groupName->setText(name);}
    inline void setPersonNum(int num){Num = num;personNum->setText(QString::number(num));}
    inline void setIcon(const QString & ipath){iconPath=ipath;icon->setPixmap(QPixmap(ipath));}
    void init();


    bool operator ==(const PersonGroup & perGroup);


private:
    QLabel * icon;              //图标
    QLabel * groupName;         //显示分组名
    QLabel * personNum;         //显示该组的人数
    int Num;                    //该组有多少人
    QString name;               //分组名
    QString iconPath;           //图标的路径

signals:

public slots:
};

#endif // PERSONGROUP_H
