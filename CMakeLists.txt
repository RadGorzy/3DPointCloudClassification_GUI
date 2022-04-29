cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(3DPointCloudClassification_GUI)
message("CMAKE_MAKE_PROGRMA= ${CMAKE_MAKE_PROGRAM}")

set(CMAKE_CXX_STANDARD 14)
# find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets OpenGL)
# need this to include the auto generated ui_mainwindow.h
# file from the qt5_wrap_ui call below.

find_package(PCL 1.9 REQUIRED)
find_package( OpenCV REQUIRED )

find_package( PythonInterp 3.5 REQUIRED )
find_package( PythonLibs 3.5 REQUIRED )

#for python embedding:
find_package( Boost REQUIRED python38)
find_package(Boost COMPONENTS system thread python38 REQUIRED) #find_package(Boost COMPONENTS system thread python-py35 REQUIRED)

find_package(OpenMP REQUIRED) # Find the package

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

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

include_directories("${PROJECT_SOURCE_DIR}/lib")
                    
add_subdirectory(lib)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)







