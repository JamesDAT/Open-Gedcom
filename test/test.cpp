#include <OpenGedcom/OpenGedcom.hpp>
#include <iostream>
#include "OpenGedcom/Tags/Events.hpp"
#include "OpenGedcom/Tags/Records.hpp"
#include "OpenGedcom/Views/BirthView.hpp"
#include "OpenGedcom/Views/IndiView.hpp"
#include "SimpleReader.hpp"

int main() {
    std::string data = SimpleReader::ReadWholeFile("active-test/main.ged");
    OpenGedcom::Document doc = OpenGedcom::Document::Parse(data);
    data.clear();

    

    std::cin.ignore();

    return 0;
}