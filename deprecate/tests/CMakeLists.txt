add_executable(OpenGedcomTests
    Test_main.cpp
    ReaderTest.cpp
    StorageTest.cpp
    DocumentTest.cpp
)

target_link_libraries(OpenGedcomTests
    PRIVATE OpenGedcom::OpenGedcom
)

target_include_directories(OpenGedcomTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/tests
)

target_compile_definitions(OpenGedcomTests
    PRIVATE OPENGEDCOM_BUILD_TESTS
)

target_compile_features(OpenGedcomTests PRIVATE cxx_std_20)
