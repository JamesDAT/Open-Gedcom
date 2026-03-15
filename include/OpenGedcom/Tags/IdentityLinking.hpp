// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class UIDTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "UID";

        using GedcomTag::GedcomTag;
    };



    class RefTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "REFN";

        using GedcomTag::GedcomTag;
    };



    class ExternalIdTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EXID";

        using GedcomTag::GedcomTag;
    };



    class NameTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NAME";

        using GedcomTag::GedcomTag;
    };



    class NamePrefixTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NPFX";

        using GedcomTag::GedcomTag;
    };



    class GivenNamesTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "GIVN";

        using GedcomTag::GedcomTag;
    };



    class SurnameTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SURN";

        using GedcomTag::GedcomTag;
    };



    class TypeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TYPE";

        using GedcomTag::GedcomTag;
    };
}