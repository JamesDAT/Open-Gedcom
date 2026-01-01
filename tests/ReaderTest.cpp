#include "ReaderTest.h"
#include <cassert>
#include <iostream>

namespace OpenGedcom {
    void ReaderTest::TestReaderRingBuffer() {
        const std::string text1 = "Test Line 1";
        const std::string text2 = "Test Line 2";
        
        GedcomReader reader{};
        
        std::string lineIn = text1;
        uint64_t lineNo = 0;
        reader.PushLine(std::move(lineIn));

        lineIn = text2;
        lineNo = 1;
        reader.PushLine(std::move(lineIn));

        auto outLine = reader.GetNextLine();
        assert(outLine == text1);

        outLine = reader.GetNextLine();
        assert(outLine == text2);
    }

    void ReaderTest::TestLineReading() {
        GedcomReader reader{};
        reader.ReadFile("Samples/555SAMPLE.ged");

        auto line = reader.GetNextLine();
        while(line != std::nullopt) {
            std::cout << line.value() << '\n';
            line = reader.GetNextLine();
        }
    }
}