// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include "ISourceReader.h"
#include <fstream>
#include <array>
#include <cstdint>

namespace OpenGedcom {
    class UTF8SourceReader : public ISourceReader {
    public:
        explicit UTF8SourceReader(std::ifstream& file, size_t startOffset = 0);
        ~UTF8SourceReader();
        
        std::optional<std::string> ReadLine() override;

    private:
        std::ifstream& m_file;

        static constexpr size_t BUFFER_SIZE = 4096;
        std::array<uint8_t, BUFFER_SIZE> m_buffer{};

        std::string m_pending;
        std::string m_carry;

        inline size_t Utf8IncompleteTail(const uint8_t* data, size_t size);
    };
}