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
        // sample file reading
        GedcomReader sampleReader{};
        sampleReader.ReadFile("Samples/555SAMPLE.ged");

        auto sampleLine = sampleReader.GetNextLine();

        assert(sampleLine != std::nullopt);

        while(sampleLine != std::nullopt) {
            //std::cout << sampleLine.value() << '\n';
            sampleLine = sampleReader.GetNextLine();
        }

        // empty file reading
        GedcomReader emptyReader{};
        emptyReader.ReadFile("Samples/empty.ged");

        auto emptyLine = emptyReader.GetNextLine();
        assert(emptyLine == std::nullopt);

        // stress testing
        GedcomReader stressReader{};
        stressReader.ReadFile("Samples/large_test.ged");

        std::cout << "Read file" << '\n';

        size_t lineCount = 0;
        auto stressLine = stressReader.GetNextLine();
        while(stressLine != std::nullopt) {
            std::cout << stressLine.value() << '\n';
            ++lineCount;
            stressLine = stressReader.GetNextLine();
        }

        std::cout << "Stress test found {" << lineCount << "} lines\n";
    }
}