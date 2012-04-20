#ifndef FUNDAMENTAL_H
#define FUNDAMENTAL_H

#include<vector>
#include<map>
#include<opencv2/opencv.hpp>
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

#include"libs.h"
#include"mainwindow.h"

using namespace std;
using namespace cv;

class ImageDisplayer:public QWidget
{
  Q_OBJECT
public slots:
  void LoadImage();
public:
  ImageDisplayer(QWidget *parent = NULL);
  void Display();
public:
  IplImage *img;
protected:
//  void initializeGL();
//  void resizeGL(int w, int h);
//  void paintGL();
};

#endif // FUNDAMENTAL_H
