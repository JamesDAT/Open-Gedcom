// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Parser.hpp"
#include <cctype>
#include <iostream>

namespace OpenGedcom::Internal {
    Parser::Parser() {

    }

    Parser::~Parser() {

    }

    void Parser::Parse(std::string_view data) {
        if(data.empty()) {
            std::cerr << "[OpenGedcom] Provided Data Was Empty";
            return;
        }

        // if file doesn't begin with 0 HEAD then it has a BOM
        if(data[0] != '0') {
            auto offset = data.find_first_of('0');
            data = std::string_view(data.begin() + offset, data.size() - offset);
        }

        m_lineInfo.reserve(EstimateLineCount(data.size()));
        size_t recordCount = 0;

        for(size_t i = 0; i < data.size(); ++i) {
            if(data[i] == '\n') {
                m_lineInfo.push_back(i); // downsize to uint32_t
                if(i + 1 < data.size() && data[i+1] == '0') {
                    ++recordCount;
                }
            }
        }

        m_documentBegin({
            .recordCount = recordCount, 
            .storageSizeEstimate = EstimateStorageSize(data.size())});

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

        m_documentEnd();
    }

    void Parser::ParseLine(const std::string_view line) {
        uint32_t level = 0;
        std::string_view xref;
        std::string_view tag;
        std::string_view value;

        auto it = line.begin();
        auto end = line.end();

        // level char
        if(it < end && std::isdigit(*it)) {
            level = *it - '0'; // convert char to int
            ++it;
        }
        else {
            // blank line, or just invalid, they must start with a level number
            std::cerr << "[OpenGedcom] Invalid Line Detected. Lines Must Begin With a Number\n";
            std::cerr << "\tLine: " << line << '\n' << std::endl;
            return;
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

            xref = std::string_view(idBegin, std::distance(idBegin, it));

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
        while (it != end && !std::isspace(*it)) {
            ++it;
        }
        tag = std::string_view(tagBegin, std::distance(tagBegin, it));
        
        // blank
        if(it < end && std::isblank(*it)) {
            ++it;
        }

        // value
        if(it != end) {
            value = std::string_view(&*it, std::distance(it, end - 1)); // remove newline character from end
        }

        if(level > m_currentTagLevel + 1) { // tag jumped
            std::cerr << "[OpenGedcom] Gedcom Hierarchy Skip Found:\n";
            std::cerr << "\tLast Tag Level: " << m_currentTagLevel << '\n';
            std::cerr << "\tLine: " << line << '\n' << std::endl;
            uint32_t jumpCount = level - m_currentTagLevel + 1;

            for(int i = 1; i <= jumpCount; ++i) {
                m_onTagBegin({
                    .level = level + i,
                    .tag = "_INVALID",
                    .value = "Line Skip Detected"});
            }
        }

        if(level <= m_currentTagLevel) {
            m_onTagEnd(level);
        }
        m_currentTagLevel = level;

        m_onTagBegin({
            .level = level, 
            .xref = xref, 
            .tag = tag, 
            .value = value});
    }
}