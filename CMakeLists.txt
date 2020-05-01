# Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
# This work is licensed under the terms of the MIT license. 
# For a copy, see <https://opensource.org/licenses/MIT>.

cmake_minimum_required (VERSION 3.0)

# this engine
project (this)


add_definitions("-Wall" "-g")

find_package(glfw3 3.3 REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB CORE_SRC src/core/*.cpp)
message( ${CORE_SRC} )

add_library(core ${CORE_SRC})

target_include_directories(core PRIVATE inc/core)
target_link_libraries(core PUBLIC glfw)
target_link_libraries(core PUBLIC SDL2)



add_executable(this-demo src/main)
target_include_directories(this-demo PUBLIC inc)
target_link_libraries(this-demo core)
target_link_libraries(this-demo glfw)
target_link_libraries(this-demo ${SDL2_LIBRARIES})
