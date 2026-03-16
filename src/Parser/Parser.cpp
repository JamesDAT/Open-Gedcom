// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "Parser.hpp"
#include <cctype>

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

        m_stack.clear();
    }

    void Parser::ParseLine(const std::string_view line) {
        uint32_t level = 0;
        uint32_t xref = UINT32_MAX;
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

        if(m_makeCopies) {
            auto copyView = m_storage->AddString(value);
            CreateTag(level, xref, tag, copyView);
        }
        else {
            CreateTag(level, xref, tag, value);
        }
    }

    void Parser::CreateTag(uint32_t level, uint32_t xref, std::string_view tag, std::string_view value) {
        auto& graph = m_storage->Records();
        TagNode node = m_registry->Create(tag);

        node.SetId(xref);
        node.SetData(value);

        // resize stack to current level
        m_stack.resize(level + 1);

        uint32_t tagIndex = 0;
        if(level == 0) {
            graph.push_back(std::move(node));
            tagIndex = graph.size() - 1;
        }
        else {
            TagNode* stackNode = &graph[m_stack[0]];

            for(uint32_t i = 1; i < level; ++i) {
                stackNode = &stackNode->GetChildren()[m_stack[i]];
            }
            
            // TODO: This doesn't work, the graph at the stack 0 index is not IndiTag ever for some reason
            if(m_registry->IsType<NameTag>(node)) {
                if(m_registry->IsType<IndiTag>(graph[m_stack[0]])) {
                    m_storage->AddName(value, graph.size() - 1);
                }
            }

            stackNode->AddChild(std::move(node));
            tagIndex = stackNode->GetChildren().size() - 1;

        }

        m_stack[level] = tagIndex;
    }
}