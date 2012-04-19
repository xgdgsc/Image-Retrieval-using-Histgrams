#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->id=new ImageDisplayer(this);
    this->setCentralWidget(id);
    QShortcut* Exit=new QShortcut(QKeySequence("Ctrl+q"),this);
    connect(Exit,SIGNAL(activated()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_activated()
{
  this->close();
}

void MainWindow::on_actionOpen_activated()
{
  id->LoadImage();
}
