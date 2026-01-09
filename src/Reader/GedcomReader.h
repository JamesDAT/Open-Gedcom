// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <condition_variable>
#include <filesystem>
#include <future>
#include <queue>
#include <semaphore>
#include <string_view>
#include <string>
#include <atomic>
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
        GedcomReader();
        ~GedcomReader();

        /// @brief Reads the Gedcom file asynchronously, populates the line buffer as it reads
        /// @param path
        std::future<void> ReadFile(const std::filesystem::path& path);

        /// @brief Returns the next line in the buffer. This function is thread safe and will block until a line is available
        /// @returns string or std::nullopt if eof and no more lines
        std::optional<std::string> GetNextLine();


    private:
        void PushLine(std::string&& text);
        EncodingInfo DetectEncoding(std::ifstream& file);
        
        std::queue<std::string> m_lineQueue;
        std::mutex m_mutex;
        std::condition_variable m_notEmpty;
        std::condition_variable m_notFull;
        size_t m_maxQueueSize = 1024;

        bool m_eof = false;

        std::unique_ptr<ISourceReader> m_sourceReader;


        OPENGEDCOM_TEST_FRIEND(ReaderTest)
    };
}