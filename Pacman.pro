#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T18:19:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Walls
TEMPLATE = app

include(engine/engine.pri)
include(ui/ui.pri)
include(agents/agents.pri)
SOURCES += main.cpp
#    elempainter.cpp \
#    layout.cpp \
#    canvas.cpp \
#    gamestate.cpp \
#    agent.cpp \
#    configuration.cpp \
#    actions.cpp \
#    agentstate.cpp \
#    gamestatedata.cpp \
#    pacmanrules.cpp \
#    util.cpp \
#    wallitem.cpp \
#    pacmankeyboarditem.cpp \
#    pacmanitem.cpp \
#    reflectagent.cpp

#HEADERS  += \
#    elempainter.h \
#    layout.h \
#    canvas.h \
#    gamestate.h \
#    agent.h \
#    configuration.h \
#    actions.h \
#    agentstate.h \
#    gamestatedata.h \
#    pacmanrules.h \
#    wallitem.h \
#    pacmankeyboarditem.h \
#    pacmanitem.h \
#    reflectagent.h

CONFIG += c++11

OTHER_FILES += \
    ../Code/multiagent/layouts/smallClassic.lay
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

HEADERS +=


