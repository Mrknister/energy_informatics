cmake_minimum_required(VERSION 2.6)
project (analyze)
 
 
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

 
set(LIBANALYZE_FILES
${PROJECT_INCLUDE_DIR}/test2.h
${PROJECT_INCLUDE_DIR}/test.h
)


include_directories("${PROJECT_INCLUDE_DIR}")
 
 
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  ${PROJECT_INCLUDE_DIR}
)

install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION inc)