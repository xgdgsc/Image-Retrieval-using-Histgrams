#ifndef LIBS_H
#define LIBS_H
#include"fundamental.h"
#include<opencv2/opencv.hpp>
static QImage IplImage2QImage(const IplImage *iplImage);
static IplImage* qImage2IplImage(const QImage& qImage);

#endif // LIBS_H
