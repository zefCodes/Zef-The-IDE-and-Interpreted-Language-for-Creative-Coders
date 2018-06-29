#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T20:29:20
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zefIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        mainwindow.cpp \
    main.cpp \
    zefopengl.cpp \



HEADERS += \
        mainwindow.h \
    ../../Lexical_Analysis/lexer.h \
    ../../Lexical_Analysis/TOKEN.h \
    ../../Lexical_Analysis/token_Buffer.h \
    ../../Lexical_Analysis/tokenIdentifier.h \
    ../../Lexical_Analysis/tokenizer.h \
    ../../Lexical_Analysis/zex.h \
    ../../Syntax_Analysis/Parsing_Table.h \
    ../../Syntax_Analysis/RULES.h \
    ../../Semantic_Analysis/DataType.h \
    ../../Semantic_Analysis/instructions.h \
    ../../Semantic_Analysis/semantic_actions.h \
    ../../Semantic_Analysis/typeSolver.h \
    ../../Interpretation/PrimitiveFunctions.h \
    ../../Interpretation/zinterpreter.h \
    ../../Syntax_Analysis/errors.h \
    ../../Syntax_Analysis/Parser.h \
    zefopengl.h \



FORMS += \
        mainwindow.ui

DISTFILES += \


LIBS += -LD:\Qt\5.5\mingw492_32\lib\libQt5OpenGL.a -lopengl32
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS_RELEASE -= -O1
