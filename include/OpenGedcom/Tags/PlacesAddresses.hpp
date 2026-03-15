// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class PlaceTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PLAC";

        using GedcomTag::GedcomTag;
    };



    class FormatTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FORM";

        using GedcomTag::GedcomTag;
    };



    class AddressTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ADDR";

        using GedcomTag::GedcomTag;
    };



    class CountryTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CTRY";

        using GedcomTag::GedcomTag;
    };



    class StateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "STAE";

        using GedcomTag::GedcomTag;
    };



    class PostTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "POST";

        using GedcomTag::GedcomTag;
    };



    class CityTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CITY";

        using GedcomTag::GedcomTag;
    };
}