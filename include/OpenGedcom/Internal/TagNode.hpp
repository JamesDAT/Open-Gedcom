// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file TagNode.hpp
 * @brief The internal representation of a tag
 *
 *
 * TagNodes aim to be as memory efficient as possible and remove polymorphism to allow for fast
 * flat, cache friendly lookups. The compromise is access speed, like accessing an individuals gender
 * requires searching child nodes, checking their type, then return the character. But this for 1
 * isn't actually that slow, simple iterate, map lookup and int compare, and 2 the use case for Gedcom
 * does not necessitate iterating over everyones gender for instance. Operations that are done in bulk,
 * like id lookups or name lookups are optimized and flattened in the storage structure for speed.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>
#include <span>

namespace OpenGedcom::Internal {
    using TagType = uint8_t;
    constexpr TagType INVALID_TAG = UINT8_MAX;
    constexpr uint32_t INVALID_ID = UINT32_MAX;

    class TagNode final {
    public:
        TagNode() {};

        TagNode(std::string_view data) 
            : m_data(data) {}

        TagType Type() const {
            return m_tagType;
        }

        void SetType(TagType tagType) {
            m_tagType = tagType;
        }

        uint32_t GetId() const {
            return m_id;
        }

        void SetId(uint32_t id) {
            m_id = id;
        }

        std::string_view GetData() const {
            return m_data;
        }

        void SetData(std::string_view data) {
            m_data = data;
        }

        TagNode* AddChild(TagNode&& child) {
            if(m_children == nullptr) {
                m_children = std::make_unique<std::vector<TagNode>>();
            }

            m_children->push_back(std::move(child));
            return &m_children->back();
        }

        std::span<TagNode> GetChildren() const {
            if(m_children == nullptr) {
                return {};
            }

            return *m_children;
        }

    private:
        std::string_view m_data;
        std::unique_ptr<std::vector<TagNode>> m_children = nullptr;

        uint32_t m_id = INVALID_ID;

        TagType m_tagType = INVALID_TAG;
    };
}