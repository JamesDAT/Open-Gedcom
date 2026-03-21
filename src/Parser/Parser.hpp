// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file Parser.hpp
 * @brief OpenGedcom string and chunk parser
 *
 *
 * The gedcom parser is primarily a line parser, as Gedcom is deliminated by new lines.
 * The parser has two read modes, a string read mode, which it scans for line placements,
 * then parses each line with the indices. Or a chunk mode which takes in chunks of Gedcom
 * data, and generates the indices on the fly for the line parser.
 */

#pragma once

// std
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string_view>
#include <vector>

namespace OpenGedcom::Internal {
    struct TagInfo {
        uint32_t level;
        std::string_view xref;
        std::string_view tag;
        std::string_view value;
    };

    struct DocumentInfo {
        size_t recordCount;
        size_t storageSizeEstimate;
    };

    class Parser {
    public:
        Parser();
        ~Parser();

        void Parse(const std::string_view data);

        void BindDocumentBegin(const std::function<void(DocumentInfo)>& func) {
            m_documentBegin = func;
        }

        void BindDocumentEnd(const std::function<void()>& func) {
            m_documentEnd = func;
        }

        void BindTagBegin(const std::function<void(TagInfo)>& func) {
            m_onTagBegin = func;
        }

        void BindTagEnd(const std::function<void(uint32_t level)>& func) {
            m_onTagEnd = func;
        }

    private:
        void ParseLine(const std::string_view data);

        inline size_t EstimateLineCount(size_t bytes) const {
            return bytes / 32 + 8; // rough estimate of 32 bytes per line on average
        }

        inline size_t EstimateStorageSize(size_t dataSize) const {
            return dataSize / 2; // gedcom files are roughly 50% useful data
        }

        std::vector<uint32_t> m_lineInfo{};

        uint32_t m_currentTagLevel = 0;

        std::function<void(DocumentInfo)> m_documentBegin; // handler after the parser has scanned the document, before parsing
        std::function<void()> m_documentEnd;
        std::function<void(TagInfo)> m_onTagBegin; // beginning of a tag structure
        std::function<void(uint32_t level)> m_onTagEnd; 
    };
}