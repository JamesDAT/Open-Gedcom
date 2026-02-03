// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class GedcTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "GEDC";

        explicit GedcTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class LanguageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "LANG";

        explicit LanguageTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class SchemaTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SCHMA";

        explicit SchemaTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class VersionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "VERS";

        explicit VersionTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CharacterTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHAR";

        explicit CharacterTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CorporateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CORP";

        explicit CorporateTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CopyrightTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "COPR";

        explicit CopyrightTag(std::string_view value)
            : GedcomTag(value) {}
    };
}