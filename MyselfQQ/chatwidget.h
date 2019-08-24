/**
  * @file
  * @brief 聊天界面
  *
  *     qq聊天界面，类似于qq，还不完善
  *
  *
  *
  *
*/

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <personlistbuddy.h>
#include <memory>
#include <QDebug>
#include <QEvent>
#include <QCloseEvent>

#include "makeqss.h"
using namespace std;

namespace Ui {
class ChatWidget;
}


/// @class ChatWidget
/// @brief 聊天界面
///
///     聊天界面类
/// @version 1.0
/// @note 现在还未开发完全
class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    explicit ChatWidget(personListBuddy * plb);
    ~ChatWidget();

    /// @brief 初始化聊天界面的初始设置
    ///
    ///     初始设置包括窗口基本设置
    void initChatWindowResouce();
	
	/// @brief 获取聊天对象的id
	/// 
    QString get_chatobj_id(){return chat_obj_->get_id();}
	
	/// @brief 获取当前窗口的状态
	///	
	/// 窗口状态为开关
    inline bool get_is_close(){return is_close_;}
signals:
    //void closeChatWindow(QString window_id);
    void sendMessages(QString,QString);
protected:

    /// @brief 重写closeEvent函数
    ///
    ///     此函数发生时设置本窗口设置为关闭状态，等待主窗口删除内存
    void closeEvent(QCloseEvent *);

private slots:
    void on_pushButtonSend_clicked();

private:
    Ui::ChatWidget *ui;
    shared_ptr<personListBuddy> chat_obj_;    ///< 选择的聊天对象
    bool is_close_;    ///< 窗口是否关闭
};

#endif // CHATWIDGET_H
