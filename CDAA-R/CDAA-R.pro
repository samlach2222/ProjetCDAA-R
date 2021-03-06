QT       += core gui \
         multimedia \
		 sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:RC_ICONS += Logo.ico
CONFIG += c++11

win32-msvc{
	DEFINES+=UWP
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    IHM/mainwindow.cpp \
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
    STORAGE/jsonstorage.cpp

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

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

