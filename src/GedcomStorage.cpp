// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/GedcomStorage.h>

namespace OpenGedcom {
    void GedcomStorage::Emit(int level, std::optional<uint32_t> xref, std::string_view tagName, std::string_view value) {

        // create tag
        auto tag = m_registry.Create(std::string{tagName}, std::string{value});
        GedcomTag* tagPtr = tag.get();
        m_tags.push_back(std::move(tag));

        // create node
        auto node = std::make_unique<GedcomNode>();
        node->tag = tagPtr;

        GedcomNode* nodePtr = node.get();
        m_nodes.push_back(std::move(node));

        // adjust the stack
        if(level >= static_cast<int>(m_levelStack.size())) {
            m_levelStack.resize(level + 1, nullptr);
        }

        if(level == 0) {
            m_roots.push_back(nodePtr);
            nodePtr->parent = nullptr;

            if(xref != std::nullopt) {
                nodePtr->ref.id = xref.value(); 
            }
        }
        else {
            GedcomNode* parent = m_levelStack[level - 1];
            nodePtr->parent = parent;
            parent->children.push_back(nodePtr);
        }

        m_levelStack[level] = nodePtr;
    }
}