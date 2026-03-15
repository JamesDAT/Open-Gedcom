#include <OpenGedcom/OpenGedcom.hpp>
#include "SimpleReader.hpp"

int main() {
    std::string data = SimpleReader::ReadWholeFile("test/samples/spec7Generated.ged");
    OpenGedcom::Document doc = OpenGedcom::Document::ParseDOM(std::move(data));

    return 0;
}