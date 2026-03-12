cmake_minimum_required(VERSION 3.16)

project(OpenGedcom VERSION 1.0.0 LANGUAGES CXX)

add_library(OpenGedcom)

add_library(OpenGedcom::OpenGedcom ALIAS OpenGedcom)

set(PUBLIC_INCLUDE include/OpenGedcom)

set(Parser_Files
    src/Parser/Parser.hpp
    src/Parser/Parser.cpp
)

set(Views_Files
    
)

target_sources(OpenGedcom
    PUBLIC
        ${PUBLIC_INCLUDE}/OpenGedcom.hpp
        ${PUBLIC_INCLUDE}/IReader.hpp

        ${PUBLIC_INCLUDE}/Internal/OpenGedcom.ipp
        ${PUBLIC_INCLUDE}/Internal/Registry.hpp
        ${PUBLIC_INCLUDE}/Internal/Storage.hpp

    PRIVATE
        src/OpenGedcom.cpp
        src/Internal/Storage.cpp

        ${Parser_Files}
)

target_include_directories(OpenGedcom
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(OpenGedcom PUBLIC cxx_std_20)

option(OPENGEDCOM_BUILD_TESTS "Build OpenGedcom tests" OFF)

if (OPENGEDCOM_BUILD_TESTS)
    target_compile_definitions(OpenGedcom PRIVATE OPENGEDCOM_BUILD_TESTS)
    add_subdirectory(test)
endif()
