QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrlist.cpp \
    dialog_arrlist_append.cpp \
    dialog_arrlist_delete.cpp \
    dialog_arrlist_edit.cpp \
    dialog_arrlist_insert.cpp \
    dialog_arrlist_load.cpp \
    link.cpp \
    linkstack.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arrlist.h \
    dialog_arrlist_append.h \
    dialog_arrlist_delete.h \
    dialog_arrlist_edit.h \
    dialog_arrlist_insert.h \
    dialog_arrlist_load.h \
    link.h \
    linkstack.h \
    mainwindow.h \
    methods.h \
    struct.h

FORMS += \
    dialog_arrlist_append.ui \
    dialog_arrlist_delete.ui \
    dialog_arrlist_edit.ui \
    dialog_arrlist_insert.ui \
    dialog_arrlist_load.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
