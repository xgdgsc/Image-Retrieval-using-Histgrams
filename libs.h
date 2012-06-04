#ifndef LIBS_H
#define LIBS_H

#include<opencv2/opencv.hpp>
#include<sys/stat.h>
using namespace std;
// QImage IplImage2QImage(const _IplImage *iplImage);
// IplImage* qImage2IplImage(const QImage& qImage);
 void myMkdir(string dir);

#ifdef Q_WS_WIN
#include<windows.h>


wstring s2ws(const std::string& s);

#endif

#endif // LIBS_H
