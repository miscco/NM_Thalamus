TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=  Main.cpp \
	    Thalamic_Column.cpp \
	    Thalamus.cpp

HEADERS +=  ODE.h \
	    saves.h \
	    Thalamic_Column.h \
	    Stimulation.h

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES -= Thalamus.cpp
