#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reader.h"
#include "writer.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    SharedParameters sharedVariables;





public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_pushButton_14_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    Writer* writer;
    Reader ** readerArray;
    unsigned int constNumberThreads;
};

#endif // MAINWINDOW_H
