#ifndef PERSONLISTBUDDY_H
#define PERSONLISTBUDDY_H

#include <QWidget>
#include <QEvent>
#include <QString>
#include <QLabel>
#include <QPalette>
#include <QPainter>
#include <QPixmap>
#include <QDebug>



/**
 * @brief The personListBuddy class
 * 主要实现的是QQ好友界面的显示分组和每个好友的显示
 * 利用自定义的QWidget实现
 */
class personListBuddy : public QWidget
{
    Q_OBJECT
public:
    explicit personListBuddy(QWidget *parent = 0);
    explicit personListBuddy(QString picPath);
    explicit personListBuddy(QString & id,QString & n,QString & s,bool sex,int age,bool is_vip);
    personListBuddy(const personListBuddy & plb);   //复制构造函数
    personListBuddy & operator=(const personListBuddy & plb);   //深度复制函数
    bool operator==(const personListBuddy & plb) const;  //比较
    ~personListBuddy();
    void initUi();   //初始化所需资源
    bool eventFilter(QObject *, QEvent *);   //事件过滤器
    void setHeadPic(const QString & picPath){headPath = picPath;}
    void setName(const QString & n){name->setText(n);}
    void setSign(const QString & s){sign->setText(s);}
    QString getSign(){return sign->text();}
    QString getName(){return name->text();}
    QString getHeadPath(){return headPath;}

    /// @brief 获取类中所有成员信息，并以字符串返回
    /// @param 返回所有信息
    QString get_all_info();

private:
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

signals:

public slots:
};

#endif // PERSONLISTBUDDY_H
