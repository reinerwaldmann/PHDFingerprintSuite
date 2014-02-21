#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*

    QString Cmd=  tr("ifconfig");

      QProcess *Process= new QProcess(this);
      Process->start(Cmd); // ,Args
      if(!Process->waitForFinished())  ms ("some shit");

      QByteArray encodedString = Process->readAll();

      ms(tr(encodedString));



      delete Process;

*/

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ms (QString ims)
{

    ui->console->appendPlainText(ims);


}

void MainWindow::on_pushSel1_clicked()
{
ui->lineSel1->setText(QFileDialog::getOpenFileName(this, QString::fromUtf8("Имя файла"), "*.bin"));

/*\

QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
"D:\",
QFileDialog::ShowDirsOnly
| QFileDialog::DontResolveSymlinks);*/


}

void MainWindow::on_pushSel2_clicked()
{
ui->lineSel2->setText(QFileDialog::getOpenFileName(this, QString::fromUtf8("Имя файла"), "*.bin"));
}

void MainWindow::on_pushMe_clicked()
{

    //ms (QString::number(fingerMatch(ui->lineSel1->text(), ui->lineSel2->text())));
    matchFolders();

}

 void MainWindow::matchFolders ()
 {
     //regexps
 QString fingers [] = {"thumb","index", "middle", "ring","little"};
 QString hands [] = {"right" , "left"};
 QString print = "_print";
 QString noprint = "_iso";


 QString normal = "normal";
 QString compact = "compact";
 QString record = "record";


 QString foldername = "11_2014-02-11.11:01:40";
QString pathname = "/media/0e9cb697-e997-44da-aad5-fd99744c0d31/kristal/Projects/build-PHDFingerprintSuite-Desktop_Qt_5_1_1_GCC_32bit-Debug/testFolder/Ilia11FEB2014/11_2014-02-11.11:01:40";
//those two parameters to be aquired, the first one to be deducted from the second


QString pathname_all = "/media/0e9cb697-e997-44da-aad5-fd99744c0d31/kristal/Projects/build-PHDFingerprintSuite-Desktop_Qt_5_1_1_GCC_32bit-Debug/testFolder/Ilia11FEB2014";
//this is also to be deducted




//now we compare:   ROLL CARD NORMAL vs PRINT<FLAT> CARD NORMAL
//ONE to MANY

//1st - list folders in pathname_all allfolder
QDir allfolder (pathname_all);
allfolder.setFilter(QDir::Dirs); //it can list files as well
 QStringList entries = allfolder.entryList();

 for( QStringList::ConstIterator entry=entries.begin(); entry!=entries.end(); ++entry )
{

     QString dirname=*entry;
     if (!dirname.compare(foldername))
     continue;

     if(!dirname.compare("."))
         continue;

     if(!dirname.compare(".."))
         continue;

     ms (tr ("current watch directory %1").arg(dirname));

     QString curpath=pathname_all+"/"+dirname;
     QDir curfolder (curpath);
     curfolder.setFilter(QDir::Files);
     QStringList subfiles = curfolder.entryList();

     ///добавить фильтрацию по имени

     foreach (QString filenm, subfiles)
     {

         /*
IMPORTANT: HERE FILTRATION OF FILENAMES TAKES PLACE!
*/

         for (int i=0; i<5; i++)
         {
             if (filenm.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[0]).arg(fingers[i]).arg(noprint).arg(normal))))
             {
                 ms (filenm);
                }





         }


     }



}







 }

//proposes that biotool is in /usr/bin directory
 double MainWindow::fingerMatch (QString ionepath, QString isecondpath)
 {
     QString Cmd=  tr("biotool mf %1 %2").arg(ionepath).arg(isecondpath);
     QProcess *Process= new QProcess(this);
     Process->start(Cmd); // ,Args
     if(!Process->waitForFinished())  ms ("some shit");
     QByteArray encodedString = Process->readAll();
     QString res = tr(encodedString).replace("Fingerprint match score =", "");

     res=res.replace(",", ".");
     delete Process;
     return (res.toDouble());

 }
