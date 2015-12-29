TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET   =  Thalamus.cpp

SOURCES +=  Thalamic_Column.cpp \
            Thalamus_mex.cpp    \
            Thalamus.cpp

HEADERS +=  Data_Storage.h      \
            ODE.h               \
            Random_Stream.h     \
            Stimulation.h       \
            Thalamic_Column.h

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES -= Thalamus_mex.cpp
