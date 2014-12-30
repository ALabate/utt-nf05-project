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
    lib/lexer.cpp \
    lib/parser.cpp \
    lib/token.cpp \
    lib/varNode.cpp \
    lib/expressionNode.cpp \
    lib/operator.cpp \
    lib/node.cpp \
    lib/calculables/matrix.cpp \
    lib/calculables/scalar.cpp \
    about.cpp \
    lib/matrixlib.cpp

HEADERS  += mainwindow.hpp \
    detailedlist.hpp \
    lib/assignationNode.h \
    lib/calculable.h \
    lib/lexer.h \
    lib/parser.h \
    lib/token.h \
    lib/varNode.h \
    lib/expressionNode.h \
    lib/operator.h \
    lib/node.h \
    lib/calculables/matrix.h \
    lib/calculables/scalar.h \
    about.h \
    lib/matrixlib.h

FORMS    += mainwindow.ui \
    about.ui
