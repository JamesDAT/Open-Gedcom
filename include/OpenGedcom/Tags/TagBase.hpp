// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file TagBase.hpp
 * @brief Base for tag types
 *
 *
 * Tag base for the registry system, any custom or extended tags should inherit from GedcomTag.
 * This is not to be confused with TagNode which is the physical storage for records/tags.
 */

#pragma once

namespace OpenGedcom {
    class GedcomTag {
    public:
        GedcomTag() = default;
        virtual ~GedcomTag() = default;
    };
}