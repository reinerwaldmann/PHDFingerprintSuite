#ifndef FRRBUILDERHEADER_H
#define FRRBUILDERHEADER_H

#include <QTextStream>
#include <QString>
#include <QFile>
#include <QHash>
#include <QDebug>
#include "tablecontendor.h"

int onArrayOfThresholds (QString infileName, QString outfileName);
QHash<int, double> onArrayOfThresholds (QList <double> indata,   QList <double> iThresholds);
QList < QList < double > > make10lists (TableContendor itable, int iColumnNumber);
TableContendor makeFRRForAllFingers (QString infile, QList <double> thresholds);
TableContendor makeFRRForAllFingers (TableContendor indata, QList <double> thresholds);

#endif // FRRBUILDERHEADER_H
