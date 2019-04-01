#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    initChatWindowResouce();
}

ChatWidget::~ChatWidget()
{
    delete ui;
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
