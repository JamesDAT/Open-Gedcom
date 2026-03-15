// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file StringArena.hpp
 * @brief Arena for stable strings
 *
 *
 * Stores an arbitrary number of characters, allowing for stable storage with no string_view/pointer invalidation
 */

#pragma once

// std
#include <cstddef>
#include <memory>
#include <vector>

namespace OpenGedcom::Internal {
    class StringArena {
    public:
        StringArena();
        ~StringArena();

        std::string_view Store(std::string_view src);
        
    private:
        static constexpr size_t CHUNK_SIZE = 64 * 1024;

        std::vector<std::unique_ptr<char[]>> m_chunks;
        size_t m_offset = 0;
    };
}