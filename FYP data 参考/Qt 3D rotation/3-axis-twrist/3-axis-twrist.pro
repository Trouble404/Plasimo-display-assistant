TEMPLATE = app
TARGET	 = 3-axis-twrist

CONFIG	+= qt warn_off qaxserver

QT += opengl

HEADERS	 = glbox.h \
           globjwin.h
SOURCES	 = glbox.cpp \
           globjwin.cpp \
           main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS opengl.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
INSTALLS += target sources
