#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T18:19:28
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets

TARGET = Pacman
TEMPLATE = app
include(engine/engine.pri)
include(ui/ui.pri)
include(agents/agents.pri)
SOURCES += main.cpp
CONFIG += c++11
OTHER_FILES += \
    ../Code/multiagent/layouts/smallClassic.lay \
    smallClassic.lay
QMAKE_CXXFLAGS_DEBUG +=  -pg
QMAKE_LFLAGS_DEBUG += -pg
RESOURCES += \
    res.qrc
win64:RC_ICONS += icon.ico
win32:RC_ICONS += icon.ico
cfg.path = $$OUT_PWD/
cfg.files += score.lst
cfg.files += config.cfg
lays.path = $$OUT_PWD/layouts
lays.files += layouts/originalClassic.lay
lays.files += layouts/mediumClassic.lay
lays.files += layouts/smallClassic.lay
INSTALLS += cfg
INSTALLS += lays



