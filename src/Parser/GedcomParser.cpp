// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomParser.h"
#include <optional>

namespace OpenGedcom {
    GedcomParser::GedcomParser(const std::filesystem::path& path, GedcomStorage& storage) :
        m_path(path), m_storage(storage)
    {
        
    }

    void GedcomParser::Parse() {
        auto future = m_reader.ReadFile(m_path);
        future.wait();
        
        auto line = m_reader.GetNextLine();


        while (line != std::nullopt) {
            ParseGedcomLine(line.value());


            line = m_reader.GetNextLine();
        }
    }

    void GedcomParser::ParseGedcomLine(std::string_view line) {
        int level = 0;
        std::optional<uint32_t> xrefId;
        std::string_view tag;
        std::string_view value;

        auto it = line.begin();
        auto end = line.end();

        // parse the level
        while (it != end && *it >= '0' && *it <= '9') {
            level = level * 10 + (*it - '0');
            ++it;
        }

        // jump space
        if (it != end && *it == ' ') {
            ++it;
        }

        // xref
        if (it != end && *it == '@') {
        ++it; // skip the initial '@'
        auto idBegin = it;

        // advance until the closing '@' or end
        while (it != end && *it != '@') {
            ++it;
        }

        // convert the digits between idBegin and it to an integer
        if (it != idBegin) {
            xrefId = 0;
            for (auto iter = idBegin; iter != it; ++iter) {
                if (*iter >= '0' && *iter <= '9') {
                    xrefId = xrefId.value() * 10 + (*iter - '0');
                } else {
                    // invalid character, emit error for now
                    throw std::runtime_error("Invalid Character in xref");
                }
            }
        }

        if (it != end && *it == '@') {
            ++it; // skip the closing '@'
        }

        // skip any space after the xref
        if (it != end && *it == ' ') {
            ++it;
        }
    }

        // Tag
        auto tagBegin = it;
        while (it != end && *it != ' ') {
            ++it;
        }
        tag = std::string_view(&*tagBegin, std::distance(tagBegin, it));

        // value
        if (it != end && *it == ' ') {
            ++it;
        }

        if(it != end) {
            value = std::string_view(&*it, std::distance(it, end));
        }

        m_storage.Emit(level, xrefId, tag, value);
    }

    GedcomParser::~GedcomParser() = default;
}