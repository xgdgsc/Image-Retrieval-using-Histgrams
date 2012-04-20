#include <QtGui/QApplication>
#include "fundamental.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/dip"));
    ImageDisplayer w;
    w.setWindowTitle("DIPfundamental");

    w.show();
    
    return a.exec();
}
