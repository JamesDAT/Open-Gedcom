// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <filesystem>
#include <future>
#include <string>
#include <memory>
#include <optional>

#include "SourceReaders/ISourceReader.h"
#include "LineRingBuffer.h"

#include "Tests.h"

namespace OpenGedcom {

#ifdef OPENGEDCOM_BUILD_TESTS
    class ReaderTest;
#endif

    enum class TextEncoding {
        Utf8,
        Utf16LE,
        Utf16BE
    };

    struct EncodingInfo {
        TextEncoding encoding;
        size_t bomSize;
    };

    class GedcomReader {
    public:
        GedcomReader();
        ~GedcomReader();

        /// @brief Reads the Gedcom file asynchronously, populates the line buffer as it reads
        /// @param path
        std::future<void> ReadFile(const std::filesystem::path& path);

        /// @brief Returns the next line in the buffer. This function is thread safe and will block until a line is available
        /// @returns string or std::nullopt if eof and no more lines
        std::optional<std::string> GetNextLine();


    private:
        EncodingInfo DetectEncoding(std::ifstream& file);
        
        LineRingBuffer m_ringBuffer{};

        std::unique_ptr<ISourceReader> m_sourceReader;

        void ReadFileInternal(const std::filesystem::path& path);
        void PushLine(std::string line); // used for debug

        OPENGEDCOM_TEST_FRIEND(ReaderTest)
    };
}