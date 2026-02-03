// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "TagBase.h"

namespace OpenGedcom {



    class RecordTag : public GedcomTag {
    public:
        using GedcomTag::GedcomTag;

        uint32_t Id() const { return m_id; }
        void SetId(uint32_t id) { m_id = id; }

    private:
        uint32_t m_id;
    };



    class HeadTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "HEAD";

        explicit HeadTag(std::string_view value)
            : RecordTag(value) {}
    };



    class TrailerTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "TRLR";

        explicit TrailerTag(std::string_view value)
            : RecordTag(value) {}
    };


    
    class IndiTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "INDI";

        explicit IndiTag(std::string_view value)
            : RecordTag(value) {}
    };



    class FamilyTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "FAM";

        explicit FamilyTag(std::string_view value)
            : RecordTag(value) {}
    };



    class SourceTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SOUR";

        explicit SourceTag(std::string_view value)
            : RecordTag(value) {}
    };



    class RepoTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "REPO";

        explicit RepoTag(std::string_view value)
            : RecordTag(value) {}
    };



    class SubmitterTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SUBM";

        explicit SubmitterTag(std::string_view value)
            : RecordTag(value) {}
    };



    class ObjectTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "OBJE";

        explicit ObjectTag(std::string_view value)
            : RecordTag(value) {}
    };



    class SharedNoteTag final : public RecordTag {
    public:
        static constexpr std::string_view TagName = "SNOTE";

        explicit SharedNoteTag(std::string_view value)
            : RecordTag(value) {}
    };
}