#include "tablecontendor.h"


TableContendor::TableContendor(int columns, int rows):table(columns)
{
setSizes(columns, rows);
}

TableContendor::TableContendor (QString infile)
{
readFileIntoContendor (infile);

}


 void TableContendor::setSizes(int columns, int rows)
 {
     QVector < QVector < double > >  newTable (columns);
     table = newTable;
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

    if (row>numOfRows)

    {
        qDebug() << "ERROR: row number exceedes available number of rows";
        return;

    }
    if (column>numOfColumns)

    {

        qDebug() << "ERROR: column number exceedes available number of columns";
        return;

    }



    table[column][row]=value;
    counterTableCells--;
}


void TableContendor::setColumnName (int column, QString name)
{   if (column>numOfColumns)

    {

        qDebug() << "ERROR: column number exceedes available number of columns";
        return;

    }
    columnNames[column]=name;
    counterColumnNames--;

}



void TableContendor::setRowName (int row, QString name)
{
    if (row>numOfRows)

    {
        qDebug() << "ERROR: row number exceedes available number of rows";
        return;

    }


    counterRowNames--;
    rowNames[row]=name;
}



QString TableContendor::getColumnName (int column)
{
    return columnNames[column];


}


QString  TableContendor::getRowName (int row)
{
    return rowNames[row];
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
    out<<"Averages";
    out <<"\n";


    for (int j=0; j<numOfRows; j++)
{

        out<<rowNames[j]<<"\t";
    for (int i=0; i<numOfColumns; i++)
    {
        out<<table[i][j]<<"\t";

    }


    out<<getRowAverages().value(j);


    out << "\n";
}


    out << "ColAverage\t";

     for (int i=0; i<numOfColumns; i++)
     {
         out<<getColumnAverages().value(i)<<"\t";
     }

return 0;


}



int TableContendor::readFileIntoContendor (QString ifilename)
{
bool res;

QFile infile(ifilename);

if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
{
    qDebug()<<"Error while opening file";
    return 1;
}





QTextStream str (&infile);
QStringList listOfLines = str.readAll().split("\n");
QStringList namesLst = listOfLines.at(0).trimmed().split("\t");
int gnumberOfColumns  = namesLst.count();
int gnumberOfRows = listOfLines.count();

setSizes(gnumberOfColumns,gnumberOfRows-1);





int i=0;
foreach (QString name, namesLst)
{
    setColumnName(i, name);
    i++;
}



bool start(1);

i=0;
foreach (QString line, listOfLines)
{
    if (start) {start=0; continue;} //пропускаем начальную строку

    QStringList lineList = line.split("\t");




    setRowName(i, lineList.at(0));



    for (int j = 1; j<lineList.count()-1; j++)
    {
        setValue(j-1, i,lineList.at(j).toDouble());

    }


     i++;
}





return 0;

}








  QHash <int ,double>  TableContendor::getRowAverages()
{

      if (RowAverages.keys().size()>0) return RowAverages;

    /*

 QVector < QVector < double > > table;
 //first is a number of a column, second is a number of a row
 //generic way - to make the table of QVariant types or separate tables of different types
*/
    int ncol = getNumOfColumns ();
    int nrow = getNumOfRows ();

    RowAverages.clear();
    for (int i=0; i<nrow; i++) //for every row
    {
        double sum(0);
        for (int j=0; j<ncol; j++) //for every column
        {
            sum+=getValue(j,i);
        }

        sum/=ncol;
        RowAverages.insert(i,sum);
    }


     return RowAverages;

}

  QHash <int ,double> TableContendor::getColumnAverages()
{


      if (ColumnAverages.keys().size()>0) return ColumnAverages;

    /*

 QVector < QVector < double > > table;
 //first is a number of a column, second is a number of a row
 //generic way - to make the table of QVariant types or separate tables of different types
*/
    int ncol = getNumOfColumns ();
    int nrow = getNumOfRows ();

    RowAverages.clear();
    for (int i=0; i<ncol; i++) //for every column
    {
        double sum(0);
        for (int j=0; j<nrow; j++) //for every row
        {
            sum+=getValue(i,j);
        }

        sum/=nrow;
        ColumnAverages.insert(i,sum);
    }


     return ColumnAverages;



}


  QString TableContendor::getName()
  {
      return name;
  }
  void TableContendor::setName(QString iname)
  {
      name=iname;

  }
