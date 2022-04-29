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
${project_sources} 
${project_headers}
${ui_wrap} 
${moc_sources})

target_link_libraries(classifier PUBLIC 
        pyboostconverter
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${VTK_LIBRARIES}
        ${PCL_LIBRARIES}
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES}
         ${OpenMP_CXX_LIBRARIES})

target_include_directories (classifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(target
${project_sources} 
${project_headers}
${ui_wrap} 
${moc_sources})

target_link_libraries(target PUBLIC classifier)
