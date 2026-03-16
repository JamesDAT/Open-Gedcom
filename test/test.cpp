#include <OpenGedcom/OpenGedcom.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include "SimpleReader.hpp"

int main() {
    using namespace std::chrono_literals;

    std::string data = SimpleReader::ReadWholeFile("test/active-test/main.ged");
    //OpenGedcom::Document docCopy = OpenGedcom::Document::ParseCopy(data);
    //data.clear();
    OpenGedcom::Document doc = OpenGedcom::Document::ParseDOM(std::move(data));

    if(auto view = doc.GetIndividual(5911)) {
        std::cout << "Got Indi: " << view->Name().value_or("Not Found") << '\n';
        std::cout << "Got FirstName: " << view->FirstName().value_or("Not Found") << '\n';
        std::cout << "Got LastName: " << view->LastName().value_or("Not Found") << '\n';
        std::cout << "Got Given: " << view->GivenName().value_or("Not Found") << '\n';
    }
    else {
        std::cout << "Indi Not Found" << '\n';
    }

    return 0;
}