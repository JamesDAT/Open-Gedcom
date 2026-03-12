// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class PageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PAGE";

        using GedcomTag::GedcomTag;
    };



    class CallTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CALN";

        using GedcomTag::GedcomTag;
    };



    class DataTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DATA";

        using GedcomTag::GedcomTag;
    };



    class AgencyTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "AGNC";

        using GedcomTag::GedcomTag;
    };



    class TitleTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TITL";

        using GedcomTag::GedcomTag;
    };



    class AbbreviationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ABBR";

        using GedcomTag::GedcomTag;
    };



    class AuthorTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "AUTH";

        using GedcomTag::GedcomTag;
    };



    class PublicationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PUBL";

        using GedcomTag::GedcomTag;
    };
}