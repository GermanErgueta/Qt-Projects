QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changes.cpp \
    dirpaths.cpp \
    example.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    symbol.cpp \
    utilities.cpp \
    Windows/utilities_windows.cpp

HEADERS += \
    changes.h \
    dirpaths.h \
    example.h \
    mainwindow.h \
    model.h \
    symbol.h \
    utilities.h \
    Windows/utilities_windows.h

FORMS += \
    mainwindow.ui

# Conditional linking based on architecture
win32 {
    # Common libraries for both architectures
    LIBS += -lws2_32 -lwldap32 -lcrypt32 -lAdvapi32

    HOME_DIR = $$system(echo %USERPROFILE%)
    # Normalize path (replace backslashes with forward slashes)
    HOME_DIR ~= s,\\,/,g
    message(Home directory: $$HOME_DIR)

    # Check for MSVC
    contains(QMAKE_CXX, "cl") {
        message("Using MSVC compiler")
        DEFINES += USING_MSVC
    }

    # Check for MinGW
    contains(QMAKE_CXX, "g++") {
        message("Using MinGW compiler")
        DEFINES += USING_MINGW
    }

    # Conditional for ARM64
    contains(QMAKE_TARGET.arch, arm64) {

        # Paths to vcpkg installed libraries and include directories for both architectures
        # INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows-static/include

        INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_arm64/include
        LIBS += -L$$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_arm64/libs -lChilkatRel_arm64

    } else {
        # Check for MSVC
        contains(QMAKE_CXX, "cl") {
            message("Using MSVC compiler")
            DEFINES += USING_MINGW
            # Paths to vcpkg installed libraries and include directories for both architectures
            INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows-static/include
            # Add ARM64-specific Chilkat include and library paths

            # Add Win32-specific Chilkat include and library paths
            INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64/include
            LIBS += -L$$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64/libs -lChilkatRel_x64

            # INCLUDEPATH += D:/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/include
            # LIBS += -LD:/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/lib -lboost_system -lboost_filesystem
        }
        # Check for MinGW
        contains(QMAKE_CXX, "g++") {
            message("Using MinGW compiler")
            DEFINES += USING_MINGW
            # Paths to vcpkg installed libraries and include directories for both architectures
            INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows-static/include
            # Add ARM64-specific Chilkat include and library paths

            # Add Win32-specific Chilkat include and library paths
            INCLUDEPATH += $$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64/include
            LIBS += -L$$HOME_DIR/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64/libs -lChilkatRel_x64

            # INCLUDEPATH += D:/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/include
            # LIBS += -LD:/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/lib -lboost_system -lboost_filesystem
        }
    }
}


# Add Boost libraries
#LIBS += -lboost_system -lboost_filesystem

# Avoid conflicting default library
QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
