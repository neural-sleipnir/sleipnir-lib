cmake_minimum_required(VERSION 3.13)

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

project(SleipnirLib C)

set(CMAKE_C_STANDARD 99)

include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

set(SLEIPNIR_HDRS)
set(SLEIPNIR_SRCS)


file(GLOB HDRS_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
list(APPEND SLEIPNIR_HDRS ${HDRS_SOURCES})

file(GLOB IMPL_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.c")
list(APPEND SLEIPNIR_SRCS ${IMPL_SOURCES})

#
# library : sleipnir
#

add_library(sleipnir_lib ${SLEIPNIR_HDRS} ${SLEIPNIR_SRCS})
set_target_properties(sleipnir_lib PROPERTIES PUBLIC_HEADER "${SLEIPNIR_HDRS}")
target_include_directories(sleipnir_lib
        PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_link_libraries(sleipnir_lib PUBLIC ${CMAKE_DL_LIBS})
add_library(SleipnirLib::sleipnir_lib ALIAS sleipnir_lib)

#
# program : libsleipnir_demo
#

add_executable(libsleipnir_demo ${PROJECT_SOURCE_DIR}/src/utils/libsleipnir_demo.c)
target_link_libraries(libsleipnir_demo PRIVATE sleipnir_lib)
add_executable(SleipnirLib::libsleipnir_demo ALIAS libsleipnir_demo)

include(CTest)
if(BUILD_TESTING)
    enable_language(CXX)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    if(NOT TARGET gtest OR NOT TARGET gmock_main)
        # Download googletest.
        configure_file(
                cmake/googletest.CMakeLists.txt.in
                googletest-download/CMakeLists.txt
        )

        execute_process(
                COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

        if(result)
            message(FATAL_ERROR "CMake step for googletest failed: ${result}")
        endif()

        execute_process(
                COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

        if(result)
            message(FATAL_ERROR "Build step for googletest failed: ${result}")
        endif()

        # Add googletest directly to build.
        add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                ${CMAKE_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)
    endif()

    add_subdirectory(test)
endif()