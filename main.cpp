#include "mainwindow.h"
#include <QApplication>
#include "reader.h"
#include "writer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
