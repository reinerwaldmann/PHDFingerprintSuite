#include "tablecontendor.h"


TableContendor::TableContendor(int columns, int rows)
{
numOfColumns = columns;
numOfRows = rows;
clear();


}


void TableContendor::clear ()
{
counterColumnNames = numOfColumns;
counterRowNames = numOfRows;
counterTableCells = numOfColumns * numOfRows;

for (int i=0; i<numOfColumns; i++)
{
    for (int j=0; j<numOfRows; j++)
    {
        table[i][j]=0;
    }

}


}




double TableContendor::getValue (int column, int row)
{}


void TableContendor::setValue (int column, int row)
{}


int TableContendor::getNumOfColumns ()
{}


int TableContendor::getNumOfRows ()
{}


bool TableContendor::areAllCellsFull()
{}


bool TableContendor::areAllRowNamesFull()
{}

bool TableContendor::areAllColumnNamesFull()
{}

char TableContendor::outTableToTextFile(QString filename)
{}


twoHandsResults TableContendor::averageOnFingers ()
{}
