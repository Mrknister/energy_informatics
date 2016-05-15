cmake_minimum_required(VERSION 2.6)
project(energy_informatics)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")



add_subdirectory("${CMAKE_SOURCE_DIR}/libanalyze")
add_subdirectory("${CMAKE_SOURCE_DIR}/dataloader")


