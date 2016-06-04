cmake_minimum_required(VERSION 2.6)
project (dataloader)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(DATALOADER_SRCS
${PROJECT_SOURCE_DIR}/main.c
${PROJECT_SOURCE_DIR}/file_loader.c
${PROJECT_SOURCE_DIR}/file_config_loader.c
${PROJECT_SOURCE_DIR}/smart_meter_channels.c
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)




# add ini file parser 

set(INIH_SOURCES 
"${EXTERNAL_DEPENDENCIES_DIR}/inih/ini.c"
)
include_directories("${EXTERNAL_DEPENDENCIES_DIR}/inih")
set(DATALOADER_SRCS
${DATALOADER_SRCS}
${INIH_SOURCES}
)

set(DATA_LOADER_FILE_BUFFER_LEN 2056)
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")


find_package(SndFile REQUIRED)


configure_file(data_loader_config.h.in data_loader_config.h)



add_executable(${PROJECT_NAME}  ${DATALOADER_SRCS})
target_link_libraries(${PROJECT_NAME} -lm)
target_link_libraries(${PROJECT_NAME} analyze)
target_link_libraries(${PROJECT_NAME} "${SNDFILE_LIBRARIES}")


install (TARGETS ${PROJECT_NAME} DESTINATION bin)
