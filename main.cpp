#include <QtGui/QApplication>
#include "fundamental.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/DCT"));
    ImageDisplayer w;
    w.setWindowTitle("DCT");

    w.show();
    
    return a.exec();
}
