#include <OpenGedcom/OpenGedcom.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include "OpenGedcom/Tags/Events.hpp"
#include "OpenGedcom/Views/BirthView.hpp"
#include "SimpleReader.hpp"

int main() {
    using namespace std::chrono_literals;

    std::string data = SimpleReader::ReadWholeFile("test/active-test/main.ged");
    //OpenGedcom::Document docCopy = OpenGedcom::Document::ParseCopy(data);
    //data.clear();
    OpenGedcom::Document doc = OpenGedcom::Document::ParseDOM(std::move(data));

    if(auto indi = doc.GetIndividual(5911)) {
        std::cout << "Sex: " << indi->Sex().value_or('U') << '\n';

        auto events = indi->Events();

        for(auto view : events) {
            if(doc.IsType<OpenGedcom::BirthTag>(view)) {
                OpenGedcom::BirthView birthView{&doc, view.Get()};

                if(auto date = birthView.GetDate()) {
                    std::cout << "Birth Date: " << date->Date() << '\n';
                    std::cout << "Birth Time: " << date->Time().value_or("Unknown Time") << '\n';
                }

                if(auto place = birthView.GetPlace()) {
                    std::cout << "Birth Place: " << place->Place() << '\n';
                }
            }
        }
    }

    return 0;
}