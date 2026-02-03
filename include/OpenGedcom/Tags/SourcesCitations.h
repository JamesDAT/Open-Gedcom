// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class PageTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PAGE";

        explicit PageTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class CallTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CALN";

        explicit CallTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class DataTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "DATA";

        explicit DataTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AgencyTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "AGNC";

        explicit AgencyTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class TitleTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TITL";

        explicit TitleTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AbbreviationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "ABBR";

        explicit AbbreviationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class AuthorTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "AUTH";

        explicit AuthorTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class PublicationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "PUBL";

        explicit PublicationTag(std::string_view value)
            : GedcomTag(value) {}
    };
}