/**
  * @file
  * @brief 自定义QListWidget类
  *
  *     该文件在此工程下已经弃用
  * @version 1.0
  * @author zsj
  * @date 2019年4月24日23:14:24
  *
  *
  *
  *
  *
  *
  *
*/


#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QListWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QLineEdit>
#include <QAction>
#include <QPixmap>
#include <QDebug>
#include <QMap>
#include <QPair>
#include <QList>
#include "personlistbuddy.h"
#include "persongroup.h"
#include <cstdlib>
#include <utility>
#include <QVector>
#include <typeinfo>

#define Cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"


/*实现好友选择界面的好友列表
 * 包括分组
 *
 *
 *
 */

class personList : public QListWidget
{
    Q_OBJECT
public:
    explicit personList(QWidget *parent = 0);
    //void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);  //菜单事件，显示菜单
    void initMenu();  //初始化菜单
    void initData();
    void showData(PersonGroup * pg = 0);


    /// @brief 创建原始分组列表信息
    ///
    ///     通过多次调用，每次调用添加一条好友信息到分组信息中（速度可能有点慢，待优化）
    ///     分解传入信息，创建对象添加到分组信息
    /// @param data 传入的好友信息
    void set_origin_list_loop(QString & data);

    void clearAllWidget();


    void showOriginList();   //调试用的函数
    void showFriendList();

private:
    QMenu * blankMenu;   //初始化菜单
    QMenu * groupMenu;   //点击组上的菜单
    QMenu * personMenu;  //点击人上的菜单

    QMap<QListWidgetItem*,QListWidgetItem*>groupMap;
    QMap<QListWidgetItem*,bool> isHideMap;      //判断该组是否隐藏了
    QLineEdit * groupNameEdit;                  //组的名字
    QListWidgetItem * currentItem;              //当前的项
    bool clearflag;


    /*
     * map第一个参数是好友分组信息，第二个参数是一个List，用于保存该分组下的好友
     * 第一个参数是一个Pair类型，其中第一个参数就是该分组的数据结构，第二个则是该分组是否打开
     */
    QList<QPair<PersonGroup*,QList<personListBuddy*>*>> origin_list_;  ///< 列表信息根本信息  由于刷新列表的一些操作  设置一个根本字符串
    QList<QPair<PersonGroup*,QList<personListBuddy*>*>> friendList;   //用来保存整个好友列表的信息  解决了  但是速率不太行
    QVector<bool>isHideVector;


signals:
    void chooseFriend(QString name,QString headPath);           //选择好友之后发出一个信号

public slots:
    void slotAddGroup();     //添加组
    void slotDelGroup();     //删除组
    void slotAddBuddy();     //添加好友
    void slotDelBuddy();     //删除好友
    void slotRename();       //重命名组
    void slotRenameEditFshed();   //命名完成

    void dealDispaly(QListWidgetItem *current);   //单击显示和隐藏
    void slotDoubleCilcked(QListWidgetItem * item);
};

#endif // PERSONLIST_H
