#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

    void ms (QString ims);



    double fingerMatch (QString ionepath, QString isecondpath);




    void matchFolders ();






private slots:
    void on_pushSel1_clicked();

    void on_pushSel2_clicked();

    void on_pushMe_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
