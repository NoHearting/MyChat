#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget),is_close_(false)
{
    ui->setupUi(this);
    initChatWindowResouce();
}

ChatWidget::ChatWidget(personListBuddy * plb)
    :ui(new Ui::ChatWidget),is_close_(false)
{
    qDebug()<<"进入";
    ui->setupUi(this);
    qDebug()<<"11111";
    initChatWindowResouce();
    qDebug()<<"XXXXXXx";
    chat_obj_ = shared_ptr<personListBuddy>(new personListBuddy(*plb));
    this->show();
    this->setWindowTitle(chat_obj_->getName());
}

ChatWidget::~ChatWidget()
{
    delete ui;
    qDebug()<<"ChatWidget析构";
}

void ChatWidget::initChatWindowResouce()
{
    this->setStyleSheet("#ChatWidget{background-color:white;}"
                        "#textBrowser,#textEdit,#widget,#widgetchoose{border:none;border-style:outset;border-right:1px solid rgb(240,239,239);}"
                        "#textBrowser{border-bottom:1px solid rgb(240,239,239);}"
                        "#pushButtonclose{background-color:white;}"
                        "#pushButtonMore,#pushButtonSend{background-color:rgb(176,156,227);border-right:3px solid rgb(176,156,227); }"
                        "QPushButton{border:1px solid rgb(240,239,239);background:transparent;border-radius:3px;}"
                        "#pushButtonclose:hover{background-color:rgb(239,239,240);}"
                        "#pushButtonMore:hover,#pushButtonSend:hover{background-color:rgb(193,178,223);}");
}

void ChatWidget::closeEvent(QCloseEvent * temp)
{
    //emit closeChatWindow(chat_obj_->get_id());
    //qDebug()<<"该窗口为关闭状态:   "<<chat_obj_->getName();
    is_close_ = true;
}

void ChatWidget::on_pushButtonSend_clicked()
{
    QString info = ui->textEdit->toPlainText();
    emit sendMessages(info,chat_obj_->get_id());   //发送信号
    ui->textBrowser->moveCursor(QTextCursor::End); //每次都在底部
    ui->textBrowser->append(info);
}
