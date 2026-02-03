// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class FactTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FACT";

        explicit FactTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class OccupationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "OCCU";

        explicit OccupationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CasteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CAST";

        explicit CasteTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class SexTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SEX";

        explicit SexTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class RoleTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ROLE";

        explicit RoleTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class StatusTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "STAT";

        explicit StatusTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ResidanceTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RESI";

        explicit ResidanceTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NationalityTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NATI";

        explicit NationalityTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NumChildrenTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NCHI";

        explicit NumChildrenTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NumMarriagesTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NMR";

        explicit NumMarriagesTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class DescriptionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DSCR";

        explicit DescriptionTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class EducationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EDUC";

        explicit EducationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NationalIdTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "IDNO";

        explicit NationalIdTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class PropertyTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PROP";

        explicit PropertyTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ReligionTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "RELI";

        explicit ReligionTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class SSNTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SSN";

        explicit SSNTag(std::string_view value)
            : GedcomTag(value) {}
    };
}