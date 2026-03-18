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

#include "RecordStorage.hpp"

//std
#include <cstddef>
#include <iostream>
#include <span>
#include <string_view>
#include <utility>
#include <vector>

namespace OpenGedcom::Internal {
    class Storage {
    public:
        Storage(Registry* registry);
        Storage(Registry* registry, std::string&& data) 
            : m_ownedStorage(std::move(data)) {}
        ~Storage();

        inline void ReserveRecords(size_t size) {
            m_records.reserve(size);
        }

        inline std::vector<TagNode>& Records() {
            return m_records;
        }

        inline std::string_view GetOwnedString() const {
            return m_ownedStorage;
        }

        inline std::string_view AddString(std::string_view data) {
            return m_arena.Store(data);
        }

        inline void AddName(std::string_view name, uint32_t index) {
            m_nameList.push_back({name, index});
        }

        inline std::span<std::pair<std::string_view, uint32_t>> GetNameIndices() {
            return m_nameList;
        }

        inline Registry* GetRegistry() const {
            return m_registry;
        }

        /// Debug function
        void PrintAllRecords() {
            for(auto& record : m_records) {
                std::cout << "Level: " << 0 << " Value: " << record.GetData() << '\n';
                PrintRecursive(1, record.GetChildren());
            }
        }

        void PrintAllNameIndices() {
            for(auto& [name, index] : m_nameList) {
                std::cout << "Name: " << name << '\n';
            }
        }

        void PrintAllWithName(std::string_view nameToSearch) {
            for(auto& [name, index] : m_nameList) {
                if(name == nameToSearch) {
                    std::cout << "Found: " << index << '\n';
                    std::cout << "ID: " << m_records[index].GetId() << '\n';
                }
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

        // this records vector needs to be moved to a stable implementation like the StringArena.
        // as it will be mutated at runtime if the user adds records, it could invalidate all views.
        // a simple implementation like the StringArena would work, and indices into it can also still
        // work like normal
        std::vector<TagNode> m_records;
        std::vector<std::pair<std::string_view, uint32_t>> m_nameList;

        // arena used in copying, ownedStorage used in non copying
        // mutations made will always go to the arena.
        // the ownedStorage must never be modified or invalidated
        StringArena m_arena;
        const std::string m_ownedStorage;
    };
}