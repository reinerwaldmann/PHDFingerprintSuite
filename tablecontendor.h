#ifndef TABLECONTENDOR_H
#define TABLECONTENDOR_H
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
    double getValue (int column, int row);
    void setValue (int column, int row);
    int getNumOfColumns ();
    int getNumOfRows ();
    void clear ();
    bool areAllCellsFull();
    bool areAllRowNamesFull();
    bool areAllColumnNamesFull();
    char outTableToTextFile(QString filename);
    twoHandsResults averageOnFingers ();

/*
Больше функций про средние!!!!!!!
*/

protected:
    int counterTableCells;
    int counterColumnNames;
    int counterRowNames;
    int numOfColumns;
    int numOfRows;
    double table [][]; //first is a number of a column, second is a number of a row
    //generic way - to make the table of QVariant types or separate tables of different types
    QString columnNames[];
    QString rowNames[];
};

#endif // TABLECONTENDOR_H
