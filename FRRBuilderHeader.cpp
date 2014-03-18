#include "FRRBuilderHeader.h"


/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream  cout (stdout);

     QString infileName (argv [1]);
    QString outfileName (argv [2]);

    double start;// = QString(argv[3]).toDouble();
    double step;// = QString(argv[4]).toDouble();


    cout<<"contendor version";
    cout<<infileName;
    cout <<"\n";
    cout<<outfileName;
    cout <<"\n";
    //cout<<start;
    cout <<"\n";
    //cout<<step;
    cout <<"\n";

    QList <double> thresholds;
    thresholds<<0.9 << 0.99 << 0.999 << 0.9999 << 1;

    makeFRRForAllFingers(infileName, thresholds).outTableToTextFile(outfileName);


    return 0;
    //дальнейшее не имеет смысла





  }*/





QHash <int, double> onArrayOfThresholds (QList <double> indata,   QList <double> iThresholds)
{
        //QTextStream  cout (stdout);
        QHash <int, double> counterValuesLowerThanThreshold;
        //QHash <int, double> keytable;


        //int j=0;
        //foreach (double u, iThresholds)
        for (int j=0; j<iThresholds.size(); j++)
        {
            //keytable.insert(j,u);
            counterValuesLowerThanThreshold.insert(j,0);
//            j++;
        }

        //зерно алгоритма
        foreach (double val, indata)
        {

            for (int j=0; j<iThresholds.size(); j++)
            {
                if (val<=iThresholds.at(j))
                {
                    counterValuesLowerThanThreshold.insert(j, counterValuesLowerThanThreshold.value(j)+1.0/indata.size());
                }
            }

 /*

            foreach (double u, iThresholds)
             {
                if (val<=u)
                {
                    int t=keytable.key(u);
                    counterValuesLowerThanThreshold.insert(t,counterValuesLowerThanThreshold.value(t)+1);
                 }
            }

  */
        }





        return counterValuesLowerThanThreshold;
}











int  onArrayOfThresholds (QString infileName, QString outfileName)
{
//a list of thresholds
    QList <double> thresholds;

    QTextStream  cout (stdout);
    QList <double> listOfValues; //список значений, читаемый из файла
    /*
        Временное решение проблемы - потом, наверное, считывать придётся в табличный контейнер или нечто типа того
    */

    QFile infile (infileName);

    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text      ))
{
        cout<<"Error: infile cannot be opened";
        cout.flush();
        return -1;
    }
    QTextStream str (&infile);
    while(!str.atEnd())
    {
        listOfValues.append(str.readLine().toDouble());
    }
    //сраный костыль, ибо qHash не может быть с ключом типа double, просто не может, трололо!!!!
//первое значение - ключ
    QHash <int, int> counterValuesLowerThanThreshold;
    QHash <int, double> keytable;
    thresholds <<0.9<<0.99<<0.999<<0.9999<<1;

    int j=0;
    foreach (double u, thresholds)
    {
        keytable.insert(j,u);
        counterValuesLowerThanThreshold.insert(j,0);
        j++;
    }

    //зерно алгоритма
    foreach (double val, listOfValues)
    {


            foreach (double u, thresholds)
         {
            if (val<=u)
            {
                int t=keytable.key(u);
                counterValuesLowerThanThreshold.insert(t,counterValuesLowerThanThreshold.value(t)+1);
             }
        }
    }
    //выхлоп
    QFile outfile (outfileName);
    if (!outfile.open(QIODevice::WriteOnly))
    {
        cout<<"Error: outfile cannot be opened";
        cout.flush();
        return -1;
    }
    QTextStream outFileStream (&outfile);
        j=0;
        foreach (double u, thresholds)
        {
             outFileStream<<u<<"\t"<<(double)counterValuesLowerThanThreshold.value(j)/listOfValues.size() <<"\n";
            j++;
        }
    outFileStream.flush();
    cout.flush();
    infile.close();
    outfile.close();
    return 0;
}

/*
из контейнера таблицы делате 10 списков данных, по каждому пальцу по списку. Всё делаетсяиз одного столбца,
номер которого передаётся входным параметром
первый список по пальцам, второй список по  данным
*/

QList < QList < double > > make10lists (TableContendor itable, int iColumnNumber)
{
    //скопипащено понятно откуда

    QString fingers [] = {"rightthumb","rightindex", "rightmiddle", "rightring","rightlittle", "leftthumb","leftindex", "leftmiddle", "leftring","leftlittle"};

    QList < QList < double > > res;

    for (int i=0; i<10; i++)
    {
        res<<QList<double> ();

    }



    for (int j=0; j<itable.getNumOfRows(); j++)

    {
        for (int i=0; i<10; i++) //по каждому пальцу
        {
            if (!itable.getRowName(j).compare(fingers[i]))
            {
                res[i].append(itable.getValue(iColumnNumber,j));

            }

        }

    }
    return res;

}

TableContendor makeFRRForAllFingers (TableContendor indata, QList <double> thresholds)
{


    TableContendor res (indata.getNumOfColumns(), thresholds.size()*10+1);

    QString fingers [] = {"rightthumb","rightindex", "rightmiddle", "rightring","rightlittle", "leftthumb","leftindex", "leftmiddle", "leftring","leftlittle"};




    for (int i=0; i<indata.getNumOfColumns(); i++)
    {//для каждого столбца из таблицы входных данных, сиречь для каждой папки регистрации

  int rowNum=0; //номер строки в таблице результатов


        QList <QList < double > > doublelist = make10lists(indata, i); //первый список - по пальцам, вложенные - список данных
        res.setColumnName(i,indata.getColumnName(i));
        //для каждого пальца, производим подсчёт
        //foreach (QList <double> list, doublelist)
        for (int m=0; m<doublelist.size(); m++)
        {
            QHash <int, double> fingerhash  =  onArrayOfThresholds(doublelist.at(m),thresholds);
            //приняли результат для пальца.

            QList<int> keylist=fingerhash.keys();
            for (int k=0; k<keylist.size(); k++)
            {


                res.setRowName(rowNum, fingers[m]+QString::number(thresholds.at(keylist.at(k))));
                res.setValue(i, rowNum, fingerhash.value(keylist.at(k)));
                rowNum++;



            }


        }

    }




    return res;



}


TableContendor makeFRRForAllFingers (QString infile, QList <double> thresholds)
{
      TableContendor indata (infile);
      return makeFRRForAllFingers(indata,thresholds);


}



