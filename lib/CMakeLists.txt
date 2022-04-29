message("LIB____PROJECT_SOURCE_DIR=" ${PROJECT_SOURCE_DIR})

file(GLOB project_sources
    "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/*.cpp"
    )
file(GLOB project_headers
            "${PROJECT_SOURCE_DIR}/lib/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.h"
            "${PROJECT_SOURCE_DIR}/lib/pyboostcvconverter/*.hpp"
            )

add_library(pyboostconverter 
            ${project_sources}
            ${project_headers}
)
target_include_directories (pyboostconverter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})