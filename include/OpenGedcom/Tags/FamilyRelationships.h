// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class FamilyChildTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAMC";

        using GedcomTag::GedcomTag;
    };



    class FamilySpouseTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAMS";

        using GedcomTag::GedcomTag;
    };



    class HusbandTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "HUSB";

        using GedcomTag::GedcomTag;
    };



    class WifeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WIFE";

        using GedcomTag::GedcomTag;
    };



    class ChildTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHIL";

        using GedcomTag::GedcomTag;
    };



    class PedigreeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PEDI";

        using GedcomTag::GedcomTag;
    };
}