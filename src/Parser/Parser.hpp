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
#include "OpenGedcom/Internal/Storage.hpp"
#include "OpenGedcom/Internal/Registry.hpp"

// std
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace OpenGedcom::Internal {
    class Parser {
    public:
        Parser(Storage* storage, Registry* registry, bool makeCopies);
        ~Parser();

        void Parse(const std::string_view data);

    private:
        void ParseLine(const std::string_view data);

        inline size_t EstimateLineCount(size_t bytes) const {
            return bytes / 32 + 8; // rough estimate of 32 bytes per line on average
        }

        inline size_t EstimateStorageSize(size_t dataSize) const {
            return dataSize / 2; // gedcom files are roughly 50% useful data
        }


        Storage* m_storage;
        Registry* m_registry;

        const bool m_makeCopies;

        std::vector<uint32_t> m_lineInfo{};
        size_t m_recordCount = 0; // used to reserve record storage

    };
}