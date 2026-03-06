// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class FactTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FACT";

        using GedcomTag::GedcomTag;
    };



    class OccupationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "OCCU";

        using GedcomTag::GedcomTag;
    };



    class CasteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CAST";

        using GedcomTag::GedcomTag;
    };



    class SexTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SEX";

        using GedcomTag::GedcomTag;
    };



    class RoleTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ROLE";

        using GedcomTag::GedcomTag;
    };



    class StatusTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "STAT";

        using GedcomTag::GedcomTag;
    };



    class ResidanceTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RESI";

        using GedcomTag::GedcomTag;
    };



    class NationalityTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NATI";

        using GedcomTag::GedcomTag;
    };



    class NumChildrenTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NCHI";

        using GedcomTag::GedcomTag;
    };



    class NumMarriagesTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NMR";

        using GedcomTag::GedcomTag;
    };



    class DescriptionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DSCR";

        using GedcomTag::GedcomTag;
    };



    class EducationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EDUC";

        using GedcomTag::GedcomTag;
    };



    class NationalIdTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "IDNO";

        using GedcomTag::GedcomTag;
    };



    class PropertyTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PROP";

        using GedcomTag::GedcomTag;
    };



    class ReligionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RELI";

        using GedcomTag::GedcomTag;
    };



    class SSNTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SSN";

        using GedcomTag::GedcomTag;
    };
}