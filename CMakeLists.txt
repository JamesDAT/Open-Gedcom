cmake_minimum_required(VERSION 3.16)

project(OpenGedcom VERSION 1.0.0 LANGUAGES CXX)

add_library(OpenGedcom)

add_library(OpenGedcom::OpenGedcom ALIAS OpenGedcom)

set(PUBLIC_INCLUDE include/OpenGedcom)

set(Reader_Files 
    src/Reader/GedcomReader.h
    src/Reader/GedcomReader.cpp

    src/Reader/SourceReaders/ISourceReader.h

    src/Reader/SourceReaders/Utf8SourceReader.h
    src/Reader/SourceReaders/Utf8SourceReader.cpp
)

set(Parser_Files
    src/Parser/GedcomParser.h
    src/Parser/GedcomParser.cpp
)

set(Views_Files
    src/Views/IndividualView.cpp
)

target_sources(OpenGedcom
    PUBLIC
        ${PUBLIC_INCLUDE}/OpenGedcom.h
        ${PUBLIC_INCLUDE}/GedcomViews.h
        ${PUBLIC_INCLUDE}/GedcomObject.h
        ${PUBLIC_INCLUDE}/GedcomStorage.h
    PRIVATE
        src/OpenGedcom.cpp
        src/GedcomStorage.cpp
        src/Tests.h
        src/TagTraversal.h

        ${Reader_Files}
        ${Parser_Files}
        ${Views_Files}
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
    add_subdirectory(tests)
endif()
