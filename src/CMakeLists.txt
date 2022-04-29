file(GLOB project_sources
    "${PROJECT_SOURCE_DIR}/src/model/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/controller/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/view/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/*.cpp"
    #"${PROJECT_SOURCE_DIR}/tests/*.cpp"
    )
file(GLOB project_headers
            "${PROJECT_SOURCE_DIR}/src/model/*.h"
            "${PROJECT_SOURCE_DIR}/src/controller/*.h"
            "${PROJECT_SOURCE_DIR}/src/view/*.h"
            "${PROJECT_SOURCE_DIR}/lib/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.hpp"
            #"${PROJECT_SOURCE_DIR}/tests/include/gtest/*.h"
            )
file(GLOB project_ui
    "${PROJECT_SOURCE_DIR}/src/ui/*.ui"
    )

#equivalent of DEFINES += QT_NO_VERSION_TAGGING in .pro file -> https://forum.qt.io/topic/38865/solved-cmake-equivalent-of-qmake-defines/3
#add_definitions(-DQT_NO_VERSION_TAGGING)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})

add_library(classifier
"${PROJECT_SOURCE_DIR}/src/model/classification.cpp"
"${PROJECT_SOURCE_DIR}/src/model/classification.h")
target_link_libraries(classifier PUBLIC pyboostconverter)
target_include_directories (classifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(modifier
"${PROJECT_SOURCE_DIR}/src/model/benchmarkAndVisualize.cpp"
"${PROJECT_SOURCE_DIR}/src/model/edit.cpp"
"${PROJECT_SOURCE_DIR}/src/model/projection.cpp"
"${PROJECT_SOURCE_DIR}/src/model/segmentation.cpp"
"${PROJECT_SOURCE_DIR}/src/model/benchmarkAndVisualize.h"
"${PROJECT_SOURCE_DIR}/src/model/edit.h"
"${PROJECT_SOURCE_DIR}/src/model/projection.h"
"${PROJECT_SOURCE_DIR}/src/model/segmentation.h")
target_link_libraries(modifier
${PCL_LIBRARIES}
${OpenCV_LIBS})

add_library(pointcloud 
"${PROJECT_SOURCE_DIR}/src/model/pointCloud.cpp"
"${PROJECT_SOURCE_DIR}/src/model/cloudFactory.cpp"
"${PROJECT_SOURCE_DIR}/src/model/prepareDataset.cpp"
"${PROJECT_SOURCE_DIR}/src/controller/pointCloudController.cpp"
"${PROJECT_SOURCE_DIR}/src/controller/prepareDatasetController.cpp"
"${PROJECT_SOURCE_DIR}/src/controller/threadController.cpp"
"${PROJECT_SOURCE_DIR}/src/view/configuration.cpp"
"${PROJECT_SOURCE_DIR}/src/view/mainwindow.cpp"
"${PROJECT_SOURCE_DIR}/src/view/memorySettings.cpp"
"${PROJECT_SOURCE_DIR}/src/view/saveLoad.cpp"
"${PROJECT_SOURCE_DIR}/src/view/saveSettings.cpp"
"${PROJECT_SOURCE_DIR}/src/model/pointCloud.h"
"${PROJECT_SOURCE_DIR}/src/model/cloudFactory.h"
"${PROJECT_SOURCE_DIR}/src/model/prepareDataset.h"
"${PROJECT_SOURCE_DIR}/src/controller/typeDefForThreding.h"
"${PROJECT_SOURCE_DIR}/src/controller/pointCloudController.h"
"${PROJECT_SOURCE_DIR}/src/controller/prepareDatasetController.h"
"${PROJECT_SOURCE_DIR}/src/controller/threadController.h"
"${PROJECT_SOURCE_DIR}/src/view/configuration.h"
"${PROJECT_SOURCE_DIR}/src/view/mainwindow.h"
"${PROJECT_SOURCE_DIR}/src/view/memorySettings.h"
"${PROJECT_SOURCE_DIR}/src/view/saveLoad.h"
"${PROJECT_SOURCE_DIR}/src/view/saveSettings.h"
${ui_wrap} 
${moc_sources})
target_link_libraries(pointcloud PUBLIC 
        classifier
        modifier
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${VTK_LIBRARIES}
        ${PCL_LIBRARIES}
        ${OpenMP_CXX_LIBRARIES})
target_include_directories (pointcloud PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(target "${PROJECT_SOURCE_DIR}/src/view/main.cpp")
target_link_libraries(target PUBLIC pointcloud)
