#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QDebug>


namespace Ui {
class MainWindow;
}


enum templates {normal, compact, record};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

    void ms (QString ims);
    void ms (double ims);


     template<typename T> void   msres (T ms); //выводит сообщение в консоль результатов


    double fingerMatch (QString ionepath, QString isecondpath);




    void matchFolders (QString iRegisterFolderPath, QString iVerifFoldersPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif);






private slots:
    void on_pushSel1_clicked();

    void on_pushSel2_clicked();

    void on_pushMe_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
