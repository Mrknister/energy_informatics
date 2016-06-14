cmake_minimum_required(VERSION 2.6)
project (performanceanalysis)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(DATALOADER_SRCS
${PROJECT_SOURCE_DIR}/main.c
${PROJECT_SOURCE_DIR}/detection_performance_evaluation.c
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)


add_custom_target(performanceanalysis_doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

if(TARGET doc)
    add_dependencies(doc performanceanalysis_doc)
endif(TARGET doc)


# add ini file parser 


set(DATA_LOADER_DATA_BUFFER_LEN 16000)

 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")



configure_file(data_loader_config.h.in data_loader_config.h)



add_executable(${PROJECT_NAME}  ${DATALOADER_SRCS})
target_link_libraries(${PROJECT_NAME} analyze)
target_link_libraries(${PROJECT_NAME} dataloader)
target_link_libraries(${PROJECT_NAME} "${SNDFILE_LIBRARIES}")


install (TARGETS ${PROJECT_NAME} DESTINATION bin)
