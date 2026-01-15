// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Utf8SourceReader.h"
#include <cstring>
#include <fstream>

namespace OpenGedcom {
    UTF8SourceReader::UTF8SourceReader(std::ifstream& file, size_t startOffset) :
        m_file(file), m_buffer(CHUNK_SIZE), m_carry()
    {
        file.clear();
        file.seekg(startOffset, std::ios::beg);
    }

    UTF8SourceReader::~UTF8SourceReader() = default;

    bool UTF8SourceReader::ReadChunk(std::string& out) {

        if(!m_file.good() && m_carry.empty()) {
            return false;
        }

        size_t offset = m_carry.size();
        if(offset > 0) {
            std::memcpy(m_buffer.data(), m_carry.data(), offset);
            m_carry.clear();
        }

        m_file.read(reinterpret_cast<char*>(m_buffer.data() + offset), CHUNK_SIZE - offset);

        size_t bytesRead = m_file.gcount();
        size_t total = offset + bytesRead;

        if(total == 0) {
            return false;
        }

        const uint8_t* data = m_buffer.data();

        // handle BOM
        size_t start = 0;
        if(!m_bomChecked) {
            m_bomChecked = true;
            if (total >= 3 &&
                data[0] == 0xEF &&
                data[1] == 0xBB &&
                data[2] == 0xBF) {
                start = 3;
            }
        }

        // handle incomplete utf8 at the end of the buffer
        size_t incomplete = Utf8IncompleteTail(data + start, total - start);
        size_t validSize = total - start - incomplete;

        // append valid utf8
        out.append(reinterpret_cast<const char*>(data + start), validSize);

        // save incomplete bytes
        if(incomplete > 0) {
            m_carry.assign(
                data + start + validSize,
                data + start + validSize + incomplete
            );
        }

        return true;
    }

    size_t UTF8SourceReader::Utf8SequenceLength(uint8_t lead) {
        if ((lead & 0b10000000) == 0) return 1;
        if ((lead & 0b11100000) == 0b11000000) return 2;
        if ((lead & 0b11110000) == 0b11100000) return 3;
        if ((lead & 0b11111000) == 0b11110000) return 4;
        return 0; // invalid
    }

    size_t UTF8SourceReader::Utf8IncompleteTail(const uint8_t* data, size_t size) {
        size_t maxCheck = size < 4 ? size : 4;

        for (size_t i = 1; i <= maxCheck; ++i) {
            uint8_t lead = data[size - i];
            size_t seqLen = Utf8SequenceLength(lead);
            if (seqLen == 0) continue;

            if (i < seqLen) {
                return i;
            }
            return 0;
        }
        return 0;
    }
}