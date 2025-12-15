QT       += core gui sql
QT      +=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dealdatabase.cpp \
    main.cpp \
    maininterface.cpp \
    mainwindow.cpp \
    manager/manager.cpp \
    user/billrecord.cpp \
    user/dataanalyse.cpp \
    user/diary.cpp \
    user/englishrecord.cpp \
    user/studyrecord.cpp

HEADERS += \
    dealdatabase.h \
    maininterface.h \
    mainwindow.h \
    manager/manager.h \
    user/billrecord.h \
    user/dataanalyse.h \
    user/diary.h \
    user/englishrecord.h \
    user/studyrecord.h

FORMS += \
    maininterface.ui \
    mainwindow.ui \
    manager/manager.ui \
    user/billrecord.ui \
    user/diary.ui \
    user/englishrecord.ui \
    user/studyrecord.ui \
    user/dataanalyse.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imageindex.qrc
