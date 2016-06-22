cmake_minimum_required(VERSION 2.6)
project (performanceanalysis)
 
set (performanceanalysis_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR})

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PERFORMANCEANALYSIS_SRCS
${PROJECT_SOURCE_DIR}/main.c
${PROJECT_SOURCE_DIR}/detection_performance_evaluation.c
${PROJECT_SOURCE_DIR}/save_data.c
)

include(${CMAKE_SOURCE_DIR}/cmake/Scripts/AddDoxygenTarget.cmake)
add_doxygen_target("performanceanalysis_doc")

# add ini file parser 


set(PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN 32000)
configure_file(performance_analysis_config.h.in performance_analysis_config.h)


include_directories(${performanceanalysis_INCLUDE_DIR})


add_executable(${PROJECT_NAME}  ${PERFORMANCEANALYSIS_SRCS})
target_link_libraries(${PROJECT_NAME} analyze)
target_link_libraries(${PROJECT_NAME} dataloader)


install (TARGETS ${PROJECT_NAME} DESTINATION bin)
