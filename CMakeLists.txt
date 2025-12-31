cmake_minimum_required(VERSION 3.16)

project(OpenGedcom VERSION 1.0.0 LANGUAGES CXX)

add_library(OpenGedcom)

add_library(OpenGedcom::OpenGedcom ALIAS OpenGedcom)

set(PUBLIC_INCLUDE include/OpenGedcom)

target_sources(OpenGedcom
    PUBLIC
        ${PUBLIC_INCLUDE}/OpenGedcom.h
        ${PUBLIC_INCLUDE}/GedcomViews.h
        ${PUBLIC_INCLUDE}/GedcomObject.h
    PRIVATE
        src/OpenGedcom.cpp
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
    add_subdirectory(tests)
endif()
