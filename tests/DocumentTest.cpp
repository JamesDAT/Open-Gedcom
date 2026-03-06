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
            std::cout << "Obtained View" << '\n';
        }

        //for(auto& record : graph) {
            //PrintChildren(record.get());
        //}
    }

    void DocumentTest::PrintChildren(const GedcomNode* tag) {
        std::cout << tag->Type() << ' ' << tag->RawValue() << '\n';
        for(auto& child : tag->GetChildren()) {
            PrintChildren(&child);
        }
    }
}