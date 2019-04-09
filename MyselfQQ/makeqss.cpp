#include "makeqss.h"

makeQSS::makeQSS()
{

}

QString makeQSS::getStyleSheet(QString filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QString StyleSheet(file.readAll());
        file.close();
        return StyleSheet;
    }
    return QString("");
}

