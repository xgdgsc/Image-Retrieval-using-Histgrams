#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/dip"));
    MainWindow w;
    w.setWindowTitle("DIPfundamental");

    w.show();
    
    return a.exec();
}
