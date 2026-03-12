// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Parser.hpp"

namespace OpenGedcom::Internal {
    Parser::Parser() {

    }

    Parser::~Parser() {

    }

    void Parser::Parse(const std::string_view data) {
        m_lineInfo.reserve(EstimateLineCount(data.size()));

        for(std::size_t i = 0; i < data.size(); ++i) {
            if(data[i] == '\n') {
                m_lineInfo.push_back(i);
                if(i + 1 < data.size() && data[i+1] == '0') {
                    ++m_recordCount;
                }
            }
        }

        // parse lines
        std::size_t lineStart = 0;

        for(std::size_t end : m_lineInfo) {
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
        
    }
}