// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file Registry.hpp
 * @brief Registry for gedcom tag types
 *
 *
 * The registry provides a runtime mechanism for registering
 * gedcom tag types, and allows users to check the types of
 * objects, and get their traits. 
 */

#pragma once

#include "OpenGedcom/Tags/TagTraits.hpp"
#include "TagNode.hpp"
#include "BuiltinTags.hpp"

// std
#include <typeindex>
#include <unordered_map>
#include <string_view>

namespace OpenGedcom::Internal {
    template<typename T>
    concept GedcomTagType =
        std::derived_from<T, GedcomTag>;

    class Registry {
    public:
        Registry() {
            m_idToTrait.resize(std::tuple_size<BuiltinTags>::value);
            RegisterBuiltinTags(std::type_identity<BuiltinTags>{});
        }

        ~Registry() = default;
        
        template<GedcomTagType T>
        TagType RegisterTag(std::string_view tagName, TagTraits traits) {
            auto it = m_tagToId.find(tagName);
                    if (it != m_tagToId.end())
                        return it->second;

                    TagType id = m_currentTagId++;

                    m_tagToId.emplace(
                        tagName,
                        id
                    );

                    m_typeToId.emplace(std::type_index(typeid(T)), id);
                    m_idToTrait[id] = GetTagTraits<T>();

                    return id;
        }


        TagNode Create(std::string_view tagName) const {
            auto it = m_tagToId.find(tagName);
            if (it == m_tagToId.end()) {
                // unknown tag
                return {};
            }

            TagNode node{};
            node.SetType(it->second);
            return node;
        }


        TagType Find(std::string_view tagName) const {
            if (auto it = m_tagToId.find(tagName); it != m_tagToId.end())
                return it->second;
            return INVALID_TAG;
        }


        bool IsType(const TagNode& tag, std::string_view tagName) const {
            TagType type = Find(tagName);
            return tag.Type() == type;
        }

        template<GedcomTagType T>
        bool IsType(const TagNode& tag) const {
            auto it = m_typeToId.find(std::type_index(typeid(T)));
            if(it == m_typeToId.end())
                return false;

            return tag.Type() == it->second;
        }


        bool HasTrait(const TagNode& tag, TagTraits trait) const {
            if(tag.Type() < m_idToTrait.size()) {
                return Traits::HasTrait(m_idToTrait[tag.Type()], trait);
            }
            return false;
        }

        template<GedcomTagType T>
        bool HasTrait(TagTraits trait) const {
            return Traits::HasTrait(T::Traits, trait);
        }

        template<GedcomTagType T>
        TagTraits GetTraits() const {
            return T::Traits;
        }

        TagTraits GetTraits(const TagNode& tag) const {
            if(tag.Type() < m_idToTrait.size()) {
                return m_idToTrait[tag.Type()];
            }
            return TagTraits::None;
        }


    private:
        template<GedcomTagType T>
        constexpr TagTraits GetTagTraits() {
            if constexpr (requires { T::Traits; }) {
                return T::Traits;
            }
            else {
                return TagTraits::None;
            }
        }

        template<GedcomTagType... Tags>
        void RegisterBuiltinTags(std::type_identity<std::tuple<Tags...>>) {
            (RegisterTag<Tags>(std::string(Tags::TagName), GetTagTraits<Tags>()), ...);
        }

        TagType m_currentTagId = 0;

        std::unordered_map<std::string_view, TagType> m_tagToId;
        std::unordered_map<std::type_index, TagType> m_typeToId;
        std::vector<TagTraits> m_idToTrait;
    };
}