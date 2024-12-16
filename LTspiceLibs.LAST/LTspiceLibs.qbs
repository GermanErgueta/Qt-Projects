import qbs.FileInfo

QtApplication {
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.sql" }

    cpp.defines: [
        // You can make your code fail to compile if it uses deprecated APIs.
        // In order to do so, uncomment the following line.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    cpp.includePaths: [
        // Add the vcpkg include directory
        "C:/Users/ergue/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/include", // Adjust based on your platform
        "C:/Users/ergue/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat-x86_64-vc2022/include"
    ]


    cpp.libraryPaths: [
        // Add the vcpkg library directory
        "C:/Users/ergue/LTspiceDevelopment/Repos/vcpkg/installed/x64-windows/lib", // Adjust based on your platform
        "C:/Users/ergue/LTspiceDevelopment/SupportProjects/Qt-Projects/chilkat-x86_64-vc2022/libs"
    ]


    cpp.dynamicLibraries: [
        // Add the specific libraries you need from vcpkg
        // "boost_system",    // Example for Boost
        // "boost_filesystem", // Example for Boost
        // "libcurl",
        // "libssl",
        // "libcrypto",
        "ChilkatRel_x64",
        "ws2_32",
        "wldap32",
        "crypt32",
        "Advapi32",
    ]


    cpp.staticLibraries: [
        // Add the specific libraries you need from vcpkg
        //"boost_system",    // Example for Boost
        //"boost_filesystem", // Example for Boost
        // "libcurl",
        //"libssl",
        //"libcrypto",
        "ChilkatRel_x64",
        "ws2_32",
        "wldap32",
        "crypt32",
        "Advapi32",
    ]
    cpp.cxxFlags: [
        //"-MT" //"-MDd" or "-MT" or "-MD"
        // for single executable
        // for single executable exprement
        "-O2", // Enable optimization for release
        "-DNDEBUG" // Define NDEBUG to disable debug-specific code
        //for single executable experiment
    ]

    cpp.linkerFlags: [
        //" -NODEFAULTLIB:LIBCMT"
    ]

    // for single executable exprement
    cpp.optimization: "speed" // Optimize for speed, typical for release builds
    cpp.debugInformation: false // Disable debug information for release
    // for single executable exprement

    files: [
        "changes.cpp",
        "changes.h",
        "example.cpp",
        "example.h",
        "ftpclient.cpp",
        "ftpclient.h",
        "logger.cpp",
        "logger.h",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
        "model.cpp",
        "model.h",
        "symbol.cpp",
        "symbol.h",
        "utilities.cpp",
        "utilities.h",
        "Windows/utilities_windows.h",
        "Windows/utilities_windows.cpp",
    ]

    Group {
        // Configure the .ui files to use the Qt User Interface Compiler (uic)
        fileTagsFilter: ["ui"]
        qbs.install: false
    }

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
