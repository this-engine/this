# Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
# This work is licensed under the terms of the MIT license. 
# For a copy, see <https://opensource.org/licenses/MIT>.

cmake_minimum_required (VERSION 3.16)

##
## this engine
##
project (this)

## Compilation flags
add_definitions("-Wall" "-g")

##
## libraries :
##

# openMP support
find_package(OpenMP)
# glad library :
add_subdirectory(lib/glad)
# glew
#find_package(GLEW REQUIRED)
#glfw
find_package(glfw3 3.3 REQUIRED)

##
## Core :
##
file(GLOB CORE_SRC CONFIGURE_DEPENDS src/core/*.cpp)
message( ${CORE_SRC} )
add_library(core ${CORE_SRC})

# core uses OMP for critical app
if(OpenMP_CXX_FOUND)
     target_link_libraries(core PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(core PUBLIC inc/core)

##
## Rendering :
##
file(GLOB RENDERING_SRC CONFIGURE_DEPENDS src/rendering/*.cpp)
message( ${RENDERING_SRC} )
add_library(rendering ${RENDERING_SRC})

# OPenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(rendering PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(rendering PUBLIC inc/rendering)
target_link_libraries(rendering PUBLIC core)


##
## thisGL :
##

file(GLOB THISGL_SRC CONFIGURE_DEPENDS src/thisGL/*.cpp)
message( ${THISGL_SRC} )
add_library(thisGL ${THISGL_SRC})
target_link_libraries(thisGL PUBLIC glad)

#if (GLEW_FOUND)
#    include_directories(${GLEW_INCLUDE_DIRS})
#    link_libraries(${GLEW_LIBRARIES})
#endif()

# OPenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(thisGL PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(thisGL PUBLIC GLEW)
target_link_libraries(thisGL PUBLIC glfw)
target_link_libraries(thisGL PUBLIC core)
target_link_libraries(thisGL PUBLIC glad)
target_link_libraries(thisGL PUBLIC rendering)
target_include_directories(thisGL PRIVATE inc/thisGL)

##
## Demo :
##
add_executable(this-demo src/main.cpp)
target_include_directories(this-demo PUBLIC inc)
target_link_libraries(this-demo core)
target_link_libraries(this-demo thisGL)
target_link_libraries(this-demo rendering)
