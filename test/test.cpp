#include <OpenGedcom/OpenGedcom.hpp>
#include "SimpleReader.hpp"

#include <iostream>

int main() {
    std::string data = SimpleReader::ReadWholeFile("test/samples/spec7Generated.ged");
    OpenGedcom::Document doc = OpenGedcom::Document::ParseDOM(std::move(data));

    std::cout << "Hello, World!" << std::endl;

    return 0;
}