#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSettings set ;

    ui->lineSel1->setText(set.value("regpath", "").toString());
    ui->lineSel2->setText(set.value("verpath", "").toString());









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
//ui->lineSel1->setText(QFileDialog::getOpenFileName(this, QString::fromUtf8("Имя файла"), "*.bin"));


    ui->lineSel1->setText(QFileDialog::getExistingDirectory(this,tr ("Open Directory")));

/*\

QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
"D:\",
QFileDialog::ShowDirsOnly
| QFileDialog::DontResolveSymlinks);*/


}

void MainWindow::on_pushSel2_clicked()
{
//ui->lineSel2->setText(QFileDialog::getOpenFileName(this, QString::fromUtf8("Имя файла"), "*.bin"));
    ui->lineSel2->setText(QFileDialog::getExistingDirectory(this,tr ("Open Directory")));
}


templates MainWindow::getTemplate (QComboBox * icombo)
{
    switch (icombo->currentIndex())
    {
        case 0:
        return normal;

        case 1:
        return compact;

        case 2:
        return record;

    }
    qDebug()<<"Error getTemplate";
    return normal;
}

void MainWindow::scriptForFolder (QString personFolder)
{
    //performs three experiments



    ui->console->clear();
    ui->console_2->clear();
    ui->console_3->clear();

    QString ds45 = personFolder+"/"+"ds45";
    QString fork = personFolder+"/"+"fork";


    QList <double> thresholds;
    thresholds<<0.9 << 0.99 << 0.999 << 0.9999 << 0.99999;

    //test1
    qDebug()<<"flat-flat-normal-normal-DS45-FORK.txt";
    TableContendor  tablex=superMatchFolder(ds45, fork, normal, normal, 1, 0);
    tablex = makeFRRForAllFingers(tablex,thresholds);
    tablex.outTableToTextFile(personFolder+"/"+"FRRflat-flat-normal-normal-DS45-FORK.txt");

    //test2
    qDebug()<<"roll-flat-normal-normal-DS45-FORK.txt";
    tablex=superMatchFolder(ds45, fork, normal, normal, 0, 0);
    tablex = makeFRRForAllFingers(tablex,thresholds);
    tablex.outTableToTextFile(personFolder+"/"+"FRRroll-flat-normal-normal-DS45-FORK.txt");


    //test3
    qDebug()<<"flat-flat-normal-normal-FORK-FORK.txt";
    tablex=superMatchFolder(fork, fork, normal, normal, 0, 0);
    tablex = makeFRRForAllFingers(tablex,thresholds);
    tablex.outTableToTextFile(personFolder+"/"+"FRRflat-flat-normal-normal-FORK-FORK.txt");



    //test4
    qDebug()<<"flat-flat-normal-normal-DS45-DS45.txt";
    tablex=superMatchFolder(ds45, ds45, normal, normal, 1, 1);
    tablex = makeFRRForAllFingers(tablex,thresholds);
    tablex.outTableToTextFile(personFolder+"/"+"FRRflat-flat-normal-normal-DS45-DS45.txt");

    //test4
    qDebug()<<"roll-flat-normal-normal-DS45-DS45.txt";
    tablex=superMatchFolder(ds45, ds45, normal, normal, 0, 1);
    tablex = makeFRRForAllFingers(tablex,thresholds);
    tablex.outTableToTextFile(personFolder+"/"+"FRRroll-flat-normal-normal-DS45-DS45.txt");



}


void MainWindow::script ()
{
    ui->console->clear();
    ui->console_2->clear();
    ui->console_3->clear();


/*
    QString regvol = "/media/DataDrive/Documents/Intek/FingerprintNeueExp/Ilia/11FEB2014";
    QString vervol= "/media/DataDrive/Documents/Intek/FingerprintNeueExp/Ilia/FORKMicro";

//bool isPrintRegister, bool isPrintVerif

    qDebug()<<"Test";
    TableContendor  tablex = superMatchFolder(regvol, vervol, normal, normal, 1, 0);
    tablex.outTableToTextFile("flat-flat-normal-normal-DS45-FORK.txt");
/*из-за особенностей работы софта регистрации при работе с FORK слово print не добавляется к имени файлов, потому
надлежит вторую булевскую переменную устанавливать в ноль*/


/*Для удобства работы с разными людьми надлежит написать функцию скрипта. каковая производит все означенные здесь исследования,
принимая на вход всего лишь имя корневой папки человека, в каковой бы находились папки flat  и roll, в которых уже, в свою очередь, бы
находились папки комплектов*/






/*
    qDebug()<<"Test1";
    TableContendor table = superMatchFolder("/home/reiner/testFolder/Ilia/Roll", "/home/reiner/testFolder/Ilia/Flat", normal, normal, 0, 0);
    table.outTableToTextFile("roll-flat-normal-normal-DS45-FORK-VOLODJA.txt");
*/

    QString vol= "/media/0e9cb697-e997-44da-aad5-fd99744c0d31/kristal/Documents/Intek/FingerprintsNeueExp/Vladimir_Ananjev/18FEB2014";


    qDebug()<<"Test2";
    TableContendor  table = superMatchFolder(vol, vol, normal, normal, 0, 1);
    table.outTableToTextFile("roll-flat-normal-normal-DS45-DS45-VOLODJA.txt");

/*
    qDebug()<<"Test3";
    TableContendor table = superMatchFolder("/home/reiner/testFolder/Ilia/Roll", "/home/reiner/testFolder/Ilia/Flat", compact, compact, 0, 0);
    table.outTableToTextFile("roll-flat-compact-compact-DS45-FORK.txt");
*/

    qDebug()<<"Test4";
    table = superMatchFolder(vol, vol, compact, compact, 0, 1);
    table.outTableToTextFile("roll-flat-compact-compact-DS45-DS45-VOLODJA.txt");


    qDebug()<<"Test5";
    table = superMatchFolder(vol, vol, normal, normal, 1, 1);
    table.outTableToTextFile("flat-flat-normal-normal-DS45-DS45-VOLODJA.txt");







}


void MainWindow::on_pushMe_clicked()
{
    script();

    return;

ui->console->clear();
ui->console_2->clear();
ui->console_3->clear();



    //ms (QString::number(fingerMatch(ui->lineSel1->text(), ui->lineSel2->text())));
    //matchFolders();

//    QString regpath = "/home/reiner/testFolder/Ilia11FEB2014/11_2014-02-11.11:01:40";
  //  QString allpath = "/home/reiner/testFolder/Ilia11FEB2014";

    QString regpath = ui->lineSel1->text();
    QString allpath = ui->lineSel2->text();

    QSettings set;
    set.setValue("regpath", regpath);
    set.setValue("verpath", allpath);

/*
    TableContendor * table  = new TableContendor(1,20);
    matchFolders(regpath, allpath, normal, normal, 0,  1, table );
    table->outTableToTextFile("res.txt");
    delete table;*/


    ui->console_3->appendPlainText("Short info about test");
    ui->console_3->appendPlainText(tr("Registration Folder Pool %1").arg(regpath) );
    ui->console_3->appendPlainText(tr("Verification Folder Pool %1").arg(allpath) );
    ui->console_3->appendPlainText(tr ("Template registration %1 %2").arg(ui->comboTemplateRegist->currentIndex()).arg(ui->comboTemplateRegist->currentText()));
    ui->console_3->appendPlainText(tr ("Template verification %1 %2").arg(ui->comboTemplateVerif->currentIndex()).arg(ui->comboTemplateVerif->currentText()));
    ui->console_3->appendPlainText("Information about are flat prints are used is to be entered manually");

    TableContendor table = superMatchFolder(regpath, allpath, getTemplate(ui->comboTemplateRegist), getTemplate(ui->comboTemplateVerif), ui->checkRegPrint->isChecked(), ui->checkVerifPrint->isChecked());
    table.outTableToTextFile("out.txt");

}

TableContendor  MainWindow::superMatchFolder (QString iRegisterFoldersPoolPath, QString iVerifFoldersPoolPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif, TableContendor * itbl)
{

QDir RegisteredFolderPool (iRegisterFoldersPoolPath);
RegisteredFolderPool.setFilter(QDir::Dirs);
QStringList registeredFolderPoolEntries= RegisteredFolderPool.entryList();

QDir VerifFolderPool (iVerifFoldersPoolPath);
VerifFolderPool.setFilter(QDir::Dirs);
QStringList VerifFolderPoolEntries= VerifFolderPool.entryList();

int numColumns = registeredFolderPoolEntries.size()-2;
int numRows = VerifFolderPoolEntries.size()-2;

int nnnn(0);
if (!iRegisterFoldersPoolPath.compare(iVerifFoldersPoolPath))
{
    nnnn=numRows*10-10; //это если пути равны, в этом случае можно на 10 поменьше, так как каждый раз будет на одну папку меньше
}
else
{

    nnnn = numRows*10;

}

TableContendor table(numColumns, nnnn);

int tableColumnCounter(0);

foreach (QString registeredFolderPoolEntry, registeredFolderPoolEntries)
{
    if(!registeredFolderPoolEntry.compare("."))
        continue;

    if(!registeredFolderPoolEntry.compare(".."))
        continue;


    qDebug()<<tr("Cur watch dir %1").arg(registeredFolderPoolEntry);

    matchFolders(iRegisterFoldersPoolPath+"/"+registeredFolderPoolEntry, iVerifFoldersPoolPath, itemplateRegistered, itemplateVerif, isPrintRegister, isPrintVerif, &table, tableColumnCounter);
tableColumnCounter++;
}


return  table;

}







//one folder to many folders around that one, but without one
 void MainWindow::matchFolders (QString iRegisterFolderPath, QString iVerifFoldersPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif, TableContendor * itbl, int colnameInTable)
 {
TableContendor * table = itbl;
table->setColumnName(colnameInTable, iRegisterFolderPath.mid(iRegisterFolderPath.lastIndexOf("/")+1)); //вписываем название папки



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



int counterRowsInTable(0);


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

                if (!colnameInTable)
                table->setRowName(counterRowsInTable, hands[0]+fingers[i]);

                table->setValue(colnameInTable, counterRowsInTable,rs);




                 msres (tr("%1 %2 %3").arg(hands[0]).arg(fingers[i]).arg(rs));

                 ms (tr("cmp: %1 & %2 = %3").arg(rightHandPaths[i]).arg(iVerifFoldersPath+"/"+dirname+"/"+filenm ).arg(rs) );

                 counterRowsInTable++;


             }

         }
//left hand
         for (int i=0; i<5; i++)
         {
             if (filenm.contains(QRegularExpression( tr (".*%1.*%2%3.*%4.*bin").arg(hands[1]).arg(fingers[i]).arg(isPrintVerif?print:noprint).arg(verifTemplateStr))))
             {
                 //ms (iVerifFoldersPath+"/"+dirname+"/"+filenm);

                double rs=fingerMatch(leftHandPaths[i], iVerifFoldersPath+"/"+dirname+"/"+filenm );


               if (!colnameInTable)
               table->setRowName(counterRowsInTable, hands[1]+fingers[i]);

               table->setValue(colnameInTable, counterRowsInTable,rs);

                msres (tr("%1 %2 %3").arg(hands[1]).arg(fingers[i]).arg(rs));
                ms (tr("cmp: %1 & %2 = %3").arg(leftHandPaths[i]).arg(iVerifFoldersPath+"/"+dirname+"/"+filenm ).arg(rs) );

                counterRowsInTable++;

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
