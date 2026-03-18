#include <OpenGedcom/OpenGedcom.hpp>
#include <iostream>
#include "OpenGedcom/Tags/Events.hpp"
#include "OpenGedcom/Tags/Records.hpp"
#include "OpenGedcom/Views/BirthView.hpp"
#include "OpenGedcom/Views/IndiView.hpp"
#include "SimpleReader.hpp"

int main() {
    std::string data = SimpleReader::ReadWholeFile("test/active-test/main.ged");
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

                std::cout << "Birth Place: " << birthView.GetLocation().value_or("Unknown Location") << '\n';
                
            }
        }
    }

    auto newIndividual = OpenGedcom::IndiView{&doc, doc.CreateTag<OpenGedcom::IndiTag>().Get()};
    newIndividual.SetId(10);
    newIndividual.SetName("Test", "Name");
    newIndividual.SetGivenName("Test Given");
    newIndividual.SetSex('M');

    if(auto name = newIndividual.Name()) {
        std::cout << "Pushed Name: " << name.value() << '\n';
    }
    if(auto given = newIndividual.GivenName()) {
        std::cout << "Pushed Given: " << given.value() << '\n';
    }
    if(auto sex = newIndividual.Sex()) {
        std::cout << "Pushed Sex: " << sex.value() << '\n';
    }

    return 0;
}