QT       += core gui
QT       += sql
QT       += svg
QT       += network
QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatboxconnectiondialog.cpp \
    client.cpp \
    connection.cpp \
    employee.cpp \
    excel.cpp \
    exportexcel.cpp \
    fournisseur.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow2.cpp \
    materiel.cpp \
    offre.cpp \
    produit.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegenratorworker.cpp \
    qrwidget.cpp \
    smtp.cpp \
    widget.cpp

HEADERS += \
    chatboxconnectiondialog.h \
    client.h \
    connection.h \
    employee.h \
    excel.h \
    exportexcel.h \
    fournisseur.h \
    login.h \
    mainwindow.h \
    mainwindow2.h \
    materiel.h \
    offre.h \
    produit.h \
    qcustomplot.h \
    qrcode.h \
    qrcodegenratorworker.h \
    qrwidget.h \
    smtp.h \
    widget.h

FORMS += \
    chatboxconnectiondialog.ui \
    mainwindow.ui \
    mainwindow2.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
