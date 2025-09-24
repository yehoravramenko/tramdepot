cmake_minimum_required(VERSION 3.15)
project(TramDepot)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utils)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tramdepot)

set(CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_subdirectory(src/TramDepot)

#add_custom_command(TARGET winyl POST_BUILD
#    COMMAND copy compile_commands.json ..
#)
