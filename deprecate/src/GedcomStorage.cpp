// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/GedcomStorage.h>
#include <iostream>

namespace OpenGedcom {
    void GedcomStorage::Emit(int level, std::optional<uint32_t> xref, std::string_view tagName, std::string_view value) {
        GedcomNode node = m_registry.Create(std::string(tagName));
        node.SetValue(value);
        Emit(level, xref, std::move(node));
    }

    void GedcomStorage::Emit(int level, std::optional<uint32_t> xref, std::string_view tagName, std::size_t valIndex, std::size_t valSize) {
        GedcomNode node = m_registry.Create(std::string(tagName));
        node.SetValue(valIndex, valSize);
        Emit(level, xref, std::move(node));
    }

    void GedcomStorage::Emit(int level, std::optional<uint32_t>& xref, GedcomNode&& node) {
        GedcomNode* tagPtr = &node;
        
        if(level >= static_cast<int>(m_stack.size())) {
            m_stack.resize(level + 1, nullptr);
        }
        
        if(level == 0) {
            m_tags.push_back(std::move(node));
            tagPtr = &m_tags.back();

            if(xref != std::nullopt) {
                tagPtr->SetId(xref.value());
            }
        }
        else {
            GedcomNode* parent = m_stack[level - 1];
            
            tagPtr->SetParent(parent);
            parent->AddChild(std::move(node));

            tagPtr = &(parent->MutateChildren().back());
        }
        
        m_stack[level] = tagPtr;
    }

    void GedcomStorage::Flush() {
        m_stack.clear();
    }
}