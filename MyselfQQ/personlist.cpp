#include "personlist.h"

personList::personList(QWidget *parent) : QListWidget(parent)
{
    qDebug()<<"首先构造构造";
    setFocusPolicy(Qt::NoFocus);   //去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //水平滚动条关闭
    clearflag = false;
    isHideVector.resize(50);
    isHideVector.fill(true);
    initMenu();
    initData();
    showData();
    connect(this,&QListWidget::itemClicked,this,&personList::dealDispaly);
    connect(this,&QListWidget::itemDoubleClicked,this,&personList::slotDoubleCilcked);
}


//鼠标点击事件
//void personList::mousePressEvent(QMouseEvent *event)
//{
//    QListWidget::mousePressEvent(event);   //调用父类的鼠标点击事件

//    if(groupNameEdit->isVisible()&&!(groupNameEdit->rect().contains(event->pos())))
//    {
//        if(groupNameEdit->text()!=NULL)
//        {
//            currentItem->setText(groupNameEdit->text());
//        }
//        groupNameEdit->setText("");
//        groupNameEdit->hide();
//    }

//    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));   //鼠标位置的item
//    if(event->button()==Qt::LeftButton&&currentItem!=NULL
//            &&currentItem==groupMap.value(currentItem));   //左键  并且是组
//    {
//        if(isHideMap.value(currentItem))    //如果是隐藏  则显示
//        {
//            foreach(QListWidgetItem * subItem,groupMap.keys(currentItem))  //遍历组的对应项
//            {
//                if(subItem!=currentItem)         //如果是组的话不进行处理
//                {
//                    subItem->setHidden(false);   //好友全部显示
//                }
//            }
//            isHideMap.insert(currentItem,false);   //设置该组为显示状态
//            currentItem->setIcon(QIcon(""));  //   设置一个icon  图标
//        }
//        else
//        {
//            foreach(QListWidgetItem * subItem,groupMap.keys(currentItem))
//            {
//                if(subItem!=currentItem)
//                {
//                    subItem!=currentItem;
//                }


//            }
//             isHideMap.insert(currentItem,true);   //设置该组为隐藏状态
//            currentItem->setIcon(QIcon(""));
//        }
//    }

//}

void personList::contextMenuEvent(QContextMenuEvent * event)
{
    QListWidget::contextMenuEvent(event);
    if(currentItem==NULL)
    {
        blankMenu->exec(QCursor::pos());
        return;
    }
    if(currentItem==groupMap.value(currentItem))   //如果点击到的是组
    {
        groupMenu->exec(QCursor::pos());
    }
    else  //否则是好友
    {
        personMenu->exec(QCursor::pos());
    }
}

void personList::initMenu()
{
    //初始化
    blankMenu = new QMenu();
    groupMenu = new QMenu();
    personMenu = new QMenu();
    groupNameEdit = new QLineEdit();

    QAction * addGroup = new QAction("添加分组",this);
    QAction * delGroup = new QAction("删除该组",this);
    QAction * rename = new QAction("重命名",this);
    QAction * addBuddy = new QAction("添加好友",this);
    QAction * delBuddy = new QAction("删除好友",this);

    //设置
    groupNameEdit->setParent(this);
    groupNameEdit->hide();
    groupNameEdit->setPlaceholderText("未命名");

    //布局
    blankMenu->addAction(addGroup);
    groupMenu->addAction(delGroup);
    groupMenu->addAction(rename);
    groupMenu->addAction(addBuddy);
    personMenu->addAction(delBuddy);

    Cout<<"运行到这里";

    //处理信号
    connect(groupNameEdit,&QLineEdit::editingFinished,this,&personList::slotRenameEditFshed);
    connect(addGroup,&QAction::triggered,this,&personList::slotAddGroup);
    connect(delGroup,&QAction::triggered,this,&personList::slotDelBuddy);
    connect(rename,&QAction::triggered,this,&personList::slotRename);
    connect(addBuddy,&QAction::triggered,this,&personList::slotAddBuddy);
    connect(delBuddy,&QAction::triggered,this,&personList::slotDelBuddy);

}

void personList::initData()
{

    //应该是从数据库写入信息

    //QList<QPair<PersonGroup*,QList<personListBuddy*>> > friendList;


    //先添加几个分组信息
    friendList.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(new PersonGroup("11111"),new QList<personListBuddy*>()));
    friendList.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(new PersonGroup("22222"),new QList<personListBuddy*>()));
    friendList.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(new PersonGroup("33333"),new QList<personListBuddy*>()));
    friendList.push_back(QPair<PersonGroup*,QList<personListBuddy*>*>(new PersonGroup("44444"),new QList<personListBuddy*>()));



    //添加几个好友
    for(auto iter = friendList.begin();iter!=friendList.end();iter++)
    {
        for(int i = 0;i<2;i++)
        {
            iter->second->push_back(new personListBuddy("://C:/Users/ASUS/Pictures/ImageMaterials/circleHeadMain.png",QString::number(rand()%100),"哈哈"));
        }
    }
}

void personList::showData(PersonGroup * pg)
{


    int i = 0;
    //QList<QPair<QPair<PersonGroup*,bool>,QList<personListBuddy*>*>> friendList;
    for(auto iter = friendList.begin();iter!=friendList.end();iter++,i++)
    {

       // qDebug()<<"-------Pair--------"<<iter->first.first->getGroupName()<<iter->first.second<<"----------";
        QListWidgetItem * item = new QListWidgetItem();
        this->addItem(item);
        if(pg!=NULL&&(*pg)==*(iter->first))
        {
            //iter->first.second = !(iter->first.second);
            isHideVector[i] = !(isHideVector[i]);
        }
        this->setItemWidget(item,iter->first);
        item->setSizeHint(QSize(this->width(),36));
        for(auto itList = iter->second->begin();itList!=iter->second->end();itList++)
        {
            //qDebug()<<(*itList)->getName()<<","<<(*itList)->getSign();
            QListWidgetItem * itemL = new QListWidgetItem();
            this->addItem(itemL);
            this->setItemWidget(itemL,(*itList));
            itemL->setSizeHint(QSize(this->width(),60));
            if(isHideVector[i] == true)
            {
                itemL->setHidden(true);
            }
        }
    }


    //connect(this,&QListWidget::itemClicked,this,&personList::dealDispaly);
}

void personList::slotAddGroup()
{
    QListWidgetItem * newItem = new QListWidgetItem(QIcon(""),"未命名");
    newItem->setSizeHint(QSize(this->width(),25));   //设置宽高
    isHideMap.insert(newItem,true);  //设置该组初始为隐藏
    groupMap.insert(newItem,newItem);
    groupNameEdit->raise();
    groupNameEdit->setText("未命名");    //设置默认内容
    groupNameEdit->selectAll();   //设置全选
    groupNameEdit->setGeometry(this->visualItemRect(newItem).left()+15,
                               this->visualItemRect(newItem).top()+1,
                               this->visualItemRect(newItem).width(),
                               this->visualItemRect(newItem).height()-2);   //出现的位置
    groupNameEdit->show();
    groupNameEdit->setFocus();   //获取焦点
    currentItem = newItem;
}

void personList::slotDelGroup()
{
    foreach(QListWidgetItem * item,groupMap.keys(currentItem))  //遍历该组所有好友和自身的组
    {
        groupMap.remove(item);
        delete item;
    }
    isHideMap.remove(currentItem);
}

void personList::slotAddBuddy()
{
    personListBuddy * buddy = new personListBuddy();
//    buddy->headPath = "";  //头像路径
//    buddy->name->setText("逍遥圣帝");
//    buddy->sign->setText("这是一个傻逼");
    buddy->setHeadPic(QString(""));
    buddy->setName("逍遥圣帝");
    buddy->setSign("这是一个傻逼");
    QList<QListWidgetItem *> tem = groupMap.keys(currentItem);   //当前组对应的项复制给tem

    QListWidgetItem * newItem = new QListWidgetItem();
    this->insertItem(row(currentItem)+tem.count(),newItem);  //将该newItem插入到后面
    this->setItemWidget(newItem,buddy);   //将buddy复制给newItem
    groupMap.insert(newItem,currentItem);   //加进容器
    if(isHideMap.value(currentItem))
    {
        newItem->setHidden(true);
    }
    else
    {
        newItem->setHidden(false);
    }
}

void personList::slotDelBuddy()
{
    groupMap.remove(currentItem);
    delete currentItem;
}

void personList::slotRename()
{
    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(currentItem).left()+15,
                               this->visualItemRect(currentItem).top()+1,
                               this->visualItemRect(currentItem).width(),
                               this->visualItemRect(currentItem).height()-2);   //出现的位置
    groupNameEdit->setText(currentItem->text());
    groupNameEdit->show();
    groupNameEdit->selectAll();
    groupNameEdit->setFocus();
}

void personList::slotRenameEditFshed()
{
    if(groupNameEdit->text()!=NULL)
    {
        currentItem->setText(groupNameEdit->text());

    }
    groupNameEdit->setText("");
    groupNameEdit->hide();
}



void personList::dealDispaly(QListWidgetItem *current)
{
    QWidget * currWidget = current->listWidget()->itemWidget(current);
    PersonGroup * temp = nullptr;
    if(typeid(*currWidget)==typeid(PersonGroup))   //如果点击的是分组选项
    {
        temp = (dynamic_cast<PersonGroup*>(currWidget));

    }
    else if(typeid(*currWidget)==typeid(personListBuddy))  //如果是好友选项
    {
        //发出一个信号   打开聊天界面
        return;
    }
    disconnect(this,&QListWidget::itemClicked,this,&personList::dealDispaly);
    this->clear();   //清空显示列表

    friendList.clear();

    initData();   //每次点击之后  初始化界面容器和数据容器  重新显示从新加载数据  速度会比较慢
    showData(temp);
    connect(this,&QListWidget::itemClicked,this,&personList::dealDispaly);
}

void personList::slotDoubleCilcked(QListWidgetItem *item)
{
    QWidget * currWidget = item->listWidget()->itemWidget(item);
    if(typeid(*currWidget)==typeid(personListBuddy))  //如果是好友选项
    {
        //发出一个信号   打开聊天界面
        auto temp = dynamic_cast<personListBuddy*>(currWidget);
        emit chooseFriend(temp->getName(),temp->getHeadPath());
        return;
    }
}

