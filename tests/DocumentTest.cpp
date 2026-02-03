#include "DocumentTest.h"
#include "OpenGedcom/OpenGedcom.h"
#include <iostream>
#include <chrono>

namespace OpenGedcom {
    void DocumentTest::TestDocument() {
        auto start = std::chrono::steady_clock::now();

        Document doc = Document::ParseFile("tests/Samples/large_test.ged");
        auto& storage = doc.Storage();
        auto& graph = storage.Graph();

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Graph Size: " << graph.size() << '\n';
        std::cout << "Elapsed: " << duration.count() << " milliseconds\n";

        //for(auto& record : graph) {
            //PrintChildren(record.get());
        //}
    }

    void DocumentTest::PrintChildren(GedcomTag* tag) {
        std::cout << tag->Type() << ' ' << tag->RawValue() << '\n';
        for(auto& child : tag->Children()) {
            PrintChildren(child.get());
        }
    }
}