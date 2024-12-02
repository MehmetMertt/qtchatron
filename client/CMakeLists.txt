cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appClient
    main.cpp
)

qt_add_qml_module(appClient
    URI Client
    VERSION 1.0
    RESOURCES qml.qrc
    RESOURCES res.qrc
    SOURCES clientcontroller.h clientcontroller.cpp
    SOURCES client.h client.cpp
    SOURCES Communicator/Communicator.h Communicator/Communicator.cpp
    SOURCES chatmessageitem.h chatmessageitem.cpp
    SOURCES chatmessagelist.h chatmessagelist.cpp
    SOURCES chatmodel.h chatmodel.cpp
    SOURCES mainpagerouter.h mainpagerouter.cpp
    SOURCES sessionuser.h sessionuser.cpp
    SOURCES user.h user.cpp
    SOURCES channelmodel.h channelmodel.cpp
    SOURCES router.h router.cpp
    SOURCES authmodel.h authmodel.cpp
    SOURCES authcontroller.h authcontroller.cpp
    SOURCES user.h user.cpp
    SOURCES sessionmodel.h sessionmodel.cpp
    SOURCES Protocol/protocol.h Protocol/protocol.cpp
    SOURCES chatcontroller.h chatcontroller.cpp
    SOURCES channelmodel.h channelmodel.cpp
    SOURCES channel.h channel.cpp
    SOURCES channelcontroller.h channelcontroller.cpp
    SOURCES threadmodel.h threadmodel.cpp
    SOURCES thread.h thread.cpp
    SOURCES threadcontroller.h threadcontroller.cpp
)

# Add the SharedProtocol subdirectory

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appClient
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
