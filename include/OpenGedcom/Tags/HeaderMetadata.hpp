// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class GedcTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "GEDC";

        using GedcomTag::GedcomTag;
    };



    class LanguageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "LANG";

        using GedcomTag::GedcomTag;
    };



    class SchemaTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SCHMA";

        using GedcomTag::GedcomTag;
    };



    class VersionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "VERS";

        using GedcomTag::GedcomTag;
    };



    class CharacterTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHAR";

        using GedcomTag::GedcomTag;
    };



    class CorporateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CORP";

        using GedcomTag::GedcomTag;
    };



    class CopyrightTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "COPR";

        using GedcomTag::GedcomTag;
    };
}