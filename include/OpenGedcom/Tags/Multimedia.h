// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {
    class FileTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FILE";

        explicit FileTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class MediaTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "MEDI";

        explicit MediaTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class WidthTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WIDTH";

        explicit WidthTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class HeightTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "HEIGHT";

        explicit HeightTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class LeftTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "LEFT";

        explicit LeftTag(std::string_view value)
            : GedcomTag(value) {}
    };



    class TopTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TOP";

        explicit TopTag(std::string_view value)
            : GedcomTag(value) {}
    };
}