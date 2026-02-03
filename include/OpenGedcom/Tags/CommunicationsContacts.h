// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class PhoneTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PHON";

        explicit PhoneTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class EmailTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "EMAIL";

        explicit EmailTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class WebsiteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WWW";

        explicit WebsiteTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class FaxTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FAX";

        explicit FaxTag(std::string_view value)
            : GedcomTag(value) {}
    };
}