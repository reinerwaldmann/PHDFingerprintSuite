#include "tablecontendor.h"


TableContendor::TableContendor(int columns, int rows):table(columns)
{
numOfColumns = columns;
numOfRows = rows;
for(int outer = 0; outer < table.size(); ++outer)
table[outer].resize(rows);
columnNames = new QString [columns];
rowNames = new QString [rows];
clear();
}


void TableContendor::clear ()
{
    counterColumnNames = numOfColumns;
    counterRowNames = numOfRows;
    counterTableCells = numOfColumns * numOfRows;


    for (int i=0; i<numOfColumns; i++)
    {
        columnNames[i] = "";
        for (int j=0; j<numOfRows; j++)
        {
            table[i][j]=0;
        }
    }

    for (int j=0; j<numOfRows; j++)
    {
        rowNames[j]="";
    }
}

double TableContendor::getValue (int column, int row)
{
    return table [column][row];
}


void TableContendor::setValue (int column, int row, double value)
{
    table[column][row]=value;
    counterTableCells--;
}


void TableContendor::setColumnName (int column, QString name)
{
    columnNames[column]=name;
    counterColumnNames--;

}



void TableContendor::setRowName (int row, QString name)
{
    counterRowNames--;
    rowNames[row]=name;
}



int TableContendor::getNumOfColumns ()
{
    return numOfColumns;

}


int TableContendor::getNumOfRows ()
{
    return numOfRows;
}


bool TableContendor::areAllCellsFull()
{
return (!counterTableCells);

}


bool TableContendor::areAllRowNamesFull()
{
    return (!counterRowNames);

}

bool TableContendor::areAllColumnNamesFull()
{
    return (!counterColumnNames);

}

char TableContendor::outTableToTextFile(QString filename)
{
    QFile file (filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Error cannot open file for output";
        return 1;
    }

    QTextStream out(&file);

    out<<" "<<"\t";
    for (int i=0; i<numOfColumns; i++)
    {
        out<<columnNames[i]<<"\t";
     }
    out <<"\n";


    for (int j=0; j<numOfRows; j++)
{

        out<<rowNames[j]<<"\t";
    for (int i=0; i<numOfColumns; i++)
    {
        out<<table[i][j]<<"\t";

    }

    out << "\n";
}




return 0;


}


twoHandsResults TableContendor::averageOnFingers ()
{



}
