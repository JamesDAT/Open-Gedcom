#include "DocumentTest.h"
#include "OpenGedcom/OpenGedcom.h"
#include <iostream>

namespace OpenGedcom {
    void DocumentTest::TestDocument() {
        Document doc = Document::ParseFile("tests/Samples/555SAMPLE.ged");
        auto& storage = doc.Storage();
        auto& graph = storage.Graph();

        std::cout << "Graph Size: " << graph.size();
        
        if(auto individual = doc.Individual(1)) {
            std::cout << "Has Indi 1\n";
        }
        else {
            std::cout << "Not has Indi1\n";
        }
    }

    void DocumentTest::PrintChildren(GedcomTag* tag) {
        //std::cout << tag->RawValue() << '\n';
        for(auto& child : tag->Children()) {
            PrintChildren(child.get());
        }
    }
}