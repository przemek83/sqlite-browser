QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLiteBrowser
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/AddRowDialog.cpp \
    src/DatabaseConfig.cpp

HEADERS += \
    src/MainWindow.h \
    src/AddRowDialog.h \
    src/DatabaseConfig.h

FORMS += \
    src/MainWindow.ui \
    src/AddRowDialog.ui

RESOURCES += \
    icons.qrc
