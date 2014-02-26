#include <QCoreApplication>
 #include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream  cout (stdout);
    
/*
    for (int i=1; i<argc; i++)
    {
        cout<<argv[i];
        cout<<"\n";
    }

    */


    /*leftthumb.txt out.txt 0.9 0.0001*/
    QString infile (argv [1]);
    QString outfile (argv [2]);

    double start = QString(argv[3]).toDouble();
    double step = QString(argv[4]).toDouble();



    cout<<infile;
    cout <<"\n";
    cout<<outfile;
    cout <<"\n";
    cout<<start;
    cout <<"\n";
    cout<<step;
    cout <<"\n";




    QList <double> listOfValues; //список значений, читаемый из файла
    /*
        Временное решение проблемы - потом, наверное, считывать придётся в табличный контейнер или нечто типа того
    */


    //QFile infile ()

















    cout.flush();
    return a.exec();
}
