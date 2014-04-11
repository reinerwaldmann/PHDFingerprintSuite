#ifndef TABLECONTENDOR_H
#define TABLECONTENDOR_H



#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QStringList>
struct twoHandsResults
{
    double  right [5];
    double  left [5];
     // 0 - thumb
};
class TableContendor
{
public:

    TableContendor(int columns, int rows);
    TableContendor(QString  infile);


    void setSizes(int columns, int rows);


    double getValue (int column, int row);
    void setValue (int column, int row, double value);
    void setColumnName (int column, QString name);
    void setRowName (int row, QString name);


    QString getColumnName (int column);
    QString getRowName (int row);



    int getNumOfColumns ();
    int getNumOfRows ();
    void clear ();
    bool areAllCellsFull();
    bool areAllRowNamesFull();
    bool areAllColumnNamesFull();
    char outTableToTextFile(QString filename);
    twoHandsResults averageOnFingers ();

    int readFileIntoContendor (QString ifilename );
    QHash <int ,double> getRowAverages();  //number of a row - average






/*
Больше функций про средние!!!!!!!
*/

protected:
    int counterTableCells;
    int counterColumnNames;
    int counterRowNames;
    int numOfColumns;
    int numOfRows;

 QVector < QVector < double > > table;
 //first is a number of a column, second is a number of a row
 //generic way - to make the table of QVariant types or separate tables of different types

 QHash <int ,  double> RowAverages;   //holds averages of the rows. Protected, as may be used only after counted





 QString *columnNames;
    QString *rowNames;
};

#endif // TABLECONTENDOR_H
