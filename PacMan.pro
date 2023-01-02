TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
include(minGL2/mingl.pri)

HEADERS += \
    structure_elements.hpp \
    structure_jeu.hpp \
    structures_pacman.hpp
