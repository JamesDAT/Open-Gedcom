// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class FamilyChildTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAMC";

        explicit FamilyChildTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class FamilySpouseTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAMS";

        explicit FamilySpouseTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class HusbandTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "HUSB";

        explicit HusbandTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class WifeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WIFE";

        explicit WifeTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ChildTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHIL";

        explicit ChildTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class PedigreeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PEDI";

        explicit PedigreeTag(std::string_view value)
            : GedcomTag(value) {}
    };
}