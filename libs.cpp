#include"libs.h"
#include<Qt>
#ifdef Q_WS_WIN
#include"Windows.h"
#endif
// IplImage* qImage2IplImage(const QImage& qImage)
//{
//  int width = qImage.width();
//  int height = qImage.height();

//  // Creates a iplImage with 3 channels
//  IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
//  char * imgBuffer = img->imageData;

//  //Remove alpha channel
//  int jump = (qImage.hasAlphaChannel()) ? 4 : 3;

//  for (int y=0;y<img->height;y++){
//      QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
//      for (int i=0; i<a.size(); i+=jump){
//          //Swap from RGB to BGR
//          imgBuffer[2] = a[i];
//          imgBuffer[1] = a[i+1];
//          imgBuffer[0] = a[i+2];
//          imgBuffer+=3;
//        }
//    }

//  return img;
//}


// QImage IplImage2QImage(const _IplImage *iplImage)
//{
//  int height = iplImage->height;
//  int width = iplImage->width;

//  if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
//    {
//      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
//      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
//      return img.rgbSwapped();
//    }
//  else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
//      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
//      QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

//      QVector<QRgb> colorTable;
//      for (int i = 0; i < 256; i++){
//          colorTable.push_back(qRgb(i, i, i));
//        }
//      img.setColorTable(colorTable);
//      return img;
//    }
//  else{
//      qWarning() << "Image cannot be converted.";
//      return QImage();
//    }
//}
#ifdef Q_WS_WIN
std::wstring s2ws(const std::string& s);
#endif
void myMkdir(string dir)
{
#ifdef Q_WS_X11
    mkdir(dir.c_str(),0777);
#endif
#ifdef Q_WS_WIN
    wstring stemp=s2ws(dir);
    CreateDirectoryW(stemp.c_str(),NULL);
#endif
}

#ifdef Q_WS_WIN
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
#endif
