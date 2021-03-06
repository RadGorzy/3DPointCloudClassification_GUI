cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(3DPointCloudClassification_GUI)

set(CMAKE_CXX_STANDARD 14)

# find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets OpenGL)
# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.
#if you didnt 'make install' vtk -> show path to your vtk build below, for ex.:
#set(VTK_DIR "/home/user/VTK/VTK-8.2.0-qt5-build")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(PCL 1.9 REQUIRED)
find_package( OpenCV REQUIRED )

find_package( PythonInterp 3.5 REQUIRED )
find_package( PythonLibs 3.5 REQUIRED )

#for python embedding:
find_package( Boost COMPONENTS python REQUIRED )
find_package(Boost COMPONENTS system thread python-py35 REQUIRED)

find_package(OpenMP REQUIRED) # Find the package

# Fix a compilation bug under ubuntu 16.04 (Xenial)
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")


set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(${EIGEN_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories( ${Boost_INCLUDE_DIR})

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
#####################################################################
#[[
set(project_sources mainwindow.cpp main.cpp  pointCloud.cpp  projection.cpp  segmentation.cpp  cloudFactory.cpp   pyboostcvconverter/pyboost_cv3_converter.cpp classification.cpp benchmarkAndVisualize.cpp edit.cpp prepareDataset.cpp
    pointCloudController.cpp threadController.cpp prepareDatasetController.cpp
    configuration.cpp saveLoad.cpp
    saveSettings.cpp)
set(project_headers mainwindow.h pointCloud.h projection.h segmentation.h cloudFactory.h helperFunctions.h pyboostcvconverter/pyboostcvconverter.hpp classification.h benchmarkAndVisualize.h edit.h prepareDataset.h Python_wrapper.h
    pointCloudController.h threadController.h typeDefForThreding.h qdebugStream.h prepareDatasetController.h
    configuration.h saveLoad.h
    saveSettings.h)
set(project_ui mainwindow.ui saveSettings.ui)
]]

file(GLOB project_sources
    "${PROJECT_SOURCE_DIR}/src/model/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/controller/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/view/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/*.cpp"
    )
file(GLOB project_headers
            "${PROJECT_SOURCE_DIR}/src/model/*.h"
            "${PROJECT_SOURCE_DIR}/src/controller/*.h"
            "${PROJECT_SOURCE_DIR}/src/view/*.h"
            "${PROJECT_SOURCE_DIR}/lib/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.hpp"
            )
file(GLOB project_ui
    "${PROJECT_SOURCE_DIR}/src/ui/*.ui"
    )

#equivalent of DEFINES += QT_NO_VERSION_TAGGING in .pro file -> https://forum.qt.io/topic/38865/solved-cmake-equivalent-of-qmake-defines/3
#add_definitions(-DQT_NO_VERSION_TAGGING)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})

add_executable(${PROJECT_NAME} 
${project_sources} 
${project_headers}
${ui_wrap} 
${moc_sources})

#qt5_use_modules(${PROJECT_NAME} Widgets Core Gui)
#This is similar to how qmake operates:

#TARGET = hello_world
#QT += widgets declarative

target_link_libraries(${PROJECT_NAME} 
	PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${VTK_LIBRARIES}
        ${PCL_LIBRARIES}
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES}
         ${OpenMP_CXX_LIBRARIES})

# auto copy dlls if on windows
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${VTK_LIBRARIES}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PCL_LIBRARIES}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${OpenCV_LIBS}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PYTHON_LIBRARIES}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${Boost_LIBRARIES}> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN32)




