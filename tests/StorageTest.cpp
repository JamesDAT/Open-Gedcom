#include "StorageTest.h"
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

    }
}