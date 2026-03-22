// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file Custom.hpp
 * @brief Custom Tags For Gedcom
 *
 *
 * This file provides the custom tag, this encompasses all tags unknown to the registry, they will be marked as a generic custom tag.
 * The string literal of such tags is still retained, but their type lookups will match to a generic CustomTag. This file also provides
 * the _INVALID tag which is a custom tag defined by OpenGedcom. It is used in places where an unrecoverable error has occured. Such as
 * a literal not being defined in the registry at all, or a line skip was detected so _INVALID is inserted as a placeholder.
 */

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class CustomTag final : public GedcomTag {
    public:
        // this is a CustomTag representation but not a tag itself,
        // it does not define a literal as it represents all literals
        // that are otherwise unknown 

        using GedcomTag::GedcomTag;
    };

    class InvalidTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "_INVALID";

        using GedcomTag::GedcomTag;
    };
}