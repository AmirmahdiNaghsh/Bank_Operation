INCLUDEPATH += $$PWD

# Add the Qt include paths
INCLUDEPATH += $$[QT_INSTALL_HEADERS]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtWidgets

# For debug builds
CONFIG(debug, debug|release) {
    DEFINES += DEBUG
    QMAKE_CXXFLAGS_DEBUG += -g3 -O0
}

# For release builds
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
    QMAKE_CXXFLAGS_RELEASE += -O2
}
