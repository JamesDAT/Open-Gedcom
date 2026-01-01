#include <iostream>
#include "ReaderTest.h"

int main() {
    std::cout << "Running Tests...\n";
    OpenGedcom::ReaderTest::TestReaderRingBuffer();
    std::cout << "[1] TestReaderRingBuffer Passed\n";

    OpenGedcom::ReaderTest::TestLineReading();
    std::cout << "[2] TestLineReading Passed\n";
    
}