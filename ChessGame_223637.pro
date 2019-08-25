#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T19:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessGame_223637
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

CONFIG += c++11

SOURCES += \
        actionbutton.cpp \
        boardfield.cpp \
        boardview.cpp \
        game.cpp \
        main.cpp \
        pawnmanager.cpp \
        pawnmodel.cpp \
        pawnposition.cpp

HEADERS += \
        actionbutton.h \
        boardfield.h \
        boardview.h \
        game.h \
        pawncolortype.h \
        pawnmanager.h \
        pawnmodel.h \
        pawnposition.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/bishop_black.svg \
    Images/bishop_white.svg \
    Images/king_black.svg \
    Images/king_white.svg \
    Images/knight_black.svg \
    Images/knight_white.svg \
    Images/pawn_black.svg \
    Images/pawn_white.svg \
    Images/queen_black.svg \
    Images/queen_white.svg \
    Images/rook_black.svg \
    Images/rook_white.svg
