#include "registerwidget.h"
#include "ui_registerwidget.h"

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    initWindowResoure();   //初始化窗口的资源与美化
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::initWindowResoure()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    setRegisWindowShadow();
}

void RegisterWidget::setRegisWindowShadow()
{
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->stackedWidget->setGraphicsEffect(shadow);

    this->setStyleSheet("#stackedWidget{background-color:rgba(0,255,255,90);}"
                        "QPushButton{background-color:rgb(29,197,252);color:white;border:none;border-radius:3px;}"//初始格式
                        "QPushButton:hover{background-color:rgb(89,210,248);}"
                        "QLineEdit:focus{border:1px solid #ee34c9;border-radius:3px;}");
}

void RegisterWidget::on_toolButton_2_clicked()
{
    close();
}

void RegisterWidget::on_toolButton_3_clicked()
{
    close();
}

void RegisterWidget::mouseMoveEvent(QMouseEvent * e)
{
    QPoint afterMovePos = e->globalPos();
    if(z.x()!=0&&z.y()!=0)
    {
        QPoint moveDis = afterMovePos-z;
        move(moveDis);
    }

}

/*
    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的差值z

*/
void RegisterWidget::mousePressEvent(QMouseEvent * e)
{

    QPoint currGlobalPos = e->globalPos();   //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z = currGlobalPos-currLocPos;


}

/*
    鼠标放开事件，当鼠标放开时，将差值z初始化为0
*/
void RegisterWidget::mouseReleaseEvent(QMouseEvent *)
{
    z = QPoint(0,0);
}

void RegisterWidget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
