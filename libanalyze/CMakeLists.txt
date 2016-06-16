cmake_minimum_required(VERSION 2.6)
project (analyze)
 
 
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)


set(DATA_POINTS_PER_FEATURE 8000)
set(DATA_POINTS_PER_WAVE_LENGTH 320)
set(CURRENT_DIFFERENCE_EVENT_TRIGGER 1.0)
configure_file(${PROJECT_SOURCE_DIR}/libanalyze_config.h.in libanalyze_config.h)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_BINARY_DIR}")



install(TARGETS ${PROJECT_NAME}
        INCLUDES DESTINATION include/
        ARCHIVE DESTINATION lib/
)


FILE(GLOB_RECURSE LibFiles "${PROJECT_INCLUDE_DIR}/*.h")
set(LibFiles ${LibFiles} ${PROJECT_BINARY_DIR}/libanalyze_config.h})

install(FILES
        ${LibFiles}
      DESTINATION include/
    )

