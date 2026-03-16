// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Internal/StringArena.hpp"
#include <cstring>

namespace OpenGedcom::Internal {
    StringArena::StringArena() {

    }

    StringArena::~StringArena() {

    }

    std::string_view StringArena::Store(std::string_view src) {
        if(src.empty()) return {};

        if(m_chunks.empty() || m_offset + src.size() > CHUNK_SIZE) {
            m_chunks.reserve(CHUNK_SIZE);
            m_chunks.push_back(std::make_unique<char[]>(CHUNK_SIZE));
            m_offset = 0;
        }

        char* dst = m_chunks.back().get() + m_offset;
        std::memcpy(dst, src.data(), src.size());

        std::string_view result(dst, src.size());
        m_offset += src.size();

        return result;
    }
}