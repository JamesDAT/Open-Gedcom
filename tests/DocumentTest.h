#pragma once

#include "OpenGedcom/GedcomObject.h"
namespace OpenGedcom {
    class DocumentTest {
    public:

    static void TestDocument();

    private:
        static void PrintChildren(GedcomTag* tag);
    };
}