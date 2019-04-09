#include "mainwidget.h"
#include "loginwidget.h"
#include "chatwidget.h"
#include "chatwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ChatWidget c;
//    c.show();
    MainWidget w;
    //w.show();
//    LoginWidget login;
//    login.show();
    //ChatWidget c;
    //c.show();

    return a.exec();
}
