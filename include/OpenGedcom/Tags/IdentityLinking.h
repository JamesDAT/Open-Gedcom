// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class UIDTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "UID";

        explicit UIDTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class RefTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "REFN";

        explicit RefTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ExternalIdTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EXID";

        explicit ExternalIdTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NameTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NAME";

        explicit NameTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NamePrefixTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NPFX";

        explicit NamePrefixTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class GivenNamesTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "GIVN";

        explicit GivenNamesTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class SurnameTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SURN";

        explicit SurnameTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class TypeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TYPE";

        explicit TypeTag(std::string_view value)
            : GedcomTag(value) {}
    };
}