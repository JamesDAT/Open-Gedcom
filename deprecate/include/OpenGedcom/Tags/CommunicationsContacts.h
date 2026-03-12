// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class PhoneTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PHON";

        using GedcomTag::GedcomTag;
    };



    class EmailTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EMAIL";

        using GedcomTag::GedcomTag;
    };



    class WebsiteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WWW";

        using GedcomTag::GedcomTag;
    };



    class FaxTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAX";

        using GedcomTag::GedcomTag;
    };
}