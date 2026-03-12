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
#include <string_view>
#include <vector>

namespace OpenGedcom::Internal {
    class Parser {
    public:
        Parser();
        ~Parser();

        void Parse(const std::string_view data);

    private:
        std::vector<std::size_t> m_lineInfo{};
        std::size_t m_recordCount = 0;

        void ParseLine(const std::string_view data);

        inline std::size_t EstimateLineCount(std::size_t bytes) const {
            return bytes / 32 + 8; // rough estimate of 32 bytes per line on average
        }
    };
}