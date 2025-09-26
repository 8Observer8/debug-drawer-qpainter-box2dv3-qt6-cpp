cmake_minimum_required(VERSION 3.19)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

project(debug-drawer-qpainter-box2dv3-qt6-cpp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(app
    WIN32 MACOSX_BUNDLE
    src/debug-drawer.h
    src/debug-drawer.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

target_link_libraries(app
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

if(ANDROID)
    # Include Box2D headers
    include_directories("${CMAKE_SOURCE_DIR}/libs/box2d-3.1.0-android/arm64-v8a/include")

    # Link static Bullet libraries
    target_link_libraries(app PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/box2d-3.1.0-android/arm64-v8a/lib/libbox2d.a
    )
endif()

if (WIN32)
    # Include Box2D headers
    include_directories("${CMAKE_SOURCE_DIR}/libs/box2d-3.1.0-mingw/arm64-v8a/include")

    # Link static Bullet libraries
    target_link_libraries(app PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/box2d-3.1.0-mingw/arm64-v8a/lib/libbox2d.a
    )
endif()
