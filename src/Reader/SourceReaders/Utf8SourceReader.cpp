// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Utf8SourceReader.h"
#include <cstring>
#include <fstream>

namespace OpenGedcom {
    UTF8SourceReader::UTF8SourceReader(std::ifstream& file, size_t startOffset) :
        m_file(file)
    {
        file.clear();
        file.seekg(startOffset, std::ios::beg);
    }

    UTF8SourceReader::~UTF8SourceReader() = default;

    std::optional<std::string> UTF8SourceReader::ReadLine() {
        while (true) {
            // 1. Return a line if we have a complete one
            auto pos = m_pending.find('\n');
            if (pos != std::string::npos) {
                std::string line = m_pending.substr(0, pos);
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                m_pending.erase(0, pos + 1);
                return line;
            }

            // 2. Check EOF
            if (m_file.eof() || !m_file.good()) {
                if (!m_pending.empty()) {
                    std::string line = std::move(m_pending);
                    m_pending.clear();
                    return line;
                }
                return std::nullopt;
            }

            // 3. Read next chunk
            size_t carrySize = m_carry.size();
            if (carrySize > 0) {
                std::memmove(m_buffer.data(), m_carry.data(), carrySize);
            }

            m_file.read(reinterpret_cast<char*>(m_buffer.data() + carrySize), BUFFER_SIZE - carrySize);
            size_t bytesRead = m_file.gcount();
            size_t total = carrySize + bytesRead;
            if (total == 0) return std::nullopt; // nothing more to read

            // 4. Handle UTF-8 incomplete tail
            size_t incomplete = Utf8IncompleteTail(m_buffer.data(), total);
            size_t validSize = total - incomplete;

            // 5. Append valid bytes to pending
            m_pending.append(reinterpret_cast<char*>(m_buffer.data()), validSize);

            // 6. Save incomplete bytes for next read
            if (incomplete > 0) {
                m_carry.assign(reinterpret_cast<char*>(m_buffer.data() + validSize), incomplete);
            } else {
                m_carry.clear();
            }
        }
    }

    size_t UTF8SourceReader::Utf8IncompleteTail(const uint8_t* data, size_t size) {
        if (size == 0) return 0;

        size_t i = size - 1;
        int continuation = 0;

        while (i > 0 && (data[i] & 0b11000000) == 0b10000000) {
            --i;
            ++continuation;
        }

        uint8_t lead = data[i];
        int expected =
            (lead & 0b10000000) == 0 ? 0 :
            (lead & 0b11100000) == 0b11000000 ? 1 :
            (lead & 0b11110000) == 0b11100000 ? 2 :
            (lead & 0b11111000) == 0b11110000 ? 3 :
            -1;

        if (expected == -1 || continuation < expected)
            return continuation + 1;

        return 0;
    }
}