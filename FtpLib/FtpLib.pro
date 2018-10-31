#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T20:17:38
#
#-------------------------------------------------

QT       += network

QT       -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG(debug, debug|release) {
  #设置debug配置下编译生成文件的路径
  TARGET = $$join(TARGET,,,d)   #为debug版本生成的文件增加d的后缀

  contains(TEMPLATE, "lib") {
    DESTDIR = $$PWD/../output/debug/lib        #将库放在lib文件夹下
    DLLDESTDIR = $$PWD/../output/debug/bin     #将动态库自动拷贝至bin目录下
  } else {
    DESTDIR = $$PWD/../output/debug/bin        #将应用程序放在bin目录下
  }
  OBJECTS_DIR = $$PWD/../output/debug/obj     #将生成的对象文件放在专门的obj文件夹下
  MOC_DIR = $$PWD/../output/debug/moc         #将QT自动生成的对象放在moc文件夹下
} else {
  #设置release配置下编译生成文件的路径

  contains(TEMPLATE, "lib") {
    DESTDIR = $$PWD/../output/release/lib        #将库放在lib文件夹下
    DLLDESTDIR = $$PWD/../output/release/bin     #将动态库自动拷贝至bin目录下
  } else {
    DESTDIR = $$PWD/../output/release/bin        #将应用程序放在bin目录下
  }
  OBJECTS_DIR = $$PWD/../output/release/obj   #将生成的对象文件放在专门的obj文件夹下
  MOC_DIR = $$PWD/../output/release/moc       #将QT自动生成的对象放在moc文件夹下
}


DEFINES += FTPLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FtpManager.cpp

HEADERS += \
        FtpManager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
