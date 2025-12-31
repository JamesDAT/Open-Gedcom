#include <iostream>
#include "ReaderTest.h"

int main() {
    std::cout << "Running Tests...\n";
    OpenGedcom::ReaderTest::TestReaderRingBuffer();
    std::cout << "[1] ReaderTest Passed\n";
    
}