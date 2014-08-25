TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    object.cpp \
    layer.cpp \
    level.cpp \
    tileimg.cpp \
    game.cpp
QMAKE_CXXFLAGS += -std=c++11 -Wswitch
LIBS += -L"/usr/lib/"
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -ltinyxml  -lBox2D
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d -ltinyxml  -lBox2D
INCLUDEPATH += "/usr/include/SFML/"
DEPENDPATH += "/usr/include/SFML/"

HEADERS += \
    object.h \
    layer.h \
    level.h \
    tileimg.h \
    game.h
