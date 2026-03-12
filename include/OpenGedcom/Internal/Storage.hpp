// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file Storage.hpp
 * @brief Storage for gedcom nodes
 *
 *
 * Storage defines the layout for storing gedcom nodes,
 * as well as their creation as given by the parser
 */

#pragma once
#include "Registry.hpp"
#include "TagNode.hpp"

//std
#include <cstddef>
#include <string_view>
#include <string>
#include <vector>

namespace OpenGedcom::Internal {
    class Storage {
    public:
        Storage(Registry* registry);
        ~Storage();

        inline void ReserveRecords(size_t size) {
            m_records.reserve(size);
        }

        inline void ReserveStringArena(size_t size) {
            m_stringArena.reserve(size);
        }

        inline std::vector<TagNode>& Records() {
            return m_records;
        }
        
    private:
        std::string_view Store(std::string_view src);
        
        Registry* m_registry;

        std::vector<TagNode> m_records;

        std::string m_stringArena;

    };
}