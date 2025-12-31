add_executable(OpenGedcomTests
    test.cpp
)

target_link_libraries(OpenGedcomTests
    PRIVATE OpenGedcom::OpenGedcom
)
