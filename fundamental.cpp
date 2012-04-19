#include"fundamental.h"


void ImageDisplayer::LoadImage()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home/gsc/Documents",tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
  if (!fileName.isEmpty())
    {
      cout<<fileName.toStdString()<<endl;
      this->image=cv::imread(fileName.toStdString());
    }
}

ImageDisplayer::ImageDisplayer():QGLWidget()
{
}

