#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T09:26:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainwindow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        mainwindow.cpp \
    basicinformationmainwindow.cpp \
    tenantmanagemainwindow.cpp \
    commodity.cpp \
    roomdao.cpp \
    logindialog.cpp \
    member.cpp \
    databasedata.cpp \
    usermodifymainwindow.cpp \
    usermanagemainwindow.cpp \
    main.cpp \
    checkinformationdialog.cpp \
    roommanagemainwindow.cpp \
    staff.cpp \
    consumptionmainwindow.cpp



HEADERS += \
        mainwindow.h \
    basicinformationmainwindow.h \
    tenantmanagemainwindow.h \
    commodity.h \
    roomdao.h \
    logindialog.h \
    member.h \
    databasedata.h \
    usermodifymainwindow.h \
    usermanagemainwindow.h \
    checkinformationdialog.h \
    roommanagemainwindow.h \
    staff.h \
    consumptionmainwindow.h



FORMS += \
    tenantmanagemainwindow.ui \
    logindialog.ui \
    usermodifymainwindow.ui \
    checkinformationdialog.ui \
    basicinformationmainwindow.ui \
    usermanagemainwindow.ui \
    mainwindow.ui \
    roommanagemainwindow.ui \
    consumptionmainwindow.ui

RESOURCES += \
    background.qrc
