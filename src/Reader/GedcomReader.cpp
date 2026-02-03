// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomReader.h"
#include "Reader/SourceReaders/Utf8SourceReader.h"
#include <stdexcept>

namespace OpenGedcom {
    GedcomReader::GedcomReader(const std::filesystem::path& path)
        : m_path(path), m_stream(path, std::ios::binary)
    {
        auto encoding = DetectEncoding();

        switch(encoding.encoding) {
            case TextEncoding::Utf8:
                m_sourceReader = std::make_unique<UTF8SourceReader>(m_stream, encoding.bomSize);
            break;

            case TextEncoding::Utf16LE:
                throw std::runtime_error("Utf16LE is not supported yet!");
            break;

            case TextEncoding::Utf16BE:
                throw std::runtime_error("Utf16BE is not supported yet!");
            break;
        }
    }

    GedcomReader::~GedcomReader() {

    }

    std::optional<std::string> GedcomReader::ReadLine() {
        return m_sourceReader->ReadLine();
    }

    EncodingInfo GedcomReader::DetectEncoding() {
        uint8_t bom[3] = {0};

        m_stream.read(reinterpret_cast<char*>(bom), 3);
        size_t n = m_stream.gcount();

        m_stream.clear();           // clear EOF flags
        m_stream.seekg(0);          // rewind

        if (n >= 3 &&
            bom[0] == 0xEF &&
            bom[1] == 0xBB &&
            bom[2] == 0xBF) {
            return { TextEncoding::Utf8, 3 };
        }

        if (n >= 2 &&
            bom[0] == 0xFF &&
            bom[1] == 0xFE) {
            return { TextEncoding::Utf16LE, 2 };
        }

        if (n >= 2 &&
            bom[0] == 0xFE &&
            bom[1] == 0xFF) {
            return { TextEncoding::Utf16BE, 2 };
        }

        // no BOM
        return { TextEncoding::Utf8, 0 };
    }
}