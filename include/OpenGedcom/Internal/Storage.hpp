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
#include "StringArena.hpp"

//std
#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

namespace OpenGedcom::Internal {
    class Storage {
    public:
        Storage(Registry* registry);
        ~Storage();

        inline void ReserveRecords(size_t size) {
            m_records.reserve(size);
        }

        inline std::vector<TagNode>& Records() {
            return m_records;
        }

        inline std::string_view SetOwnedString(std::string&& data) {
            m_ownedStorage = std::move(data);
            return m_ownedStorage;
        }

        inline std::string_view GetOwnedString() const {
            return m_ownedStorage;
        }

        inline std::string_view AddString(std::string_view data) {
            return m_arena.Store(data);
        }

        /// Debug function
        void PrintAllRecords() {
            for(auto& record : m_records) {
                std::cout << "Level: " << 0 << " Value: " << record.GetData() << '\n';
                PrintRecursive(1, record.GetChildren());
            }
        }

    private:
        void PrintRecursive(uint32_t level, std::span<TagNode> nodes) {
            for(auto& node : nodes) {
                std::cout << "Level: " << level << " Value: " << node.GetData() << '\n';
                PrintRecursive(level + 1, node.GetChildren());
            }
        }

        std::string_view Store(std::string_view src);
        
        Registry* m_registry;

        std::vector<TagNode> m_records;

        // arena used in copying, ownedStorage used in non copying
        StringArena m_arena;
        std::string m_ownedStorage;
    };
}