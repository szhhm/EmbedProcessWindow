#-------------------------------------------------
#
# Project created by QtCreator 2018-04-27T21:15:16
#
#-------------------------------------------------

#-------------------------------------------------
#
# PS:应将此配置放置在pro文件的最后, 否则可能会不起作用
#
# 以下配置为程序输出目录配置模板, 根据需要自行修改
# 其中, 默认认为整个工程使用SubDir工程, 且子工程为非SubDir工程.
# 如有不同, 请根据情况进行修改
#
#
# 主要就是配置 TARGET(目标名字) 以及 DESTDIR(目标目录), DLLDESTDIR(动态库自动复制目录)
# 将TARGET在debug状况下加上d后缀
# 将DESTDIR设置到bin目录下,而在目标为动态库时修改为放入lib目录下
# 将DLLDESTDIR设置为bin目录, 用于将动态库的自动发布复制
#
# 配置后, release以及debug目录将会出现在目标路径的output文件夹下
# 并且会将子工程的ui生成文件放入子工程相应的ui目录下
#
#-------------------------------------------------

QT       -= gui

TEMPLATE = lib
CONFIG += staticlib


#设置UI文件目录
UI_DIR = ./ui

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

include(log4qt/log4qt.pri)

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
    SLogHelper.cpp \
    SLogWrapper.cpp

HEADERS += \
    SLogHelper.h \
    SLogWrapper.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
