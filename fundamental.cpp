#include"fundamental.h"
#include"libs.h"

void ImageDisplayer::LoadImage()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home/gsc/Documents",tr("Image Files (*.png *.jpg *.bmp *.jpeg *.tiff *.tif *.p?m *.sr *.jp2);;All Files (*.*);;BMP(*.bmp);;JPEG(*.jpg *.jpeg *.jp2);;PNG(*.png);;TIFF(*.tif *.tiff)"));
  if (!fileName.isEmpty())
    {
      cout<<fileName.toStdString()<<endl;
      this->img=cvLoadImage(fileName.toStdString().c_str(),4);
    }
}

ImageDisplayer::ImageDisplayer(QWidget *parent):QWidget(parent)
{
  img=NULL;
  QShortcut *Open = new QShortcut(QKeySequence("Ctrl+o"), parent);
  QObject::connect(Open, SIGNAL(activated()), this, SLOT(LoadImage()));
}





//void ImageDisplayer::initializeGL()
//{
//  glDisable(GL_TEXTURE_2D);
//  glDisable(GL_DEPTH_TEST);
//  glDisable(GL_COLOR_MATERIAL);
//  glEnable(GL_BLEND);
//  glEnable(GL_POLYGON_SMOOTH);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glClearColor(0, 0, 0, 0);
//}

//void ImageDisplayer::resizeGL(int w, int h)
//{
//  glViewport(0, 0, w, h);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
//  //    gluPerspective(52.0f, 1.3333f, 0.1f, 100.0f);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//}

////extern static QImage IplImage2QImage(const IplImage *iplImage);

//void ImageDisplayer::paintGL()
//{
//  if(this->img)
//    {
//      glClear (GL_COLOR_BUFFER_BIT);
//      glClearColor(0.0,0.0,0.0,1.0);
//      glMatrixMode(GL_PROJECTION);
//#ifndef QT_OPENGL_ES_2
//      glEnable(GL_TEXTURE_2D);
//#endif
//      glPushMatrix();
//      glLoadIdentity();
//      gluOrtho2D(0.0,img->width, 0.0, img->width);
//      glMatrixMode(GL_MODELVIEW);
//      glPushMatrix();
//      glLoadIdentity();
//      QImage qimg=IplImage2QImage(this->img);
//      //bindTexture(qimg,GL_TEXTURE_2D,GL_RGBA);
//      glDrawPixels(img->width,img->height,GL_RGB,GL_UNSIGNED_BYTE,img->imageData);
//      glMatrixMode(GL_PROJECTION);
//      glPopMatrix();
//      glMatrixMode(GL_MODELVIEW);
//      glPopMatrix();
//    }
//}
