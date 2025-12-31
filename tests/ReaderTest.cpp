#include "ReaderTest.h"
#include <cassert>
#include <iostream>

namespace OpenGedcom {
    void ReaderTest::TestReaderRingBuffer() {
        const std::string text1 = "Test Line 1";
        const std::string text2 = "Test Line 2";
        const std::string text3 = "Test Line 3";
        const std::string text4 = "Test Line 4";

        
        GedcomReader reader{};
        
        std::string lineIn = text1;
        uint64_t lineNo = 0;
        reader.PushLine(std::move(lineIn), lineNo);

        lineIn = text2;
        lineNo = 1;
        reader.PushLine(std::move(lineIn), lineNo);

        lineIn = text3;
        lineNo = 2;
        reader.PushLine(std::move(lineIn), lineNo);

        lineIn = text4;
        lineNo = 3;
        reader.PushLine(std::move(lineIn), lineNo);

        auto outLine = reader.GetNextLine();
        assert(outLine == text1);

        outLine = reader.GetNextLine();
        assert(outLine == text2);

        outLine = reader.GetNextLine();
        assert(outLine == text3);

        outLine = reader.GetNextLine();
        assert(outLine == text4);
    }
}