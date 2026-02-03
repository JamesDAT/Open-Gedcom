#include "StorageTest.h"
#include "OpenGedcom/GedcomRegistry.h"
#include "Parser/GedcomParser.h"
#include <OpenGedcom/GedcomStorage.h>
#include <OpenGedcom/GedcomObject.h>
#include <cassert>
#include <iostream>

namespace OpenGedcom {
    void StorageTest::TestRegistry() {
        TagRegistry registry{};
        auto tag = registry.Create("INDI", "This Name");
        
    }

    void StorageTest::TestTagEmit() {
        
    }

    void StorageTest::TestParserEmit() {
        
    }
}