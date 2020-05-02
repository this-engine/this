# Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
# This work is licensed under the terms of the MIT license. 
# For a copy, see <https://opensource.org/licenses/MIT>.

cmake_minimum_required (VERSION 3.16)

# this engine
project (this)


add_definitions("-Wall" "-g")

# glfw support
find_package(glfw3 3.3 REQUIRED)

# sdl2 support
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# openMP support
find_package(OpenMP)


# Core :
file(GLOB CORE_SRC CONFIGURE_DEPENDS src/core/*.cpp)
message( ${CORE_SRC} )
add_library(core ${CORE_SRC})
if(OpenMP_CXX_FOUND)
    target_link_libraries(core PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(core PRIVATE inc/core)
target_link_libraries(core PUBLIC glfw)
target_link_libraries(core PUBLIC SDL2)

# Demo :

add_executable(this-demo src/main.cpp)
target_include_directories(this-demo PUBLIC inc)
target_link_libraries(this-demo core)
