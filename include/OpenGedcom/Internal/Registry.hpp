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
#include <deque>
#include <iostream>
#include <optional>
#include <typeindex>
#include <unordered_map>
#include <string_view>

namespace OpenGedcom::Internal {
    class Registry {
    public:
        Registry() {
            m_idToTrait.resize(std::tuple_size<BuiltinTags>::value);
            m_tagToId.reserve(std::tuple_size<BuiltinTags>::value);
            m_typeToId.reserve(std::tuple_size<BuiltinTags>::value);
            m_recordRefs.reserve(6); // there are 6 builtin records with xref idents
            RegisterBuiltinTags(std::type_identity<BuiltinTags>{});
        }

        ~Registry() = default;
        
        template<GedcomTagType T>
        TagType RegisterTag(std::string_view tagName, bool makeCopy = true) {
            auto it = m_tagToId.find(tagName);

            if (it != m_tagToId.end())
                return it->second;

            TagType id = m_currentTagId++;
            
            if(makeCopy) {
                m_tagStorage.push_back(std::string(tagName));
                tagName = m_tagStorage.back();
            }

            m_tagToId.emplace(tagName, id);
            m_typeToId.emplace(std::type_index(typeid(T)), id);

            if(id >= m_idToTrait.size()) {
                m_idToTrait.resize(id + 1);
            }
            m_idToTrait[id] = GetTagTraits<T>();
            
            if(auto xrefChar = GetTagXrefChar<T>()) {
                RegisterXrefChar(id, xrefChar.value());
            }

            return id;
        }

        // runtime custom types cannot have traits or xref idents
        template<>
        TagType RegisterTag<CustomTag>(std::string_view tagName, bool makeCopy) {
            auto it = m_tagToId.find(tagName);

            if (it != m_tagToId.end())
                return it->second;

            TagType id = m_currentTagId++;

            if(makeCopy) {
                m_tagStorage.push_back(std::string(tagName));
                tagName = m_tagStorage.back();
            }

            m_tagToId.emplace(tagName, id);

            return id;
        }



        TagNode Create(std::string_view tagName) const {
            TagNode node{};

            auto it = m_tagToId.find(tagName);
            if (it == m_tagToId.end()) {
                // unknown tag
                node.SetType(INVALID_TAG);
                return node;
            }

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

        bool IsKnown(std::string_view tag) {
            return m_tagToId.contains(tag);
        }

        void DebugDumpTags() {
            for(auto [key, value] : m_tagToId) {
                std::cout << key << '\n';
            }
        }

        std::string_view GetTypeString(const TagNode& node) const {
            for(auto& [string, id] : m_tagToId) {
                if(node.Type() == id) {
                    return string;
                }
            }
            return "_INVALID";
        }

        template<GedcomTagType T>
        std::string_view GetTypeString() const {
            auto it = m_typeToId.find(std::type_index(typeid(T)));
            if(it != m_typeToId.end()) {
                for(auto& [string, id] : m_tagToId) {
                    if(it->second == id) {
                        return string;
                    }
                }
            }

            return "_INVALID";
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

        void RegisterXrefChar(TagType tag, char character) {
            if(tag >= m_recordRefs.size()) {
                m_recordRefs.resize(tag + 1);
            }

            m_recordRefs[tag] = character;
        }

        template<GedcomTagType T>
        char GetXrefChar() const {
            return T::RefChar;
        }

        char GetXrefChar(const TagNode& tag) const {
            if(tag.Type() < m_recordRefs.size()) {
                return m_recordRefs[tag.Type()];
            }

            return '_';
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

        template<GedcomTagType T>
        constexpr std::optional<char> GetTagXrefChar() {
            if constexpr ( requires { T::RefChar; }) {
                return T::RefChar;
            }
            else {
                return std::nullopt;
            }
        }

        template<GedcomTagType... Tags>
        void RegisterBuiltinTags(std::type_identity<std::tuple<Tags...>>) {
            (RegisterTag<Tags>(Tags::TagName, false), ...);
        }

        TagType m_currentTagId = 0;

        std::deque<std::string> m_tagStorage; // for tags that need to be stored
        std::unordered_map<std::string_view, TagType> m_tagToId;
        std::unordered_map<std::type_index, TagType> m_typeToId;
        std::vector<TagTraits> m_idToTrait;
        std::vector<char> m_recordRefs; // xref prefixes
    };
}