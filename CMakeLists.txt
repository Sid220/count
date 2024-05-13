cmake_minimum_required(VERSION 3.22)
project(count C)

include(print_version.cmake)


###############################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

set(CPACK_PACKAGE_NAME "count")
set(CPACK_PACKAGE_VENDOR "Plios")
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "count the number of files in a directory")

set(CMAKE_C_STANDARD 11)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(libcount STATIC src/count.c)
target_include_directories( libcount
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )
add_executable(count src/main.c)

target_link_libraries(count libcount)

install(TARGETS count libcount
        COMPONENT linapp
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION "/usr/lib"
        DESTINATION bin
        )

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sidney Trzepacz") #required
INCLUDE(CPack)

###############################################################################
# Generate "config.h" from "cmake/config.h.cmake"
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG_H)
set(CONFIG_HEADER ${CMAKE_CURRENT_BINARY_DIR}/config.h)


###############################################################################
# Subdirectories
add_subdirectory(tests)


###############################################################################
# Unit tests
enable_testing()
add_test(NAME check_count COMMAND check_count)

