#-------------------------------------------------
#
# Project created by QtCreator 2018-11-04T15:57:19
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET       =  spoQQs
TEMPLATE     =  app

INCLUDEPATH +=  \
                ../spoXXs/


SOURCES     +=  main.cpp\
                ../spoXXs/flange.cpp \
                ../spoXXs/hole.cpp \
                ../spoXXs/hub.cpp \
                ../spoXXs/nipple.cpp \
                ../spoXXs/pattern.cpp \
                ../spoXXs/rim.cpp \
                ../spoXXs/spoke.cpp \
                ../spoXXs/spokes.cpp \
                ../spoXXs/wheel.cpp \
                ../spoXXs/wheelbuild.cpp \
                spoqqs.cpp \
                dialog_rimhub.cpp \
                dialog_results.cpp \
                dialog_graph.cpp \
                qgraphicsview_nowheel.cpp \
                dialog_sponip.cpp \
                dialog_about.cpp

HEADERS     +=  ../spoXXs/flange.h \
                ../spoXXs/hole.h \
                ../spoXXs/hub.h \
                ../spoXXs/nipple.h \
                ../spoXXs/pattern.h \
                ../spoXXs/rim.h \
                ../spoXXs/spoke.h \
                ../spoXXs/spokes.h \
                ../spoXXs/wheel.h \
                ../spoXXs/wheelbuild.h \
                ../spoXXs/wheel_define.h \
                spoqqs.h \
                dialog_rimhub.h \
                dialog_results.h \
                dialog_graph.h \
                qgraphicsview_nowheel.h \
                dialog_sponip.h \
                dialog_about.h

FORMS       +=  spoqqs.ui \
                dialog_rimhub.ui \
                dialog_results.ui \
                dialog_graph.ui \
                dialog_sponip.ui \
    dialog_about.ui
