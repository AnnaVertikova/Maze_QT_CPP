QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/cave.cpp \
    model/maze.cpp \
    model/model.cpp \
    model/parser.cpp \
    model/pathfinder.cpp \
    view/view_cave.cpp \
    view/view_maze.cpp \
    view/widget_painter.cpp

HEADERS += \
    controller/controller.h \
    model/cave.h \
    model/errors.h \
    model/maze.h \
    model/model.h \
    model/parser.h \
    model/pathfinder.h \
    view/view_cave.h \
    view/view_maze.h \
    view/widget_painter.h

FORMS += \
    view/view_cave.ui \
    view/view_maze.ui

macx:ICON = view/Maze.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
