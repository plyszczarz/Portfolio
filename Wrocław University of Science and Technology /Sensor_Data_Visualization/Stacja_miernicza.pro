QT       += core gui
QT += serialport
QT += core
QT += widgets
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    second_dialog.cpp \
    serial_port_manager.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    second_dialog.h \
    serial_port_manager.h

FORMS += \
    mainwindow.ui \
    second_dialog.ui

TRANSLATIONS += \
    english.ts \
    polish.ts \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
