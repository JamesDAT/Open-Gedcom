add_executable(OpenGedcomTests
    test.cpp
    SimpleReader.hpp
)

target_link_libraries(OpenGedcomTests
    PRIVATE OpenGedcom::OpenGedcom
)

target_include_directories(OpenGedcomTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/test
)

target_compile_definitions(OpenGedcomTests
    PRIVATE OPENGEDCOM_BUILD_TESTS
)

target_compile_features(OpenGedcomTests PRIVATE cxx_std_20)