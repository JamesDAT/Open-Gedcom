// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <filesystem>
#include <future>
#include <semaphore>
#include <string_view>
#include <string>
#include <atomic>

#include "Utility/LineRingBuffer.h"
#include "Tests.h"

namespace OpenGedcom {

#ifdef OPENGEDCOM_BUILD_TESTS
    class ReaderTest;
#endif

    class GedcomReader {
    public:
        GedcomReader();
        ~GedcomReader();

        /// @brief Reads the Gedcom file asynchronously, populates the line buffer as it reads
        /// @param path
        std::future<void> ReadFile(const std::filesystem::path& path);

        /// @brief Returns the next line in the buffer. This function is thread safe and will block until a line is available (or eof)
        /// NOTE: The last line becomes invalid when GetNextLine is called again, only ever consume one line at a time.
        std::string_view GetNextLine();

        bool IsEndOfFile() const;


    private:
        LineRingBuffer m_buffer{1024};
        std::atomic<bool> m_eof{false};

        std::counting_semaphore<> m_ready{0};
        std::counting_semaphore<> m_free{1024};

        void PushLine(std::string&& text, uint64_t lineNo);


        OPENGEDCOM_TEST_FRIEND(ReaderTest)
    };
}