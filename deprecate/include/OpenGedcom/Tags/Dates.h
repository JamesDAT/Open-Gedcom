// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class DateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DATE";

        using GedcomTag::GedcomTag;
    };



    class SortDateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SDATE";

        using GedcomTag::GedcomTag;
    };



    class TimeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TIME";

        using GedcomTag::GedcomTag;
    };



    class PhraseTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PHRASE";

        using GedcomTag::GedcomTag;
    };
}