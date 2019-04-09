#include "loginwidget.h"
#include "ui_loginwidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initWindowResouce();   //初始化
}

LoginWidget::~LoginWidget()
{
    delete ui;
}


/*
  鼠标移动事件，解决无边框的窗口无法移动问题



    bug：
    移动时如果点到控件再移动会出现无法移动的情况，然后移出控件区该界面会随意乱跳

    解决办法：
    通过调试发现，点击控件时并不获取当前鼠标的位置，
    则只需在移动的时候判断z值是否有值就能安全解决

*/
void LoginWidget::mouseMoveEvent(QMouseEvent * e)
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
void LoginWidget::mousePressEvent(QMouseEvent * e)
{

    QPoint currGlobalPos = e->globalPos();   //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z = currGlobalPos-currLocPos;


}

/*
    鼠标放开事件，当鼠标放开时，将差值z初始化为0
*/
void LoginWidget::mouseReleaseEvent(QMouseEvent *)
{
    z = QPoint(0,0);
}

/*
    初始化基本界面

    1.设置外层窗口无边框，并这是阴影
    2.播放窗口上的一个QLabel，播放内容为GIF
    3.给当前窗口中的输入账号框添加两个内容，测试效果
    4.初始化窗口移动需要的差值变量为0

*/
void LoginWidget::initWindowResouce()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    this->setLoginWidgetShadow();    //设置阴影


    QMovie * movie = new QMovie("://C:/Users/ASUS/Pictures/GIf/move.gif");
    ui->labelMovePic->setMovie(movie);
    movie->start();
    movie->setParent(this);   //自动回收资源

    ui->comboBoxUserID->addItem("傻逼  第一个");
    ui->comboBoxUserID->addItem("猪头  第二个");

    z = QPoint(0,0);

    regis = nullptr;      //先给注册窗口的指针赋空

    isLogin = false;
}

void LoginWidget::setIsLogin(bool flag)
{
    isLogin = flag;
}


//设置主窗口阴影效果
void LoginWidget::setLoginWidgetShadow()
{
    this->setStyleSheet("#LoginwidgetInner{border-radius:5px;background-color:rgba(0,255,255,90);}"  //主窗口背景和阴影
                        "QToolButton{color:white;}"             //三个按钮的前景色
                        "#widgetInnerMain{background-color:white;}"
                        "#labelHeadPic{border-radius:32px;}"
                        "#widgetInnerMain QToolButton,QCheckBox{color:gray;}"   //将复选框和标签前景色设置为白色
                        "#widgetInnerMain QComboBox,QLineEdit{border:none;border-style:outset;border-bottom:1px solid gray;}"  //填写账号密码的widget的样式
                        "QComboBox::drop-down{image:url(://C:/Users/ASUS/Pictures/ImageMaterials/qarr.png);}"  //comboBox按钮的美化
                        "QPushButton{background-color:rgb(29,197,252);color:white;border:none;border-radius:3px;}"//初始格式
                        "QPushButton:hover{background-color:rgb(89,210,248);}"  //鼠标放上去之后的显示   21 140 179
                        "QLineEdit:focus{border-color:rgb(29,197,252);}"
                        "QComboBox:focus{border:1px solid rgb(29,197,252);color:red;}");
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->LoginwidgetInner->setGraphicsEffect(shadow);


}

void LoginWidget::on_toolButtonClose_clicked()
{
    close();
}

void LoginWidget::on_toolButton_2_clicked()
{
    if(regis!=nullptr)
    {
        delete regis;
        regis = nullptr;
    }
    regis  = new RegisterWidget();
    regis->show();
}


/*
    登录按钮：
    获取账号密码以信号的方式发送到主窗口

*/
void LoginWidget::on_pushButton_clicked()   //未完成  判断有瑕疵
{
    //一些信息判断
    QString id = ui->comboBoxUserID->currentText();
    QString password = ui->lineEditPassword->text();
    if(id==""||password=="")
    {
        QMessageBox::warning(0,"错误","账号或密码不能为空",QMessageBox::Ok);
        return;
    }
    emit loginOk(id,password);
}
