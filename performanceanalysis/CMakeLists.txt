cmake_minimum_required(VERSION 2.6)
project (performanceanalysis)
 
set (performanceanalysis_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR})

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PERFORMANCEANALYSIS_SRCS
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

    if(NOT TARGET doc)
        add_custom_target(doc)
    endif(NOT TARGET doc)
    add_dependencies(doc performanceanalysis_doc)

endif(DOXYGEN_FOUND)

if(NOT TARGET doc)
    add_custom_target(doc)
endif(NOT TARGET doc)
add_dependencies(doc performanceanalysis_doc)


# add ini file parser 


set(PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN 16000)
configure_file(performance_analysis_config.h.in performance_analysis_config.h)


include_directories(${performanceanalysis_INCLUDE_DIR})


add_executable(${PROJECT_NAME}  ${PERFORMANCEANALYSIS_SRCS})
target_link_libraries(${PROJECT_NAME} analyze)
target_link_libraries(${PROJECT_NAME} dataloader)


install (TARGETS ${PROJECT_NAME} DESTINATION bin)
