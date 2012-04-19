#ifndef FUNDAMENTAL_H
#define FUNDAMENTAL_H
#include<QtOpenGL/QGLWidget>
#include"mainwindow.h"
#include"libs.h"
#include<vector>
#include<map>
#include<opencv2/opencv.hpp>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<QtDebug>
#include<QString>
#include<QFileDialog>

using namespace std;
using namespace cv;

class ImageDisplayer:public QGLWidget
{
  Q_OBJECT
public slots:
void LoadImage();
public:
  ImageDisplayer();
  void Display();
public:
  Mat image;
};

#endif // FUNDAMENTAL_H
