HEADERS += ui/canvas.h \
    ui/ghostitem.h \
    ui/graphicobject.h \
    ui/scoretext.h
SOURCES += ui/canvas.cpp \
    ui/ghostitem.cpp \
    ui/graphicobject.cpp \
    ui/scoretext.cpp

HEADERS += ui/pacmanitem.h
SOURCES += ui/pacmanitem.cpp
HEADERS += ui/elempainter.h
SOURCES += ui/elempainter.cpp
HEADERS += ui/wallitem.h
SOURCES += ui/wallitem.cpp
HEADERS += ui/pacmankeyboarditem.h
SOURCES += ui/pacmankeyboarditem.cpp
include(menu/menu.pri)
