TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -m32 -Werror -Wall -Wextra -pedantic
QMAKE_LFLAGS += -static-libgcc -static-libstdc++

LIBS += -L"Y:\TDDC76\Fightwrench\SDL2-2.0.3\i686-w64-mingw32\lib" -lmingw32 -lSDL2_image -lSDL2_mixer -lSDL2main -lSDL2
INCLUDEPATH += "Y:\TDDC76\Fightwrench\SDL2-2.0.3\i686-w64-mingw32\include"

SOURCES += \
    main.cpp \
    graphic_engine.cpp\
    gameobject.cpp\
    gamefield.cpp \
    character.cpp \
    input_handler.cpp \
    game.cpp

HEADERS += \
    graphic_engine.h\
    gameobject.h\
    gamefield.h \
    character.h \
    input_handler.h \
    game.h
