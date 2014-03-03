#include <QCoreApplication>
 #include <QTextStream>
#include <QString>
#include <QFile>
#include <QHash>
#include <QDebug>
#include "tablecontendor.h"

int onArrayOfThresholds (QString infileName, QString outfileName);
QHash<int, int> onArrayOfThresholds (QList <double> indata,   QList <double> iThresholds);
QList < QList < double > > make10lists (TableContendor itable, int iColumnNumber);
TableContendor makeFRRForAllFingers (QString infile, QList <QString> thresholds);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream  cout (stdout);
    
/*    for (int i=1; i<argc; i++)
    {
        cout<<argv[i];
        cout<<"\n";
    }  */
    /*leftthumb.txt out.txt 0.9 0.0001*/
    QString infileName (argv [1]);
    QString outfileName (argv [2]);

    double start = QString(argv[3]).toDouble();
    double step = QString(argv[4]).toDouble();


    cout<<"contendor version";
    cout<<infileName;
    cout <<"\n";
    cout<<outfileName;
    cout <<"\n";
    cout<<start;
    cout <<"\n";
    cout<<step;
    cout <<"\n";


    TableContendor cnt (1,1);

//    cnt.readFileIntoContendor("tablein.txt");
  //  cnt.outTableToTextFile("tableout.txt");

    return 0;


    //return    onArrayOfThresholds (infileName, outfileName);







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
    QHash <int, int> counterValuesLowerThanThreshold;
    //сраный костыль, ибо qHash не может быть с ключом типа double, просто не может, трололо!!!!
//первое значение - ключ
    QHash <int, double> keytable;
//заполняем таблицу порогов
    int j=0;
    for (double i=start; i<=1; i+=step)
    {
        keytable.insert(j,i);
        counterValuesLowerThanThreshold.insert(j,0);
        j++;
    }
    //зерно алгоритма
    foreach (double val, listOfValues)
    {
               {

        for (double i=start; i<=1; i+=step)
            if (val<=i)
            {
    //сраные костыли во все поляяяя!!
                //тролли советуют написать-таки реализацию qHash()с double, вкупе с оператором ==()
                counterValuesLowerThanThreshold.insert(keytable.key(i),counterValuesLowerThanThreshold.value(keytable.key(i))+1  );
                //counterValuesLowerThanThreshold.insert(i,counterValuesLowerThanThreshold.value(i)+1);
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
    for (double i=start; i<=1; i+=step)
    {
        outFileStream<<i<<"\t"<<(double)counterValuesLowerThanThreshold.value(j)/listOfValues.size() <<"\n";
        j++;
    }
    outFileStream.flush();
    cout.flush();
    infile.close();
    outfile.close();
    return 0;
    return a.exec();
}
/*
На вход подаётся список данных, это понятно
И список порогов.
Важный момент - на выходе хеш, где номеру порога во входном списке  соответствует количество данных ниже его.


*/


QHash <int, int> onArrayOfThresholds (QList <double> indata,   QList <double> iThresholds)
{
        //QTextStream  cout (stdout);
        QHash <int, int> counterValuesLowerThanThreshold;
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
                counterValuesLowerThanThreshold.insert(j,counterValuesLowerThanThreshold.value(j)+1);
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

    for (int j=0; j<itable.getNumOfRows(); j++)

    {
        for (int i=0; i<10; i++) //по каждому пальцу
        {
            if (!itable.getRowName(j).compare(fingers[i]))
            {
                res.at(i).append(itable.getValue(iColumnNumber,j));

            }

        }

    }
    return res;

}


TableContendor makeFRRForAllFingers (QString infile, QList <QString> thresholds)
{
    TableContendor indata (infile);

    TableContendor res (indata.getNumOfColumns(), thresholds.size());

    for (int i=0; i<indata.getNumOfColumns(); i++)
    {//для каждого столбца из таблицы входных данных


        QList <QList < double > > doublelist = make10lists(indata, i);

        foreach (QList <double> list, doublelist)
        {
            QHash <int, int> fingerhash  =  onArrayOfThresholds(list,thresholds);
        }

//QHash<int, int> onArrayOfThresholds (QList <double> indata,   QList <double> iThresholds);

















    }





}
