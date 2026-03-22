#include <OpenGedcom/OpenGedcom.hpp>
#include <iostream>
#include "OpenGedcom/Tags/Events.hpp"
#include "OpenGedcom/Tags/Records.hpp"
#include "OpenGedcom/Views/BirthView.hpp"
#include "OpenGedcom/Views/IndiView.hpp"
#include "SimpleReader.hpp"

int main() {
    std::string data = SimpleReader::ReadWholeFile("active-test/output.ged");
    OpenGedcom::Document doc = OpenGedcom::Document::Parse(data);
    data.clear();

    if(auto indi = doc.GetIndividual(5911)) {
        std::cout << "Found Indi" << '\n';
        std::cout << "Name: " << indi.value().Get()->GetChildren()[0]->GetData() << '\n';
    }

    std::string gedcomString = doc.GetGedcomString();
    SimpleReader::WriteStringToFile("active-test/output.ged", gedcomString);

    std::cin.ignore();

    return 0;
}