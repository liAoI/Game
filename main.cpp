#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSize size(1000.0,900.0);
    w.setFixedSize(size);
    w.show();

    return a.exec();
}
