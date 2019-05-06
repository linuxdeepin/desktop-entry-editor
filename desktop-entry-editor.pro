#-------------------------------------------------
#
# Project created by QtCreator 2019-04-23T15:41:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop-entry-editor
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget Qt5Xdg

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

isEmpty(PREFIX) {
    PREFIX = /usr
}

# Automating generation .qm files from .ts files
!system($$PWD/translations/translate_generation.sh): error("Failed to generate translation")

qm_files.path = /usr/share/desktop-entry-editor/translations/
qm_files.files = translations/*.qm

desktop.files += *.desktop
desktop.path = $${PREFIX}/share/applications/

target.path = $${PREFIX}/bin/
INSTALLS += target desktop qm_files
