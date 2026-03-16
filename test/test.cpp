#include <OpenGedcom/OpenGedcom.hpp>
#include <chrono>
#include <thread>
#include "SimpleReader.hpp"

int main() {
    using namespace std::chrono_literals;

    std::string data = SimpleReader::ReadWholeFile("test/active-test/main.ged");
    //OpenGedcom::Document docCopy = OpenGedcom::Document::ParseCopy(data);
    //data.clear();
    OpenGedcom::Document doc = OpenGedcom::Document::ParseDOM(std::move(data));

    return 0;
}