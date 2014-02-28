#include <QCoreApplication>
 #include <QTextStream>
#include <QString>
#include <QFile>
#include <QHash>
#include <QDebug>
#include "tablecontendor.h"

int onArrayOfThresholds (QString infileName, QString outfileName);



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

    cout<<infileName;
    cout <<"\n";
    cout<<outfileName;
    cout <<"\n";
    cout<<start;
    cout <<"\n";
    cout<<step;
    cout <<"\n";


    TableContendor cnt (1,1);

    cnt.readFileIntoContendor("tablein.txt");
    cnt.outTableToTextFile("tableout.txt");

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
