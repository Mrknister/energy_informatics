cmake_minimum_required(VERSION 2.6)
project (dataloader)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PROJECT1_SRCS 
${PROJECT_SOURCE_DIR}/main.c
${PROJECT_SOURCE_DIR}/file_loader.c

)

set(DATA_LOADER_FILE_BUFFER_LEN 2056)
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")


find_package(SndFile REQUIRED)


configure_file(data_loader_config.h.in data_loader_config.h)



add_executable(${PROJECT_NAME}  ${PROJECT1_SRCS})
target_link_libraries(${PROJECT_NAME} "${SNDFILE_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} analyze)

install (TARGETS ${PROJECT_NAME} DESTINATION bin)