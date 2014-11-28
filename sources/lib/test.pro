#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T19:53:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    token.cpp \
    node.cpp \
    parser.cpp \
    assignationNode.cpp \
    calculable.cpp \
    calculableNode.cpp \
    operatorNode.cpp \
    varNode.cpp

SOURCES += lexer.cpp

HEADERS += \
    token.h \
    lexer.h \
    node.h \
    parser.h \
    assignationNode.h \
    calculable.h \
    calculableNode.h \
    operatorNode.h \
    varNode.h
