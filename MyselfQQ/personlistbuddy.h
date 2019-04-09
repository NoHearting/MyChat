#ifndef PERSONLISTBUDDY_H
#define PERSONLISTBUDDY_H

#include <QWidget>
#include <QEvent>
#include <QString>
#include <QLabel>
#include <QPalette>
#include <QPainter>
#include <QPixmap>



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
    explicit personListBuddy(QString picPath,QString n,QString s);
    void initUi();   //初始化所需资源
    bool eventFilter(QObject *, QEvent *);   //事件过滤器
    void setHeadPic(const QString & picPath){headPath = picPath;}
    void setName(const QString & n){name->setText(n);}
    void setSign(const QString & s){sign->setText(s);}
    QString getSign(){return sign->text();}
    QString getName(){return name->text();}
    QString getHeadPath(){return headPath;}

private:
    QWidget * head;  //创建一个QWidget放头像
    QLabel * name;   //用户名
    QLabel * sign;   //个性签名
    QString headPath;  //头像的路径

signals:

public slots:
};

#endif // PERSONLISTBUDDY_H
