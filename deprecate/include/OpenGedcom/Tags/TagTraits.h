// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>
namespace OpenGedcom {
    enum class TagTraits : uint32_t {
        None = 0,
        Event = 1 << 0
    };

    namespace Traits {

        inline TagTraits operator|(TagTraits a, TagTraits b) {
            return static_cast<TagTraits>(
                static_cast<uint32_t>(a) |
                static_cast<uint32_t>(b)
            );
        }

        inline bool HasTrait(TagTraits value, TagTraits trait) {
            return (static_cast<uint32_t>(value) &
                    static_cast<uint32_t>(trait)) != 0;
        }
    }
}