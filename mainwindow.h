#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <tablecontendor.h>
#include <QComboBox>
#include <QSettings>


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

    /**
     * @brief matchFolders
     *берёт папку RegisterFolderPath, и прикладывает ко всем подпапкам VerifFolderPath. Выводит в консоли и выводит в табличный контейнер результаты прикладывания
     * @param iRegisterFolderPath
     * @param iVerifFoldersPath
     * @param itemplateRegistered тип шаблона при регистрации
     * @param itemplateVerif тип шаблона при верификации
     * @param isPrintRegister искать ли ключевое слово print в именах файлов  папки регистрации
     * @param isPrintVerif искать ли ключевое слово print в именах файлах папок верификации
     * @param itbl  указатель на табличный контейнер
     * @param colnameInTable столбец в таблице, куда писать данные
     */
    void matchFolders (QString iRegisterFolderPath, QString iVerifFoldersPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif, TableContendor * itbl, int colnameInTable=0);





    /**
     * @brief superMatchFolder
     * Хтоничный ужас, летящий на крыльях ночи
     *Берёт пул папок на регистрацию. Каждую из подпапок скармливает matchFolders, каковой в части папок с подпапками на верификацию скармливет пул верификации
     *данные вкатывает в табличный контейнер, в котором по строчкам идут результаты из папок верификации, а по столбцам - папки регистрации.
     * @param iRegisterFoldersPoolPath
     * @param iVerifFoldersPoolPath
     * @param itemplateRegistered
     * @param itemplateVerif
     * @param isPrintRegister
     * @param isPrintVerif
     * @param itbl
     */
    TableContendor superMatchFolder (QString iRegisterFoldersPoolPath, QString iVerifFoldersPoolPath, templates itemplateRegistered, templates itemplateVerif, bool isPrintRegister, bool isPrintVerif, TableContendor * itbl=0);

    templates getTemplate (QComboBox * icombo);





private slots:
    void on_pushSel1_clicked();

    void on_pushSel2_clicked();

    void on_pushMe_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
