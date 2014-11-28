#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T21:44:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utt-nf05-project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    detailedlist.cpp \
    lib/assignationNode.cpp \
    lib/calculable.cpp \
    lib/calculableNode.cpp \
    lib/lexer.cpp \
    lib/node.cpp \
    lib/operatorNode.cpp \
    lib/parser.cpp \
    lib/token.cpp \
    lib/varNode.cpp

HEADERS  += mainwindow.hpp \
    detailedlist.hpp \
    lib/assignationNode.h \
    lib/calculable.h \
    lib/calculableNode.h \
    lib/lexer.h \
    lib/node.h \
    lib/operatorNode.h \
    lib/parser.h \
    lib/token.h \
    lib/varNode.h

FORMS    += mainwindow.ui
