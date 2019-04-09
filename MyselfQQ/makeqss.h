#ifndef MAKEQSS_H
#define MAKEQSS_H

#include <QString>
#include <QFile>

class makeQSS
{
public:
    makeQSS();
    static QString getStyleSheet(QString filePath);
};

#endif // MAKEQSS_H
