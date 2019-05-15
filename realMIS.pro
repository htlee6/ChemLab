#-------------------------------------------------
#
# Project created by QtCreator 2019-05-01T16:58:15
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
#QT       += axcontainer
QT       += multimediawidgets
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = realMIS
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        logindialog.cpp \
    connect_mysql.cpp \
    login.cpp \
    stuwindow.cpp \
    teacherwindow.cpp \
    adminwindow.cpp \
    util.cpp \
    stuinfodialog.cpp \
    teacherinfodialog.cpp \
    teachinginfodialog.cpp \
    stulogininfodialog.cpp \
    teacherlogininfodialog.cpp \
    medicineinfodialog.cpp \
    equipmentinfodialog.cpp \
    gradedialog.cpp \
    ratingdialog.cpp

HEADERS += \
        logindialog.h \
    connect_mysql.h \
    login.h \
    stuwindow.h \
    teacherwindow.h \
    adminwindow.h \
    util.h \
    stuinfodialog.h \
    teacherinfodialog.h \
    teachinginfodialog.h \
    stulogininfodialog.h \
    teacherlogininfodialog.h \
    medicineinfodialog.h \
    equipmentinfodialog.h \
    gradedialog.h \
    ratingdialog.h

FORMS += \
        logindialog.ui \
    stuwindow.ui \
    teacherwindow.ui \
    adminwindow.ui \
    stuinfodialog.ui \
    teacherinfodialog.ui \
    teachinginfodialog.ui \
    stulogininfodialog.ui \
    teacherlogininfodialog.ui \
    medicineinfodialog.ui \
    equipmentinfodialog.ui \
    gradedialog.ui \
    ratingdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
