#
# [CMake](http://www.cmake.org/) Configuration
#
cmake_minimum_required (VERSION 2.8.4)
project (TutorialMatrixSTL CXX)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#SET(CMAKE_VERBOSE_MAKEFILE on )
SET(CMAKE_BUILD_TYPE       Release)

#enable_testing()

# find_package(MPI REQUIRED)
# set_property( DIRECTORY PROPERTY COMPILE_DEFINITIONS ${MPI_CXX_COMPILE_FLAGS} )
# include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})
# list(APPEND EXTRALIBS ${MPI_CXX_LIBRARIES})

#====== [Boost](http://www.boost.org/) ======
# Note: uBlas is part of the 'numeric' library and is NOT a compiled library
find_package(Boost COMPONENTS random program_options timer system REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
list(APPEND EXTRALIBS ${Boost_LIBRARIES})


# Sources of the main executable
set(matrix_HEADERS Matrix.h MatrixRuntimeExceptions.h)
set(matrix_SOURCE MatrixRuntimeExceptions.cpp)

add_executable(matrix_stl  main.cpp ${matrix_HEADERS} ${matrix_SOURCE})
target_link_libraries(matrix_stl ${EXTRALIBS})
