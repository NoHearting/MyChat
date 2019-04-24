#ifndef PERSONGROUP_H
#define PERSONGROUP_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>


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
    explicit PersonGroup(QString gName,int g_num = 0);
    explicit PersonGroup(const PersonGroup & pg);
    PersonGroup & operator =(const PersonGroup & pg);
    bool operator==(const PersonGroup & pg)const;
    ~PersonGroup();
    inline QString getGroupName(){return name;}
    inline int getPersonNum(){return Num;}
    inline QString getIconPath(){return iconPath;}
    inline void setGroupName(QString n){name = n;groupName->setText(name);}
    inline void setPersonNum(int num){Num = num;personNum->setText(QString::number(num));}
    inline void setIcon(const QString & ipath){iconPath=ipath;icon->setPixmap(QPixmap(ipath));}
    inline void reverseIsHiden(){is_hide_ = !is_hide_;}
    inline bool get_is_hide(){return is_hide_;}
    void init();


    bool operator ==(const PersonGroup & perGroup);


private:
    QLabel * icon;              //图标
    QLabel * groupName;         //显示分组名
    QLabel * personNum;         //显示该组的人数
    int Num;                    //该组有多少人
    QString name;               //分组名
    QString iconPath;           //图标的路径
    bool is_hide_ = true;              ///< 分组是否隐藏  默认true(隐藏）

signals:

public slots:
};

#endif // PERSONGROUP_H
