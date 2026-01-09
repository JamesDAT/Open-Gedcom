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
    };

    // registry

    template<typename T>
    concept GedcomTagType =
        std::derived_from<T, GedcomTag> &&
        std::constructible_from<T, std::string_view>;

    /// TagRegistry stores the string code for the tag, and a function reference for how to construct that tag
    /// all tags derive from GedcomTag
    class TagRegistry {
    public:
        template<GedcomTagType T>
        TagType RegisterTag(const std::string& tagName) {
            auto it = m_registry.find(tagName);
                    if (it != m_registry.end())
                        return it->second.id;

                    TagType id = m_nextID++;

                    m_registry.emplace(
                        std::string(tagName),
                        TagEntry{
                            .id = id,
                            .creator = &CreateTag<T>
                        }
                    );

                    return id;
        }

        std::unique_ptr<GedcomTag> Create(const std::string& tagName, const std::string& value) const {
            auto it = m_registry.find(tagName);
            if (it == m_registry.end()) {
                // unknown tag fallback
                auto tag = std::make_unique<GedcomTag>(value);
                tag->SetType(INVALID_TAG);
                return tag;
            }

            auto tag = it->second.creator(value);
            tag->SetType(it->second.id);
            return tag;
        }

        TagType Find(const std::string& tagName) const {
            if (auto it = m_registry.find(tagName); it != m_registry.end())
                return it->second.id;
            return INVALID_TAG;
        }

        bool IsType(GedcomTag* tag, const std::string& tagName) {
            TagType type = Find(tagName);
            return tag->Type() == type;
        }

    private:
        TagType m_nextID = 1; // INVALID_TAG begins at 0

        using Creator = std::unique_ptr<GedcomTag>(*)(std::string_view);

        struct TagEntry {
            TagType id;
            Creator creator;
        };

        std::unordered_map<std::string, TagEntry, std::hash<std::string>, std::equal_to<>> m_registry;

        template<typename T>
        static std::unique_ptr<GedcomTag> CreateTag(std::string_view value) {
            return std::make_unique<T>(value);
        }
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