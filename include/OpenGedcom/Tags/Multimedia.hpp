// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {
    class FileTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "FILE";

        using GedcomTag::GedcomTag;
    };



    class MediaTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "MEDI";

        using GedcomTag::GedcomTag;
    };



    class WidthTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "WIDTH";

        using GedcomTag::GedcomTag;
    };



    class HeightTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "HEIGHT";

        using GedcomTag::GedcomTag;
    };



    class LeftTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "LEFT";

        using GedcomTag::GedcomTag;
    };



    class TopTag final : public GedcomTag {
    public:
        static constexpr std::string_view TagName = "TOP";

        using GedcomTag::GedcomTag;
    };
}