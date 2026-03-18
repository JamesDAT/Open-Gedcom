// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file ViewBase.hpp
 * @brief Base for view types
 *
 *
 * This file defines the View types for interfacing with Gedcom tags
 */

#pragma once

#include "OpenGedcom/Internal/TagNode.hpp"

// std
#include <optional>
#include <string_view>

namespace OpenGedcom {
    class Document;

    // base view, not for user use
    class TagView {
    public:
        TagView(Document* doc, Internal::TagNode* node)
            : m_document(doc), m_node(node) {}
        virtual ~TagView() {}

        [[nodiscard]] inline Internal::TagNode* Get() const {
            return m_node;
        }

        [[nodiscard]] inline std::string_view Value() const {
            return m_node->GetData();
        }

        std::string_view SetValue(std::string_view data);

        /// @brief Get views to the children nodes
        [[nodiscard]] std::vector<TagView> GetSubViews() const {
            std::vector<TagView> children;

            for(auto& node : m_node->GetChildren()) {
                children.push_back(TagView{m_document, &node});
            }

            return children;
        }

        [[nodiscard]] std::optional<uint32_t> Id() const {
            if(m_node->GetId() == Internal::INVALID_ID) {
                return std::nullopt;
            }
            else {
                return m_node->GetId();
            }
        }

        void SetId(uint32_t id) {
            m_node->SetId(id);
        }

    protected:
        Internal::TagNode* m_node;
        Document* m_document;
    };
}