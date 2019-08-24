/**
  * @file
  * @brief 加载静态样式表
  * @version 1.0
  * @date 2019年4月30日10:12:39
*/
#ifndef MAKEQSS_H
#define MAKEQSS_H

#include <QString>
#include <QFile>
#include <QDebug>

#define  Cout qDebug()<<"[ "<<__FILE__<<":"<<__LINE__<<" ]"

/// @class makeQss
/// @brief 加载静态样式表
class makeQSS
{
public:
    makeQSS();
    /// @brief 从文件中读取出样式表内容
    /// @param 文件名
    static QString getStyleSheet(QString filePath);
};

#endif // MAKEQSS_H
