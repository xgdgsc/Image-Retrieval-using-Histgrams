#ifndef HISTO_H
#define HISTO_H


#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iomanip>

//#include<QtOpenGL/QtOpenGL>
//#include<QtDebug>
//#include<QString>
//#include<QFileDialog>
//#include<GL/glu.h>
//#include<QShortcut>
//#include<QImage>
//#include<QIcon>
//#include<QStyle>
//#include<QCommonStyle>

typedef unsigned int uint;


#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include"libs.h"

class HDist
{
public:
  string name;
  double distance;
  friend bool operator<(HDist d1,HDist d2){return (d1.distance<d2.distance);}
 // bool operator<(HDist d){return distance<d.distance;}
};

class imgHisto
{
public:
  imgHisto(){precision=0;}
  string imgName,nameCore;
  Mat img;
  vector<double> histo;
  int w,h;
  vector<HDist> dist;
  int precision;
  void clear(){dist.clear();}
  void clearH(){histo.clear();}
};



class Histo
{
public:
    void input();
    void generateHist(int part[]);
    double calcL2(imgHisto query,imgHisto all);
    double calcHI(imgHisto query,imgHisto all);
    double calcBh(imgHisto query,imgHisto all);
    double calcCo(imgHisto query,imgHisto all);
    void  generateReport(imgHisto& query,int part[],string method);
    void overall(int part[], string method);
    void clear();
    void clearH();
private:
    vector<imgHisto> allImage;
    vector<imgHisto> queryImage;
//    vector<int> preciion;
};

#endif // HISTO_H
