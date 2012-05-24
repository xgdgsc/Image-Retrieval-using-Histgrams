#include"fundamental.h"
#include"libs.h"


ImageDisplayer::ImageDisplayer(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::ImageDisplayer)
{
  img=NULL;
  ui->setupUi(this);
  initializeIcons();
  //initializeWidgets();
  //initializeShortcuts();
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  //scrollArea->setWidgetResizable(true);
  setCentralWidget(scrollArea);

  resize(1024,600);
}

ImageDisplayer::~ImageDisplayer()
{
  delete ui;
}

void ImageDisplayer::loadImage()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home/gsc/Documents",tr("Image Files (*.png *.jpg *.bmp *.jpeg *.tiff *.tif *.p?m *.sr *.jp2);;All Files (*.*);;BMP(*.bmp);;JPEG(*.jpg *.jpeg *.jp2);;PNG(*.png);;TIFF(*.tif *.tiff)"));
  if (!fileName.isEmpty())
    {
      cout<<fileName.toStdString()<<endl;
      this->img=cvLoadImage(fileName.toStdString().c_str(),4);
      QImage qimg=IplImage2QImage(this->img);
      imageLabel->setPixmap(QPixmap::fromImage(qimg));
      scaleFactor = 1.0;

      ui->action_Fit_to_Window->setEnabled(true);
      updateActions();

      if (!ui->action_Fit_to_Window->isChecked())
        {
          imageLabel->adjustSize();
        }
    }
}

void ImageDisplayer::on_actionExit_triggered()
{
  this->close();
}

void ImageDisplayer::on_actionOpen_triggered()
{
  this->loadImage();
}

void ImageDisplayer::on_action_About_triggered()
{
  QMessageBox::about(this, tr("About DCT"),
                     tr("Written by GaoShichao"));
}

void ImageDisplayer::on_action_Fit_to_Window_triggered()
{
  fitToWindow();
}

void ImageDisplayer::on_action_Actual_Size_triggered()
{
  normalSize();
}

void ImageDisplayer::fitToWindow()
{
  bool fitToWindow =ui->action_Fit_to_Window->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);

  if (!fitToWindow) {
      normalSize();
    }
  updateActions();
}

void ImageDisplayer::normalSize()
{
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void ImageDisplayer::updateActions()
{
  ui->actionZoom_In->setEnabled(!ui->action_Fit_to_Window->isChecked());
  ui->actionZoom_Out->setEnabled(!ui->action_Fit_to_Window->isChecked());
  ui->action_Actual_Size->setEnabled(!ui->action_Fit_to_Window->isChecked());
}

void ImageDisplayer::initializeIcons()
{
  ui->actionOpen->setIcon(qcs.standardIcon(QStyle::SP_DirIcon,0,0));
  ui->actionExit->setIcon(qcs.standardIcon(QStyle::SP_DialogCloseButton,0,0));
}

void ImageDisplayer::zoomIn()
//! [9] //! [10]
{
  scaleImage(1.25);
}

void ImageDisplayer::zoomOut()
{
  scaleImage(0.8);
}

void ImageDisplayer::on_actionZoom_In_triggered()
{
  zoomIn();
}

void ImageDisplayer::on_actionZoom_Out_triggered()
{
  zoomOut();
}

void ImageDisplayer::scaleImage(double factor)
{
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

}


void ImageDisplayer::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
  scrollBar->setValue(int(factor * scrollBar->value()
                          + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageDisplayer::on_actionGenerate_triggered()
{

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
