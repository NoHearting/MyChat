#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initWindowResouce();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mouseMoveEvent(QMouseEvent * e)
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
void MainWidget::mousePressEvent(QMouseEvent * e)
{

    QPoint currGlobalPos = e->globalPos();   //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z = currGlobalPos-currLocPos;


}

/*
    鼠标放开事件，当鼠标放开时，将差值z初始化为0
*/
void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    z = QPoint(0,0);
}

void MainWidget::initWindowResouce()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明


//    //最开始为登录界面

    //this->hide();
    ui->widgetInner->hide();
    loginWin = new LoginWidget;
    loginWin->show();
    connect(loginWin,&LoginWidget::loginOk,[=](QString id,QString pwd){    //接收到登录的消息
        //操作   访问数据库。。。。
        qDebug()<<"进入";
        loginWin->setIsLogin(true);   //假设登录成功
        loginWin->close();

        ui->widgetInner->show(); //显示出主窗口
        this->show();
    });

    setMainWinShadow();

}

void MainWidget::setMainWinShadow()
{
    this->setStyleSheet("#widgetInner{background-color:rgba(238,52,201,85);border-radius:5px;}"
                        "#widgetInnerHead{background-color:rgba(52,238,89,90);}"
                        "#stackedWidget{background-color:rgba(247,212,18,90);}"
                        "QLineEdit{background:transparent;border-width:0;border-style:outset;}"
                        "QLineEdit:focus{background-color:white;}"
                        "#lineEditSign:hover:!focus{border:1px solid gray;}");
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->widgetInner->setGraphicsEffect(shadow);
}

void MainWidget::on_toolButton_2_clicked()
{
    close();
}
