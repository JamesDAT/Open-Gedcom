#include "StorageTest.h"
#include "Parser/GedcomParser.h"
#include <OpenGedcom/GedcomStorage.h>
#include <OpenGedcom/GedcomObject.h>
#include <cassert>
#include <iostream>

namespace OpenGedcom {
    void StorageTest::TestRegistry() {
        TagRegistry registry{};
        TagType indi = registry.RegisterTag<IndiTag>("INDI");

        auto tag = registry.Create("INDI", "Test Name");

        assert(tag->Type() == indi);
        assert(tag->Value() == "Test Name");

        auto* indiTag = dynamic_cast<IndiTag*>(tag.get());
        assert(indiTag);
    }

    void StorageTest::TestTagEmit() {
        GedcomStorage storage{};
        TagType indi = storage.Registry().RegisterTag<IndiTag>("INDI");
        TagType occu = storage.Registry().RegisterTag<OccuTag>("OCCU");

        storage.Emit(0, std::nullopt, "INDI", "Person /NAME/");
        storage.Emit(0, std::nullopt, "OCCU", "Some Occupation");
        storage.Emit(0, std::nullopt, "INAVLID", "Invalid Tag");

        assert(storage.GetGraph()[0]->tag->Value() == "Person /NAME/");
        assert(storage.GetGraph()[1]->tag->Value() == "Some Occupation");
        assert(storage.GetGraph()[2]->tag->Value() == "Invalid Tag");

        assert(storage.GetGraph()[0]->tag->Type() == indi);
        assert(storage.GetGraph()[1]->tag->Type() == occu);
        assert(storage.GetGraph()[2]->tag->Type() == 0);
    }

    void StorageTest::TestParserEmit() {
        GedcomStorage storage{};
        GedcomParser parser{"tests/Samples/555SAMPLE.ged", storage};
        parser.Parse();

        std::cout << "Node Count: " << storage.GetGraph().size() << '\n';
    }
}