// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Parser.hpp"
#include <cctype>
#include <iostream>

namespace OpenGedcom::Internal {
    Parser::Parser(Storage* storage, Registry* registry, bool makeCopies)
        :   m_storage(storage),
        m_registry(registry),
        m_makeCopies(makeCopies)
    {

    }

    Parser::~Parser() {

    }

    void Parser::Parse(const std::string_view data) {
        m_lineInfo.reserve(EstimateLineCount(data.size()));

        for(size_t i = 0; i < data.size(); ++i) {
            if(data[i] == '\n') {
                m_lineInfo.push_back(i); // downsize to uint32_t
                if(i + 1 < data.size() && data[i+1] == '0') {
                    ++m_recordCount;
                }
            }
        }

        m_storage->ReserveRecords(m_recordCount);
        if(m_makeCopies) {
            m_storage->ReserveStringArena(EstimateStorageSize(data.size()));
        }

        // parse lines
        size_t lineStart = 0;

        for(size_t end : m_lineInfo) {
            ParseLine(std::string_view(data.data() + lineStart, 
                                            end - lineStart));

            lineStart = end + 1;
        }

        // handle final line
        if(lineStart < data.size()) {
            ParseLine(std::string_view(data.data() + lineStart,
                                            data.size() - lineStart));
        }
    }

    void Parser::ParseLine(const std::string_view line) {
        uint32_t level = 0;
        uint32_t xref = UINT32_MAX;
        std::string_view tag;
        uint32_t id = UINT32_MAX;
        std::string_view value;

        auto it = line.begin();
        auto end = line.end();

        // level char
        if(it < end && std::isdigit(*it)) {
            level = *it - '0'; // convert char to int
            ++it;
        }

        // blank
        if(it < end && std::isblank(*it)) {
            ++it;
        }

        // xref @I123@ as an example
        if(it < end && *it == '@') {
            ++it; // skip the initial '@'
            auto idBegin = it;

            // advance until the closing '@' or end
            while (it != end && *it != '@') {
                ++it;
            }

            // convert the digits between idBegin and it to an integer
            if (it != idBegin) {
                xref = 0;
                for (auto iter = idBegin; iter != it; ++iter) {
                    if (std::isdigit(*iter)) {
                        xref = xref * 10 + (*iter - '0'); // char to int, moving the existing digits up by 1 place each time
                    }
                }
            }

            if (it != end && *it == '@') {
                ++it; // skip the closing '@'
            }
        }

        // blank
        if(it < end && std::isblank(*it)) {
            ++it;
        }

        // tag
        auto tagBegin = it;
        while (it != end && *it != ' ') {
            ++it;
        }
        tag = std::string_view(tagBegin, std::distance(tagBegin, it));
        
        // blank
        if(it < end && std::isblank(*it)) {
            ++it;
        }

        // value
        if(it != end) {
            value = std::string_view(&*it, std::distance(it, end));
        }

        std::cout << level << ' ';
        std::cout << (xref != UINT32_MAX ? xref : 0) << ' ';
        std::cout << tag << ' ';
        std::cout << value << '\n';
    }
}