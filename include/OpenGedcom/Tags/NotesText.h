// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class TextTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TEXT";

        explicit TextTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class NoteTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "NOTE";

        explicit NoteTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class TranslationTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TRAN";

        explicit TranslationTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class ChangeTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "CHAN";

        explicit ChangeTag(std::string_view value)
            : GedcomTag(value) {}
    };
}