#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:57:13
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = DIPfundamental
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    libs.cpp \
    fundamental.cpp

HEADERS  += mainwindow.h \
    fundamental.h \
    libs.h

FORMS    += mainwindow.ui
win32 {
            LIBS+="D:/Program Files/opencv/build/x86/mingw/lib/libopencv_core231.dll.a" \
                    "D:/Program Files/opencv/build/x86/mingw/lib/libopencv_highgui231.dll.a"
}

unix {
            LIBS+= -lGLU -lopencv_core -lopencv_highgui
}

RESOURCES += \
    icon.qrc
