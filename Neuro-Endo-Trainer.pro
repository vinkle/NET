#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T22:18:33
#
#-------------------------------------------------

QT       += core sql gui multimedia multimediawidgets opengl serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Neuro-Endo-Trainer
TEMPLATE = app
CONFIG += console
#CONFIG += debug

SOURCES += main.cpp\
        qmainwindow.cpp \
    settings_main.cpp \
    settings.cpp \
    testBasler.cpp \
    testIDS.cpp \
    testUSB.cpp \
    qtopencvviewergl.cpp \
    buf_aux.cpp \
    buf_endo.cpp \
    usbcamrecorddisp.cpp \
    auxCamRecord.cpp \
    params.cpp \
    auxcamgraphicsview.cpp \
    timeClass.cpp \
    Scorer.cpp \
    util.cpp \
    tracker/BB.cpp \
    tracker/BBPredict.cpp \
    tracker/FBTrack.cpp \
    tracker/Lk.cpp \
    tracker/Median.cpp \
    tracker/MedianFlowTracker.cpp \
    treeitem.cpp \
    treemodel.cpp \
    showresult.cpp

HEADERS  += qmainwindow.h \
    settings_main.h \
    settings.h \
    testBasler.h \
    testIDS.h \
    testUSB.h \
    qtopencvviewergl.h \
    buf_aux.h \
    buf_endo.h \
    usbcamrecorddisp.h \
    auxCamRecord.h \
    params.h \
    auxcamgraphicsview.h \
    timeClass.h \
    Scorer.h \
    util.h \
    tracker/BB.h \
    tracker/BBPredict.h \
    tracker/FBTrack.h \
    tracker/Lk.h \
    tracker/Median.h \
    tracker/MedianFlowTracker.h \
    treeitem.h \
    treemodel.h \
    showresult.h

FORMS    += qmainwindow.ui \
    settings_main.ui \
    settings.ui \
    showresult.ui


RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -O2


QMAKE_CFLAGS -= -Wno-unused-parameter

INCLUDEPATH += /opt/pylon3/include
INCLUDEPATH += /opt/pylon3/genicam/library/CPP/include
INCLUDEPATH += /usr/local/include

LIBS += -L/usr/lib
LIBS += -L/usr/local/lib
LIBS += -L/usr/lib/x86_64-linux-gnu/
LIBS += -L/opt/pylon3/lib64
LIBS += -L/opt/pylon3/genicam/bin/Linux64_x64
LIBS += -L/opt/pylon3/genicam/bin/Linux64_x64/GenApi/Generic

LIBS += -lpylonbase
LIBS += -lGenApi_gcc40_v2_3
LIBS += -lGCBase_gcc40_v2_3
LIBS += -lLog_gcc40_v2_3
LIBS += -lMathParser_gcc40_v2_3
LIBS += -lXerces-C_gcc40_v2_7
LIBS += -llog4cpp_gcc40_v2_3
LIBS += -lpthread
LIBS += -lv4l2
LIBS += -lv4l2rds
LIBS += -lX11
LIBS += -lueye_api

LIBS += -lopencv_calib3d
LIBS += -lopencv_contrib
LIBS += -lopencv_core
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_legacy
LIBS += -lopencv_ml
LIBS += -lopencv_nonfree
LIBS += -lopencv_objdetect
LIBS += -lopencv_photo
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_ts
LIBS += -lopencv_video
LIBS += -lopencv_videostab
LIBS += -lrt
LIBS += -lm
LIBS += -ldl

DISTFILES +=
