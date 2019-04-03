cmake_minimum_required(VERSION 3.0.0)
project(camel)

#set flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -l armadillo -std=c++17")

#Bring the headers into the project
include_directories(include)
file(GLOB_RECURSE HEADERS "include/*.hpp" )

#Include source files for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")

#Link armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

#Generate the static library from the sources
add_library(camel STATIC ${SOURCES})
target_link_libraries(camel ${ARMADILLO_LIBRARIES})


#Install library
install(TARGETS camel DESTINATION lib)

#Install header files
install(FILES ${HEADERS} DESTINATION include/camel)