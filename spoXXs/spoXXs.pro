TEMPLATE =  app
CONFIG +=   console c++11
CONFIG -=   app_bundle
CONFIG -=   qt

SOURCES +=  main.cpp \
            hole.cpp \
            nipple.cpp \
            spoke.cpp \
            flange.cpp \
            hub.cpp \
            rim.cpp \
            pattern.cpp \
            spokes.cpp \
            wheel.cpp \
    wheelbuild.cpp

HEADERS +=  \
            hole.h \
            nipple.h \
            spoke.h \
            flange.h \
            hub.h \
            rim.h \
            pattern.h \
            spokes.h \
            wheel_define.h \
            wheel.h \
    wheelbuild.h
