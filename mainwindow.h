#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"fundamental.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    class ImageDisplayer* id;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
public slots:
    void on_actionOpen_activated();
    void on_actionExit_activated();
};

#endif // MAINWINDOW_H
