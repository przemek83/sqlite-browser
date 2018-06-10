QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLiteBrowser
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    AddRowDialog.cpp \
    DatabaseConfig.cpp

HEADERS += \
    MainWindow.h \
    AddRowDialog.h \
    DatabaseConfig.h

FORMS += \
    MainWindow.ui \
    AddRowDialog.ui

RESOURCES += \
    icons.qrc
