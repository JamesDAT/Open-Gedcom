// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Internal/Storage.hpp"

namespace OpenGedcom::Internal {
    Storage::Storage(Registry* registry) 
        : m_registry(registry)
    {

    }

    Storage::~Storage() {

    }

    std::string_view Storage::Store(std::string_view src) {
        size_t offset = m_stringArena.size();
        m_stringArena.append(src.data(), src.size());

        return std::string_view(m_stringArena.data() + offset, src.size());
    }
}