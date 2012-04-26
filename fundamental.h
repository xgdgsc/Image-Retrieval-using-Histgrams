#ifndef FUNDAMENTAL_H
#define FUNDAMENTAL_H

#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iomanip>

#include<QtOpenGL/QtOpenGL>
#include<QtDebug>
#include<QString>
#include<QFileDialog>
#include<GL/glu.h>
#include<QShortcut>
#include<QImage>
#include<QIcon>
#include<QStyle>
#include<QCommonStyle>

#ifdef Q_WS_X11
#include<opencv2/opencv.hpp>
#endif

#ifdef Q_WS_WIN
#include<cv.h>
#endif


#include"libs.h"
#include"ui_mainwindow.h"

using namespace std;
using namespace cv;
namespace Ui{
  class ImageDisplayer;
}
class ImageDisplayer:public QMainWindow
{
  Q_OBJECT

public:
  explicit ImageDisplayer(QWidget *parent =0);
  ~ImageDisplayer();
  void Display();
public:
  IplImage *img;
public slots:
  void LoadImage();
  void on_actionOpen_activated();
  void on_actionExit_activated();
  void on_action_About_activated();
private:
  Ui::ImageDisplayer *ui;
  QLabel *imageLabel;
  QScrollArea *scrollArea;
  QCommonStyle  qcs;
private:
  void initializeShortcuts();
  void initializeWidgets();
  void initializeIcons();
  void fitToWindow();
  void normalSize();
  void updateActions();
  double scaleFactor;
protected:
  //  void initializeGL();
  //  void resizeGL(int w, int h);
  //  void paintGL();
};

#endif // FUNDAMENTAL_H
