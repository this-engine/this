# Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
# This work is licensed under the terms of the MIT license. 
# For a copy, see <https://opensource.org/licenses/MIT>.

cmake_minimum_required (VERSION 3.16)


##
## glad
##
project (glad)

add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)
if (UNIX)
    target_link_libraries(glad -ldl)
endif (UNIX)
