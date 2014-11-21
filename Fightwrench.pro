TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -m32 -Werror -Wall -Wextra -pedantic
QMAKE_LFLAGS += -static-libgcc -static-libstdc++

LIBS += -L"Y:\SDL2-2.0.3\i686-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2
INCLUDEPATH += "Y:\SDL2-2.0.3\i686-w64-mingw32\include"

SOURCES += main.cpp

