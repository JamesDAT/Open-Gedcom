// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>
#include <functional>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <concepts>


namespace OpenGedcom {

    // basic types
    using TagType = uint32_t;
    constexpr TagType INVALID_TAG = 0;

    struct xref {
        uint32_t id;
        TagType type;
    };

    // tree
    class GedcomTag {
    public:
        virtual ~GedcomTag() = default;

        // force constructor to take a value
        explicit GedcomTag(std::string_view rawValue)
            : m_rawValue(rawValue) {}

        bool HasValue() const { return !m_rawValue.empty(); }

        std::string_view Value() const { return m_rawValue; }

        TagType Type() const { return m_tagType; }
        void SetType(TagType tag) { m_tagType = tag; }

    private:
        std::string m_rawValue;
        TagType m_tagType;
    };


    struct GedcomNode {
        GedcomTag* tag; // non owning tag
        GedcomNode* parent = nullptr;
        std::vector<GedcomNode*> children;
        xref ref;
    };
    
    // tags
    class IndiTag : public GedcomTag {
    public:
        explicit IndiTag(std::string_view value)
            : GedcomTag(value)
        {
            // parse name value   
        }
        
        std::string_view Given() const { return m_given; }
        std::string_view Surname() const { return m_surname; }
    private:
        std::string_view m_given;
        std::string_view m_surname;
    };

    class OccuTag : public GedcomTag {
    public:
        using GedcomTag::GedcomTag;
    };

    class SexTag : public GedcomTag {
    public:
        explicit SexTag(std::string_view value)
            : GedcomTag({}) // sex tag does not store a raw value, but requires parsing
        {
            if(value.length() != 1) {
                // emmit error
            }

            m_sex = value[0];
        }

        char Sex() const { return m_sex; }

    private:
        char m_sex;
    };
}