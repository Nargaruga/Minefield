#include "mainwindow.h"
#include "grid.h"
#include "config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
