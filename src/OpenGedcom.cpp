// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/OpenGedcom.hpp"

#include "OpenGedcom/Views/IndiView.hpp"
#include "Parser/Parser.hpp"
#include <cassert>
#include <cctype>

namespace OpenGedcom {
    using namespace Internal;

    Document::Document() {
        
    }

    Document::~Document() {
        
    }

    Document Document::Parse(std::string_view data) {
        Document doc{};
        std::vector<TagNode*> parseStack;

        Parser parser{};

        parser.BindDocumentBegin([&doc](DocumentInfo info){
            
        });

        parser.BindTagBegin([&doc, &parseStack](TagInfo info){
            assert(parseStack.size() == info.level); // these should never mismatch, parser bug if this occurs

            std::string_view value = info.value;
            
            // Name is special as it is used for fuzzy finding
            if(info.tag == "NAME") {
                value = doc.m_names.Store(info.value);
            }
            else if(!value.empty()) {
                value = doc.m_values.Store(info.value);
            }



            TagNode node = doc.m_registry.Create(info.tag);
            uint32_t xref = UINT32_MAX;

            // compute xref
            if(!info.xref.empty()) {
                xref = 0;

                for(auto character : info.xref) {
                    if(std::isdigit(static_cast<unsigned char>(character))) {
                        xref = xref * 10 + (character - '0'); // char to int, moving the existing digits up by 1 place each time
                    }
                }
            }

            
            
            node.SetId(xref);
            node.SetData(value);
            
            TagNode* tagPtr = nullptr;
            
            if(info.level == 0) {
                doc.m_records.push_back(std::move(node));
                tagPtr = &doc.m_records.back();
            }
            else {
                doc.m_tags.push_back(std::move(node));
                tagPtr = &doc.m_tags.back();
                
                auto parent = parseStack.back();

                parent->AddChild(tagPtr);
            }

            parseStack.push_back(tagPtr);
        });

        parser.BindTagEnd([&parseStack](uint32_t level) {
            parseStack.resize(level);
        });

        parser.BindDocumentEnd([](){

        });


        parser.Parse(data);
        return doc;
    }

    Document Document::ParseReader(std::shared_ptr<IReader> reader, bool lazyLoad) {
        Document doc{};

        Parser parser{};

        return doc;
    }

    std::optional<IndiView> Document::GetIndividual(uint32_t id) {
        for(auto& record : m_records) {
            if(record.GetId() == id) {
                return IndiView{this, &record};
            }
        }

        return std::nullopt;
    }

    std::vector<IndiView> Document::GetIndividuals(std::string_view name) {
        std::vector<IndiView> views;
        

        return views;
    }

    TagView Document::CreateTag(std::string_view tag, TagView* parent) {
        auto node = m_registry.Create(tag);
        m_tags.push_back(std::move(node));
        auto nodePtr = &m_tags.back();
        
        if(parent != nullptr) {
            auto parentNode = parent->Get();
            parentNode->AddChild(nodePtr);

            return TagView{this, nodePtr};
        }
        else {
            m_records.push_back(std::move(node));

            return TagView{this, &m_records.back()};
        }

    }
}
