// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class TextTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TEXT";

        using GedcomTag::GedcomTag;
    };



    class NoteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NOTE";

        using GedcomTag::GedcomTag;
    };



    class TranslationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TRAN";

        using GedcomTag::GedcomTag;
    };



    class ChangeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHAN";

        using GedcomTag::GedcomTag;
    };
}