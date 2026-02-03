// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <filesystem>
#include <fstream>
#include <future>
#include <string>
#include <memory>
#include <optional>

#include "SourceReaders/ISourceReader.h"
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
        GedcomReader(const std::filesystem::path& path);
        ~GedcomReader();

        std::optional<std::string> ReadLine();

    private:
        EncodingInfo DetectEncoding();
        
        const std::filesystem::path m_path;
        std::ifstream m_stream;

        std::unique_ptr<ISourceReader> m_sourceReader;

        OPENGEDCOM_TEST_FRIEND(ReaderTest)
    };
}