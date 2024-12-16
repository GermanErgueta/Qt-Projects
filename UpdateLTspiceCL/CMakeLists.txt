cmake_minimum_required(VERSION 3.16)

project(UpdateLTspiceCL VERSION 0.1 LANGUAGES CXX)

# Enable Qt automatic tools
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect and set Qt installation directory based on architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM|aarch64")
        if(NOT DEFINED QT_INSTALL_DIR)
            set(QT_INSTALL_DIR "C:/Qt/6.8.1/msvc2022_arm64") # Update with your Qt installation path
        endif()
    else()
        if(NOT DEFINED QT_INSTALL_DIR)
            set(QT_INSTALL_DIR "C:/Qt/6.8.1/msvc2022_64") # Update with your Qt installation path
        endif()
    endif()
else() # 32-bit
    if(NOT DEFINED QT_INSTALL_DIR)
        set(QT_INSTALL_DIR "C:/Qt/6.8.1/msvc2022_64") # Update with your Qt installation path
    endif()
endif()
message("Using Qt installation at: ${QT_INSTALL_DIR}")

list(APPEND CMAKE_PREFIX_PATH "${QT_INSTALL_DIR}/lib/cmake")

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Sql)

# Detect home directory
if(WIN32)
    string(REPLACE "\\" "/" HOME_DIR $ENV{USERPROFILE})
else()
    set(HOME_DIR $ENV{HOME})
endif()
message("Home Directory: ${HOME_DIR}")

# Define Chilkat directories and library
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM|aarch64")
            set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_arm64")
            set(CHILKAT_LIB "${CHILKAT_DIR}/libs/ChilkatRel_arm64.lib")
        else()
            set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64")
            set(CHILKAT_LIB "${CHILKAT_DIR}/libs/ChilkatRel_x64.lib")
        endif()
    else() # 32-bit
        set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86")
        set(CHILKAT_LIB "${CHILKAT_DIR}/libs/ChilkatRel_x86.lib")
    endif()
elseif(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM|aarch64")
        set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_arm64")
        set(CHILKAT_LIB "${CHILKAT_DIR}/lib/libchilkat_arm64.a")
    else()
        set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64")
        set(CHILKAT_LIB "${CHILKAT_DIR}/lib/libchilkat_x86_64.a")
    endif()
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM|aarch64")
        set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_arm64")
        set(CHILKAT_LIB "${CHILKAT_DIR}/lib/libchilkat_arm64.so")
    else()
        set(CHILKAT_DIR "${HOME_DIR}/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat_x86_64")
        set(CHILKAT_LIB "${CHILKAT_DIR}/lib/libchilkat_x86_64.so")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

message("Chilkat Directory: ${CHILKAT_DIR}")
message("Chilkat Library: ${CHILKAT_LIB}")

# Include Chilkat headers
include_directories(${CHILKAT_DIR}/include)

# Define sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    changes.h changes.cpp
    dirpaths.h dirpaths.cpp
    example.h example.cpp
    model.h model.cpp
    symbol.h symbol.cpp
    Windows/utilities_windows.cpp Windows/utilities_windows.h
    utilities.h utilities.cpp
)

# Add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UpdateLTspiceCL
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(UpdateLTspiceCL ${PROJECT_SOURCES})
endif()

# Link libraries
target_link_libraries(UpdateLTspiceCL
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
    ${CHILKAT_LIB}
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(UpdateLTspiceCL PRIVATE ws2_32 wldap32 crypt32 Advapi32)
elseif(APPLE)
    # Add macOS-specific libraries if needed
elseif(UNIX)
    # Add Unix-specific libraries if needed
endif()

# Deployment for Windows
if(WIN32)
    set(WINDEPLOYQT_EXECUTABLE "${QT_INSTALL_DIR}/bin/windeployqt.exe")
    add_custom_command(TARGET UpdateLTspiceCL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Deploying with windeployqt..."
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:UpdateLTspiceCL>"
        COMMENT "Running windeployqt to deploy Qt dependencies"
    )
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS UpdateLTspiceCL
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize for Qt 6
if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(UpdateLTspiceCL)
endif()
