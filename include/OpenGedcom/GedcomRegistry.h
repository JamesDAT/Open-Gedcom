// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/// The registry provides a way for tags to be registered within the OpenGedcom system. It stores 3 things for each tag,
/// it stores a string literal as it would appear in the gedcom file like "INDI", it stores a type, this must be a class
/// derived from a GedcomTag, it also stores an ID which is just an integer identifier for type checking, it begins at 1
/// and counts up for every tag registered. Types defined in the GedcomBuiltin.h tuple are registered upon construction
/// automatically.

#pragma once

#include "GedcomObject.h"
#include "GedcomBuiltin.h"

#include <concepts>
#include <functional>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

namespace OpenGedcom {
    template<typename T>
    concept GedcomTagType =
        std::derived_from<T, GedcomTag>;

    class TagRegistry {
    public:
        TagRegistry() {
            RegisterBuiltinTags(std::type_identity<BuiltinTags>{});
        }

        ~TagRegistry() = default;

        template<GedcomTagType T>
        TagType RegisterTag(const std::string& tagName) {
            auto it = m_registry.find(tagName);
                    if (it != m_registry.end())
                        return it->second;

                    TagType id = m_nextID++;

                    m_registry.emplace(
                        std::string(tagName),
                        id
                    );

                    m_typeToId.emplace(std::type_index(typeid(T)), id);

                    return id;
        }

        GedcomNode Create(const std::string& tagName) const {
            auto it = m_registry.find(tagName);
            if (it == m_registry.end()) {
                // unknown tag fallback
                GedcomNode node{};
                node.SetType(INVALID_TAG);
                return node;
            }

            GedcomNode node{};
            node.SetType(it->second);
            return node;
        }

        TagType Find(const std::string& tagName) const {
            if (auto it = m_registry.find(tagName); it != m_registry.end())
                return it->second;
            return INVALID_TAG;
        }

        bool IsType(const GedcomNode& tag, const std::string& tagName) {
            TagType type = Find(tagName);
            return tag.Type() == type;
        }

        template<GedcomTagType T>
        bool IsType(const GedcomNode& tag) const {
            auto it = m_typeToId.find(std::type_index(typeid(T)));
            if(it == m_typeToId.end())
                return false;

            return tag.Type() == it->second;
        }

        template<typename T>
        TagType TypeId() const {
            return T::TypeId;
        }

    private:
        TagType m_nextID = 1; // INVALID_TAG is 0

        std::unordered_map<std::string, TagType, std::hash<std::string>, std::equal_to<>> m_registry;
        std::unordered_map<std::type_index, TagType> m_typeToId;

        template<typename T>
        static std::unique_ptr<GedcomTag> CreateTag(std::string_view value) {
            return std::make_unique<T>(value);
        }

        template<typename... Tags>
        void RegisterBuiltinTags(std::type_identity<std::tuple<Tags...>>) {
            (RegisterTag<Tags>(std::string(Tags::TagName)), ...);
        }

    };
}