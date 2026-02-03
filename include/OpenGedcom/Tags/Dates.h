// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class DateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DATE";

        explicit DateTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class SortDateTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "SDATE";

        explicit SortDateTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class TimeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TIME";

        explicit TimeTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class PhraseTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PHRASE";

        explicit PhraseTag(std::string_view value)
            : GedcomTag(value) {}
    };
}