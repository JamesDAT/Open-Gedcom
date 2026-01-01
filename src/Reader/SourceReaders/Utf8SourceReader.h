// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include "ISourceReader.h"
#include <fstream>
#include <vector>
#include <cstdint>

namespace OpenGedcom {
    class UTF8SourceReader : public ISourceReader {
    public:
        explicit UTF8SourceReader(std::ifstream& file, size_t startOffset);
        ~UTF8SourceReader();
        
        bool ReadChunk(std::string& out) override;

    private:
        std::ifstream& m_file;
        bool m_bomChecked = false;

        std::vector<uint8_t> m_buffer;
        std::vector<uint8_t> m_carry;

        inline size_t Utf8SequenceLength(uint8_t lead);
        inline size_t Utf8IncompleteTail(const uint8_t* data, size_t size);
    };
}