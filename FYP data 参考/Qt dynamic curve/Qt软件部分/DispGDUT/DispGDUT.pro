TARGET   = DispGDUT
LIBS += -L D:\Qwt-6.0.1\lib -lqwtd
INCLUDEPATH += D:\Qwt-6.0.1\include


HEADERS = \
    signaldata.h \
    plot.h \
    knob.h \
    wheelbox.h \
    samplingthread.h \
    curvedata.h \
    mainwindow.h 

SOURCES = \
    signaldata.cpp \
    plot.cpp \
    knob.cpp \
    wheelbox.cpp \
    samplingthread.cpp \
    curvedata.cpp \
    mainwindow.cpp \
    main.cpp
