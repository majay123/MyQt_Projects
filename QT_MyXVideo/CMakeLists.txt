cmake_minimum_required(VERSION 3.5)

project(QT_MyXVideo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/Users/mcd/Qt/6.2.3/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED) 
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)


#添加OPENCV库
find_package(OpenCV REQUIRED)
#添加OpenCV头文件
include_directories(${OpenCV_INCLUDE_DIRS})

# message(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        xvideo.cpp
        xvideo.h
        xvideo.ui
        videowidget.h
        videowidget.cpp
        videothread.h
        videothread.cpp
        filter.h
        filter.cpp
        imagepro.h
        imagepro.cpp
)

#add image resource
qt_add_resources(PROJECT_SOURCES image.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_MyXVideo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QT_MyXVideo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT_MyXVideo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT_MyXVideo
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT_MyXVideo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})
target_link_libraries(QT_MyXVideo PRIVATE Qt6::Core)
target_link_libraries(QT_MyXVideo PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(QT_MyXVideo PRIVATE Qt6::Gui)

target_include_directories(QT_MyXVideo PRIVATE "${CMAKE_BINARY_DIR}/QT_MyXVideo_autogen/include/")

#target_link_libraries(QT_MyXVideo  ${OpenCV_LIBS})
#/usr/local/opt/opencv/lib

set_target_properties(QT_MyXVideo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT_MyXVideo)
endif()
