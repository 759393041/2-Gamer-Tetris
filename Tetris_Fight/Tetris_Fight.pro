QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    cell.cpp \
    ishape.cpp \
    jshape.cpp \
    lshape.cpp \
    main.cpp \
    mainwindow.cpp \
    oshape.cpp \
    shape.cpp \
    sshape.cpp \
    tshape.cpp \
    zshape.cpp

HEADERS += \
    board.h \
    cell.h \
    ishape.h \
    jshape.h \
    lshape.h \
    mainwindow.h \
    oshape.h \
    public_define.h \
    shape.h \
    sshape.h \
    tshape.h \
    zshape.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
