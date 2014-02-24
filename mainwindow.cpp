#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TableContendor table (10,20);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ms (QString ims)
{
    ui->console->appendPlainText(ims);
}

void MainWindow::ms(double ims)
{
    ms (QString::number(ims));

}



template<typename T> void   MainWindow::msres (T ms) //выводит сообщение в консоль результатов
{

    ui->console_2->appendPlainText(tr ("%1").arg(ms));


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
    //matchFolders();



    QString regpath = "/home/reiner/testFolder/Ilia11FEB2014/11_2014-02-11.11:01:40";
    QString allpath = "/home/reiner/testFolder/Ilia11FEB2014";
    matchFolders(regpath, allpath, normal, normal, 0, 1);

}


//one folder to many folders around that one, but without one
 void MainWindow::matchFolders (QString iRegisterFolderPath, QString iVerifFoldersPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif)
 {
     //regexps
 QString fingers [] = {"thumb","index", "middle", "ring","little"};
 QString hands [] = {"right" , "left"};
 QString print = "_print";
 QString noprint = "_iso";


 QString normalS = "normal";
 QString compactS = "compact";
 QString recordS = "record";



 QString verifTemplateStr;
  switch (itemplateVerif)
  {
  case normal:
         verifTemplateStr=normalS;
      break;
  case compact:
         verifTemplateStr=compactS;
      break;
  case record:
         verifTemplateStr=recordS;
      break;

  default:
      verifTemplateStr = normalS;
         break;
  }

  QString registerTemplateStr;
   switch (itemplateRegistered)
   {
   case normal:
          registerTemplateStr=normalS;
       break;
   case compact:
          registerTemplateStr=compactS;
       break;
   case record:
          registerTemplateStr=recordS;
       break;

   default:
       registerTemplateStr= normalS;
          break;
   }














 QString pathname = iRegisterFolderPath;
QString foldername  = pathname.mid(pathname.lastIndexOf("/")+1);
QString pathname_all = iVerifFoldersPath;


//list all registered prints into two arraysof fingers

QString rightHandPaths [5];
QString leftHandPaths [5];

int counterright=5;
int counterleft=5;
QDir RegisteredFolder (pathname);
RegisteredFolder.setFilter(QDir::Files);
QStringList registeredFolderEntries= RegisteredFolder.entryList();
foreach (QString registeredFolderEntry, registeredFolderEntries)
{


    for (int i=0; i<5; i++)
    {
        if (registeredFolderEntry.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[0]).arg(fingers[i]).arg(isPrintRegister?print:noprint).arg(registerTemplateStr))))
        {
            rightHandPaths[i]=pathname+"/"+registeredFolderEntry;
            //ms (rightHandPaths[i]);
            counterright--;
           }

    }

    for (int i=0; i<5; i++)
    {
        if (registeredFolderEntry.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[1]).arg(fingers[i]).arg(isPrintRegister?print:noprint).arg(registerTemplateStr))))

        {
            leftHandPaths[i]=pathname+"/"+registeredFolderEntry;
            //ms (leftHandPaths[i]);
            counterleft--;
           }

    }
}


if (counterright) {
    ms ("Error: not enough right fingers to compare, aborting");
    return;
}


if (counterleft) {
    ms ("Error: not enough left fingers to compare, aborting");
    return;
}






//now we compare:    ONE to MANY
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

     ms (tr(" "));
     ms (tr ("current watch directory %1").arg(dirname));
     ms (tr(" "));


     QString curpath=pathname_all+"/"+dirname;
     QDir curfolder (curpath);
     curfolder.setFilter(QDir::Files);
     QStringList subfiles = curfolder.entryList();

      foreach (QString filenm, subfiles)
     {

         /*
IMPORTANT: HERE FILTRATION OF FILENAMES TAKES PLACE!
*/
//right hand
         for (int i=0; i<5; i++)
         {
             if (filenm.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[0]).arg(fingers[i]).arg(isPrintVerif?print:noprint).arg(verifTemplateStr))))
             {
                 //ms (iVerifFoldersPath+"/"+dirname+"/"+filenm);

                 double rs=fingerMatch(rightHandPaths[i], iVerifFoldersPath+"/"+dirname+"/"+filenm );
                 msres (tr("%1 %2 %3").arg(hands[0]).arg(fingers[i]).arg(rs));

                 ms (tr("cmp: %1 & %2 = %3").arg(rightHandPaths[i]).arg(iVerifFoldersPath+"/"+dirname+"/"+filenm ).arg(rs) );

                }

         }
//left hand
         for (int i=0; i<5; i++)
         {
             if (filenm.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[1]).arg(fingers[i]).arg(isPrintVerif?print:noprint).arg(verifTemplateStr))))
             {
                 //ms (iVerifFoldersPath+"/"+dirname+"/"+filenm);

                double rs=fingerMatch(leftHandPaths[i], iVerifFoldersPath+"/"+dirname+"/"+filenm );
                msres (tr("%1 %2 %3").arg(hands[1]).arg(fingers[i]).arg(rs));
                ms (tr("cmp: %1 & %2 = %3").arg(leftHandPaths[i]).arg(iVerifFoldersPath+"/"+dirname+"/"+filenm ).arg(rs) );

                }

         }




     }


      msres (" ");


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
