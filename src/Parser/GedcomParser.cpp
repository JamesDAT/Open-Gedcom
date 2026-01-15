// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomParser.h"

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
        std::string_view xref;
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
            auto xrefBegin = it;
            ++it;
            while (it != end && *it != ' ') {
                ++it;
            }
            xref = std::string_view(&*xrefBegin, std::distance(xrefBegin, it));

            if(it != end && *it == ' ') {
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

        m_storage.Emit(level, xref, tag, value);
    }

    GedcomParser::~GedcomParser() = default;
}