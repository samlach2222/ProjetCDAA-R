QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

PRECOMPILED_HEADER = precompiled-header.h
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IHM/ui_filtercontact.cpp \
    IHM/ui_interactioncontact.cpp \
    IHM/ui_requestcontact.cpp \
    IHM/ui_savegestioncontact.cpp \
    LOGIC/fichecontact.cpp \
    LOGIC/gestioncontact.cpp \
    LOGIC/horodatage.cpp \
    LOGIC/interaction.cpp \
    LOGIC/log.cpp \
    LOGIC/soundplayer.cpp \
    LOGIC/tagsinteraction.cpp \
    STORAGE/databasestorage.cpp \
    STORAGE/jsonstorage.cpp \
    main.cpp \
    IHM/mainwindow.cpp

HEADERS += \
    IHM/mainwindow.h \
    IHM/ui_filtercontact.h \
    IHM/ui_interactioncontact.h \
    IHM/ui_requestcontact.h \
    IHM/ui_savegestioncontact.h \
    LOGIC/fichecontact.h \
    LOGIC/gestioncontact.h \
    LOGIC/horodatage.h \
    LOGIC/interaction.h \
    LOGIC/log.h \
    LOGIC/soundplayer.h \
    LOGIC/tagsinteraction.h \
    STORAGE/databasestorage.h \
    STORAGE/jsonstorage.h

FORMS += \
    IHM/mainwindow.ui \
    IHM/ui_filtercontact.ui \
    IHM/ui_interactioncontact.ui \
    IHM/ui_requestcontact.ui \
    IHM/ui_savegestioncontact.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

