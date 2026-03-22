// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file Xref.hpp
 * @brief Defines the standard layout for xref type
 */

#include <cstdint>
#include <functional>

namespace OpenGedcom {
    struct XrefType{
        uint32_t xref;
        char type;

        bool operator==(const XrefType& other) const noexcept {
            return xref == other.xref && type == other.type;
        }
    };
}

template<>
struct std::hash<OpenGedcom::XrefType> {
    std::size_t operator()(const OpenGedcom::XrefType& x) const noexcept {
        std::size_t h1 = std::hash<uint32_t>{}(x.xref);
        std::size_t h2 = std::hash<char>{}(x.type);

        // combine hashes
        return h1 ^ (h2 << 1);
    }
};