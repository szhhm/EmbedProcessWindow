TEMPLATE = app
QT += qml quick widgets websockets
CONFIG += c++11

INCLUDEPATH += ../SLog ../FtpLib ../

SOURCES += main.cpp \
    ProcessWindow.cpp \
    WindowContainer.cpp \
    SQuickView.cpp \
    SFrontWorker.cpp \
    model/SAnoucementMsg.cpp

RESOURCES += qml.qrc

OUTPUTDIR = ..\\output

CONFIG(debug, debug|release) {
  #设置debug配置下编译生成文件的路径
#  TARGET = $$join(TARGET,,,d)   #为debug版本生成的文件增加d的后缀

  contains(TEMPLATE, "lib") {
    DESTDIR = $$PWD/../output/debug/lib        #将库放在lib文件夹下
    DLLDESTDIR = $$PWD/../output/debug/bin     #将动态库自动拷贝至bin目录下
  } else {
    DESTDIR = $$PWD/../output/debug/bin        #将应用程序放在bin目录下
  }
  OBJECTS_DIR = $$PWD/../output/debug/obj     #将生成的对象文件放在专门的obj文件夹下
  MOC_DIR = $$PWD/../output/debug/moc         #将QT自动生成的对象放在moc文件夹下
  RCC_DIR = $$PWD/../output/debug/rcc
  UI_DIR = $$PWD/../output/debug/ui
  LIBS += -L$$PWD/../output/debug/lib -lSLogd -lFtpLibd -lUser32
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
  RCC_DIR = $$PWD/../output/release/rcc
  UI_DIR = $$PWD/../output/release/ui
  LIBS += -L$$PWD/../output/release/lib -lSLog  -lFtpLib -lUser32
}
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = EmbedProcessWnd.ico

# Default rules for deployment.
include(deployment.pri)

RC_FILE += EmbedProcessWnd.rc

#QMAKE_POST_LINK = copy /y $$OUTPUTDIR\\*.lib $(QTDIR)\\lib
#QMAKE_POST_LINK = "copy /y EmbedProcessWnd.ico $$OUTPUTDIR\\debug\\bin"
QMAKE_POST_LINK += afterLink.bat

win32-msvc* {
    QMAKE_CXXFLAGS +=  /wd"4100"
    contains (QMAKE_CXXFLAGS_WARN_ON, -w34100) : QMAKE_CXXFLAGS_WARN_ON -= -w34100
}
HEADERS += \
    ProcessWindow.h \
    WindowContainer.h \
    SQuickView.h \
    SFrontWorker.h \
    model/SAnoucementMsg.h

DISTFILES += \

FORMS += \
    windowcontainer.ui

