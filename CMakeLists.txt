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
    src/Views/TagTreeParser.hpp
    src/Views/ViewBase.cpp
    src/Views/IndiView.cpp
    src/Views/DateView.cpp
    src/Views/BirthView.cpp
    src/Views/PlaceView.cpp
)

target_sources(OpenGedcom
    PUBLIC
        ${PUBLIC_INCLUDE}/OpenGedcom.hpp
        ${PUBLIC_INCLUDE}/IReader.hpp

        ${PUBLIC_INCLUDE}/Internal/OpenGedcom.ipp
        ${PUBLIC_INCLUDE}/Internal/Registry.hpp
        ${PUBLIC_INCLUDE}/Internal/StringArena.hpp
        ${PUBLIC_INCLUDE}/Internal/RecordStorage.hpp
        ${PUBLIC_INCLUDE}/Internal/Xref.hpp

        ${PUBLIC_INCLUDE}/Tags/TagBase.hpp
        ${PUBLIC_INCLUDE}/Tags/TagTraits.hpp
        ${PUBLIC_INCLUDE}/Tags/GedcomTags.hpp

        ${PUBLIC_INCLUDE}/Views/ViewBase.hpp
        ${PUBLIC_INCLUDE}/Views/GedcomViews.hpp
        ${PUBLIC_INCLUDE}/Views/IndiView.hpp
        ${PUBLIC_INCLUDE}/Views/DateView.hpp
        ${PUBLIC_INCLUDE}/Views/BirthView.hpp
        ${PUBLIC_INCLUDE}/Views/PlaceView.hpp

    PRIVATE
        src/OpenGedcom.cpp
        src/Internal/StringArena.cpp
        src/Internal/RecordStorage.cpp

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

if (OPENGEDCOM_BUILD_TESTS)
    target_compile_definitions(OpenGedcom PRIVATE OPENGEDCOM_BUILD_TESTS)
    add_subdirectory(test)
endif()
