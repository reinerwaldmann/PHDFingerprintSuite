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

TableContendor MainWindow::subScriptForFolder (QList <double> thresholds, QString personfolder, QString testname, QString iRegisterFoldersPoolPath, QString iVerifFoldersPoolPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif, TableContendor * itbl )
//упрощает написание скриптов
/*+производит тестирование по указанным параметрам
 *+спихивает сырьё в текстовый файл
 *+спихивает FRR в текстовый файл
 **/
{
       qDebug()<<testname;
       TableContendor tablex=superMatchFolder(iRegisterFoldersPoolPath, iVerifFoldersPoolPath, itemplateRegistered, itemplateVerif, isPrintRegister, isPrintVerif);
       tablex.outTableToTextFile(personfolder+"/"+testname.append(".txt"));
       tablex = makeFRRForAllFingers(tablex,thresholds);
       tablex.outTableToTextFile(personfolder+"/"+QString("FRR").append(testname).append(".txt"));
       tablex.setName(testname);
       return tablex;
}

void MainWindow::scriptForFolder (QString personFolder)
{
    //performs three experiments

    qDebug()<<"-------------["<<personFolder<<"]--------------";


    ui->console->clear();
    ui->console_2->clear();
    ui->console_3->clear();

    QString ds45 = personFolder+"/"+"ds45";
    QString fork = personFolder+"/"+"fork";

    QList <double> thresholds;
    thresholds<< 0.9999 << 0.99999 << 0.999999;

    QList <TableContendor>results;  //список таблиц результатов


//собственно, тестирование в соответствии с планом эксперимента от 10 Апреля 2014//
/*
     * internal, internal mobile, internal small, iso card normal
ds45-fork	rf	1
ds45-fork	ff	2
ds45-fork	rf	3
ds45-fork	ff	4
>>>>>>> b51f2cece5714ddd39f570ab9586ef89bdf1045e

ds45-ds45	rf	2
ds45-ds45	ff	3
ds45-ds45	rf	4
ds45-ds45	ff	1

fork-fork	ff	4
fork-fork	ff	2

fork-ds45	ff	1
sfork-ds45	ff	3


flat-flat-normal-normal-DS45-DS45-VOLODJA
*/



    /*
АХТУНГ!
Все тесты предназначены для использования со стандартной базой:
в каждой папке в папке ds45 лежат прокатки (без префикса или с префиксом roll), и оттиски (с префиксом print)
в каждой папке в папке fork лежат оттиски (без префикса или с префиксом print)


из чего следует пересмотреть БД или код программы (возможные опции: обязательно print, необязательно print, обязательно чтоб не было print)


*/

    //BATCH1

    //test1
    results.append(subScriptForFolder(thresholds, personFolder, "roll-flat-internal-internal-ds45-fork",ds45,fork,internal,internal,0,1));

    //test2
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-internalmobile-internalmobile-ds45-fork",ds45,fork,internalmobile,internalmobile,1,1));

    //test3
    results.append(subScriptForFolder(thresholds, personFolder, "roll-flat-internalsmall-internalsmall-ds45-fork",ds45,fork,internalsmall,internalsmall,0,1));

    //test4
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-normal-normal-ds45-fork",ds45,fork,normal,normal,1,1));


    //BATCH2


    //test5
    results.append(subScriptForFolder(thresholds, personFolder, "roll-flat-internal-internal-ds45-ds45",ds45,ds45,internalmobile,internalmobile,0,1));

    //test6
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-internalmobile-internalmobile-ds45-ds45",ds45,ds45,internalsmall,internalsmall,1,1));

    //test7
    results.append(subScriptForFolder(thresholds, personFolder, "roll-flat-internalsmall-internalsmall-ds45-ds45",ds45,ds45,normal,normal,0,1));

    //test8
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-normal-normal-ds45-ds45",ds45,ds45,internal,internal,1,1));





    //BATCH3


    //test9
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-normal-normal-fork-fork",fork,fork,normal,normal,1,1));

    //test10
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-internalmobile-internalmobile-fork-fork",fork,fork,internalmobile,internalmobile,1,1));




    //BATCH4


    //test11
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-internal-internal-fork-ds45",fork,ds45,internal,internal,1,1));

    //test12
    results.append(subScriptForFolder(thresholds, personFolder, "flat-flat-internalsmall-internalsmall-fork-ds45",fork,ds45,internalsmall,internalsmall,1,1));




    //printing tests results

    if (results.isEmpty()) return;


QFile outfile (personFolder+"/"+"FRRResults.txt");
if (!outfile.open(QIODevice::WriteOnly|QIODevice::Text))
{
qDebug()<<"Cannot write FRR results file, error!";
return;
}

QTextStream ostream (&outfile);

ostream<<" \t";
foreach (TableContendor tc, results)
{
    ostream<<tc.name<<"\t";
}
ostream<<"\n";



int numRowsRes = ((TableContendor)results.at(0)).getNumOfRows();
for (int i=0; i<numRowsRes; i++)
{

    ostream<<((TableContendor)results.at(0)).getRowName(i)<<"\t";

    foreach (TableContendor tc, results)
    {
        ostream<<tc.getRowAverages().value(i)<<'\t';
    }

    ostream<<"\n";

}

ostream.flush();

outfile.close();



/*


 foreach (TableContendor tc, results)
 {


    QHash <int, double> ra=tc.getRowAverages();
    QList <int> keylist = ra.keys();

    foreach (int i, keylist)
    {
        ostream<<ra.value(i)<<'\t';
    }

ostream<<"\n";
 }

ostream.flush();

outfile.close();


*/


}




void MainWindow::on_pushMe_clicked()
{

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

 QString internalS = "internal";
 QString internalmobileS = "internal_mobile";
 QString internalsmallS = "internal_small";




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

  case internal:
        verifTemplateStr = internalS;
        break;

  case internalmobile:
        verifTemplateStr = internalmobileS;
        break;

  case internalsmall:
        verifTemplateStr = internalsmallS;
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


   case internal:
         registerTemplateStr = internalS;
         break;

   case internalmobile:
         registerTemplateStr = internalmobileS;
         break;

   case internalsmall:
         registerTemplateStr = internalsmallS;
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
