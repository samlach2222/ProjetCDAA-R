QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LOGIC/fichecontact.cpp \
    LOGIC/gestioncontact.cpp \
    LOGIC/horodatage.cpp \
    LOGIC/interaction.cpp \
    LOGIC/log.cpp \
    STORAGE/databasestorage.cpp \
    STORAGE/jsonstorage.cpp \
    main.cpp \
    IHM/mainwindow.cpp

HEADERS += \
    IHM/mainwindow.h \
    LOGIC/fichecontact.h \
    LOGIC/gestioncontact.h \
    LOGIC/horodatage.h \
    LOGIC/interaction.h \
    LOGIC/log.h \
    STORAGE/databasestorage.h \
    STORAGE/jsonstorage.h

FORMS += \
    IHM/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
