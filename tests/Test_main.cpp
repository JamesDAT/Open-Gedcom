#include <iostream>
#include "ReaderTest.h"
#include "StorageTest.h"

int main() {
    int count = 1;

    std::cout << "Running Tests...\n";
    OpenGedcom::ReaderTest::TestReaderRingBuffer();
    std::cout << count << " TestReaderRingBuffer Passed\n";
    count++;

    OpenGedcom::ReaderTest::TestLineReading();
    std::cout << count << " TestLineReading Passed\n";
    count++;
    
    OpenGedcom::StorageTest::TestRegistry();
    std::cout << count << " TestRegistry Passed\n";
    count++;

    OpenGedcom::StorageTest::TestTagEmit();
    std::cout << count << " TestTagEmit Passed\n";
    count++;
}