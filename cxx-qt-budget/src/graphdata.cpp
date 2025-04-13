#include "graphdata.h"

#include <fstream>
#include <QTextStream>
#include <QFile>

void CGraphData::ReadFile(const QString& file, QVector<QStringList>& tokens)
{
    QFile inFile(file);
    if(inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream stream(&inFile);
        while(!stream.atEnd()) {
            QString line = stream.readLine();
            if(line.startsWith("#") || line.startsWith(":"))
                continue;
            QStringList values = line.split(QLatin1Char(';'), Qt::SkipEmptyParts);
            tokens.append(values);
        }
        inFile.close();
    }
}
