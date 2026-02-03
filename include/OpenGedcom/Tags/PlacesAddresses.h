// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class PlaceTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PLAC";

        explicit PlaceTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class FormatTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FORM";

        explicit FormatTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AddressTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ADDR";

        explicit AddressTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CountryTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CTRY";

        explicit CountryTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class StateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "STAE";

        explicit StateTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class PostTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "POST";

        explicit PostTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CityTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CITY";

        explicit CityTag(std::string_view value)
            : GedcomTag(value) {}
    };
}