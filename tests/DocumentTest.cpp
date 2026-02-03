#include "DocumentTest.h"
#include "OpenGedcom/OpenGedcom.h"
#include <iostream>

namespace OpenGedcom {
    void DocumentTest::TestDocument() {
        Document doc = Document::ParseFile("tests/Samples/spec7Generated.ged");
        auto& storage = doc.Storage();
        auto& graph = storage.Graph();

        std::cout << "Graph Size: " << graph.size() << '\n';

        for(auto& record : graph) {
            PrintChildren(record.get());
        }
    }

    void DocumentTest::PrintChildren(GedcomTag* tag) {
        std::cout << tag->Type() << ' ' << tag->RawValue() << '\n';
        for(auto& child : tag->Children()) {
            PrintChildren(child.get());
        }
    }
}