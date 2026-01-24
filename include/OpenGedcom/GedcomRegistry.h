// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#include "GedcomObject.h"

#include <functional>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

namespace OpenGedcom {
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
                            .creator = &CreateTag<T>,
                            .type = std::type_index(typeid(T))
                        }
                    );

                    m_typeToId.emplace(std::type_index(typeid(T)), id);

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

        bool IsType(const GedcomTag* tag, const std::string& tagName) {
            TagType type = Find(tagName);
            return tag->Type() == type;
        }

        template<GedcomTagType T>
        bool IsType(const GedcomTag* tag) const {
            auto it = m_typeToId.find(std::type_index(typeid(T)));
            if(it == m_typeToId.end())
                return false;

            return tag->Type() == it->second;
        }

        template<GedcomTagType T>
        T* As(GedcomTag* tag) const {
            return IsType<T>(tag) ? static_cast<T*>(tag) : nullptr;
        }

    private:
        TagType m_nextID = 1; // INVALID_TAG begins at 0

        using Creator = std::unique_ptr<GedcomTag>(*)(std::string_view);

        struct TagEntry {
            TagType id;
            Creator creator;
            std::type_index type;
        };

        std::unordered_map<std::string, TagEntry, std::hash<std::string>, std::equal_to<>> m_registry;
        std::unordered_map<std::type_index, TagType> m_typeToId;

        template<typename T>
        static std::unique_ptr<GedcomTag> CreateTag(std::string_view value) {
            return std::make_unique<T>(value);
        }
    };
}