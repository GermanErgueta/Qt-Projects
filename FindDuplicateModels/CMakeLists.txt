
cmake_minimum_required(VERSION 3.16)

# Set the project name
project(FindDuplicateModels VERSION 1.0 LANGUAGES CXX)

# Find the necessary Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Tell CMake to create a macOS app bundle
set(MACOSX_BUNDLE TRUE)

# Specify the source files
set(SOURCES
    main.cpp
    # Add other source files here
)

# Add the executable, mark it as a macOS bundle
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})

# Link against Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Optional: Specify an icon for the app (macOS uses .icns format)
set(MACOSX_BUNDLE_ICON_FILE "app_icon.icns")
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/app_icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Optional: Provide a custom Info.plist for macOS
set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)

# Set the target macOS version
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15") # Adjust based on your minimum macOS target
