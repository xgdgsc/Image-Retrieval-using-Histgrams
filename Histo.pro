#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:57:13
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Histo
TEMPLATE = app


SOURCES += main.cpp\
    libs.cpp \
    histo.cpp

HEADERS  += \
    libs.h \
    histo.h

FORMS    += mainwindow.ui
win32 {
            INCLUDEPATH+="D:/Program Files/opencv/include/opencv"
            #INCLUDEPATH+="D:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include"
            LFLAGS = -static-libgcc
            LIBS+="D:/Program Files/opencv/build/x86/mingw/lib/libopencv_core241.dll.a"
            LIBS+="D:/Program Files/opencv/build/x86/mingw/lib/libopencv_highgui241.dll.a"
            LIBS+="D:/Program Files/opencv/build/x86/mingw/lib/libopencv_imgproc241.dll.a"
            DEPENDPATH+="D:/Program Files/opencv/build/x86/mingw/bin"
}

unix {
            LIBS+= -lGLU -lopencv_core -lopencv_highgui -lopencv_imgproc
}

RESOURCES += \
    icon.qrc

