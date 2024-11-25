cmake_minimum_required(VERSION 3.16)

project(client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appclient
    main.cpp
)

qt_add_qml_module(appclient
    URI appclient
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES




        chatclient.h
        chatclient.cpp
    RESOURCES
        certs/client.crt
        certs/client.key
        certs/sslserver.pem
        certs/server.crt
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appclient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appclient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

target_link_libraries(appclient
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appclient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
