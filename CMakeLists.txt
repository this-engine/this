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
## Qt :
##
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
FIND_PACKAGE(Qt5 COMPONENTS OpenGL REQUIRED)

set(HW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

##
## Core :
##
file(GLOB CORE_SRC CONFIGURE_DEPENDS src/core/*.cpp)
file(GLOB CORE_INC CONFIGURE_DEPENDS inc/core/*.hpp)
qt5_wrap_cpp(CORE_MOC_SRC ${CORE_INC})
message( ${CORE_SRC} )
add_library(core ${CORE_SRC} ${CORE_MOC_SRC})

set(HW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc/core)
#set(HW_GUI_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/gui)

target_link_libraries(core Qt5::Core)
target_link_libraries(core Qt5::Gui)
target_link_libraries(core Qt5::Widgets)
#target_link_libraries(core Qt5::OpenGL)
include_directories(${HW_HEADER_DIR})

##
## Game :
##
file(GLOB GAME_SRC CONFIGURE_DEPENDS src/game/*.cpp)
file(GLOB GAME_INC CONFIGURE_DEPENDS inc/game/*.hpp)
qt5_wrap_cpp(GAME_MOC_SRC ${GAME_INC})
message( ${GAME_SRC} )
add_library(game ${GAME_SRC} ${GAME_MOC_SRC})
set(HW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc/game)
#set(HW_GUI_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/gui)
target_link_libraries(game PUBLIC core)
#target_link_libraries(core Qt5::Core)
#target_link_libraries(core Qt5::Gui)
#target_link_libraries(core Qt5::Widgets)
#target_link_libraries(core Qt5::OpenGL)
include_directories(${HW_HEADER_DIR})

##
## Demo :
##
add_executable(this-demo src/main.cpp)
target_include_directories(this-demo PUBLIC inc)
target_link_libraries(this-demo core)
target_link_libraries(this-demo game)
