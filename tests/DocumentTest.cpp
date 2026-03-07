#include "DocumentTest.h"
#include "OpenGedcom/OpenGedcom.h"
#include <iostream>
#include <chrono>

namespace OpenGedcom {
    void DocumentTest::TestDocument() {
        auto start = std::chrono::steady_clock::now();

        Document doc = Document::ParseFile("tests/Samples/spec7Generated.ged");
        auto& storage = doc.Storage();
        auto& graph = storage.Graph();

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Graph Size: " << graph.size() << '\n';
        std::cout << "Elapsed: " << duration.count() << " milliseconds\n";

        if(auto view = doc.Individual(1)) {
            std::cout << "Obtained Indi View" << '\n';
            std::cout << "Indi Given Name: " << view->Given().value() << '\n';
            std::cout << "Indi Surname: " << view->Surname().value() << '\n';
            std::cout << "Resi Count: " << view->Residence().size() << '\n';
            std::cout << "Occu Count: " << view->Occupations().size() << '\n';
        }

        
    }

    void DocumentTest::PrintChildren(const GedcomNode* tag) {
        std::cout << tag->Type() << ' ' << tag->RawValue() << '\n';
        for(auto& child : tag->GetChildren()) {
            PrintChildren(&child);
        }
    }
}