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

namespace OpenGedcom::Internal {
    using TagType = uint8_t;
    constexpr TagType INVALID_TAG = 0;

    class TagNode final {
    public:
        TagNode() {};

        TagNode(std::string_view data) 
            : m_data(data) {}

        TagNode(uint32_t dataIndex, uint32_t dataSize) 
            : m_dataIndex(dataIndex), m_dataSize(dataSize) {}

    private:
        std::string_view m_data;
        std::unique_ptr<std::vector<TagNode>> m_children;

        uint32_t m_dataIndex = 0;
        uint32_t m_dataSize = 0;
        uint32_t m_id = UINT32_MAX;

        TagType m_tagType = INVALID_TAG;
    };
}