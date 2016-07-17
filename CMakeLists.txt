cmake_minimum_required(VERSION 2.6)
project(energy_informatics)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(EXTERNAL_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/external")

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-Wall -g -std=gnu99")
set(CMAKE_C_FLAGS_RELEASE "-O3 ")

set(CMAKE_C_FLAGS_DEBUG "-O0 ")

add_custom_target(doc)

add_subdirectory("${CMAKE_SOURCE_DIR}/libanalyze")
add_subdirectory("${CMAKE_SOURCE_DIR}/dataloader")
add_subdirectory("${CMAKE_SOURCE_DIR}/performanceanalysis")

