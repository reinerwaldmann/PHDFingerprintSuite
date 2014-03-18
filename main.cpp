#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    

    if (argc>1)
    {
        QString fld (argv[1]);
        w.scriptForFolder(fld);

    }


    return a.exec();
}
