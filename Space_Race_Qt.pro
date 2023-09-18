QT       += core gui
QT += statemachine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/src/bullet.cpp \
    $$PWD/src/enemy.cpp \
    $$PWD/src/game.cpp \
    $$PWD/src/health.cpp \
    main.cpp \
    $$PWD/src/player.cpp \
    $$PWD/src/score.cpp

HEADERS += \
    $$PWD/src/bullet.h \
    $$PWD/src/enemy.h \
    $$PWD/src/game.h \
    $$PWD/src/health.h \
    $$PWD/src/player.h \
    $$PWD/src/score.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $$PWD/res/res.qrc
