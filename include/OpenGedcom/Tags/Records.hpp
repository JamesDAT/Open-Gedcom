// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.hpp"

#include <string_view>

namespace OpenGedcom {



    class RecordTag : public GedcomTag {
    public:
        using GedcomTag::GedcomTag;
        virtual ~RecordTag() = default;
        
    };



    class HeadTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "HEAD";

        using RecordTag::RecordTag;
    };



    class TrailerTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "TRLR";

        using RecordTag::RecordTag;
    };


    
    class IndiTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "INDI";
        static constexpr char RefChar = 'I';

        using RecordTag::RecordTag;
    };



    class FamilyTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "FAM";
        static constexpr char RefChar = 'F';

        using RecordTag::RecordTag;
    };



    class SourceTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SOUR";
        static constexpr char RefChar = 'S';

        using RecordTag::RecordTag;
    };



    class RepoTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "REPO";
        static constexpr char RefChar = 'R';

        using RecordTag::RecordTag;
    };



    class SubmitterTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SUBM";
        static constexpr char RefChar = 'U';

        using RecordTag::RecordTag;
    };



    class ObjectTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "OBJE";
        static constexpr char RefChar = 'M';

        using RecordTag::RecordTag;
    };



    class SharedNoteTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SNOTE";

        using RecordTag::RecordTag;
    };
}