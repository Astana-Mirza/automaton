QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += $$system(python3-config --includes)
DESTDIR = $${PWD}/build
LIBS += $$system(python3-config --embed --ldflags)
unix:LIBS   += -L$${PWD}/extern/libkam/build -lkam

INCLUDEPATH += extern/pybind11/include \
               extern/libkam/include   \
               include


ADAPTOR_DIR = src/adaptors
ADAPTOR_DESTDIR = $${DESTDIR}/adaptors
ADAPTOR_CXX = g++ -O3 $${QMAKE_CXXFLAGS} -shared -fPIC    \
              $(python3 -m pybind11 --includes)           \
              -I$${PWD}/extern/pybind11/include -std=c++2a


make_libkam.target   = $${PWD}/extern/libkam/build/libkam.so
make_libkam.commands = cd $${PWD}/extern/libkam && \
                       make &&                     \
                       cd ../../


adaptor_prepare.target = $${DESTDIR}/adaptors
adaptor_prepare.commands = mkdir -p $${DESTDIR}/adaptors


bit_adaptor.target   = $${ADAPTOR_DESTDIR}/bit$$system(python3-config --extension-suffix)
bit_adaptor.commands = $${ADAPTOR_CXX} $${PWD}/$${ADAPTOR_DIR}/bit_adaptor.cpp                    \
                         -o $${ADAPTOR_DESTDIR}/bit$$system(python3-config --extension-suffix)
bit_adaptor.depends = adaptor_prepare


vector_adaptor.target   = $${ADAPTOR_DESTDIR}/vector$$system(python3-config --extension-suffix)
vector_adaptor.commands = $${ADAPTOR_CXX} $${PWD}/$${ADAPTOR_DIR}/vector_adaptor.cpp              \
                         -o $${ADAPTOR_DESTDIR}/vector$$system(python3-config --extension-suffix)
vector_adaptor.depends = adaptor_prepare


PRE_TARGETDEPS      += $${PWD}/extern/libkam/build/libkam.so                                      \
                       $${ADAPTOR_DESTDIR}/bit$$system(python3-config --extension-suffix)         \
                       $${ADAPTOR_DESTDIR}/vector$$system(python3-config --extension-suffix)
QMAKE_EXTRA_TARGETS += make_libkam adaptor_prepare bit_adaptor vector_adaptor


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/mainwindow.h \
    include/python_function.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
