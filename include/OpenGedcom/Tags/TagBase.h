// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include "TagTraits.h"

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <optional>

namespace OpenGedcom {
    // basic types
    using TagType = uint8_t;
    using NodeId = uint32_t;
    constexpr TagType INVALID_TAG = 0;

    struct xref {
        uint32_t id;
        TagType type;
    };

    class GedcomTag {
    public:
        GedcomTag() = default;
        virtual ~GedcomTag() = default;

        static constexpr TagTraits Traits = TagTraits::None;
    };

    class GedcomNode final {
    public:
        GedcomNode() {}

        GedcomNode(std::string_view value)
            : m_rawValue(std::make_unique<std::string>(value)) {}

        GedcomNode(std::size_t dataLocation, std::size_t count)
            : m_dataLoc(dataLocation), m_dataSize(count) {}

        std::string_view RawValue() const { 
            if(m_rawValue == nullptr) {
                return "";
            }
            else {
                return *m_rawValue;
            }
        }

        void SetValue(std::string_view value) {
            if(m_rawValue == nullptr) {
                m_rawValue = std::make_unique<std::string>(value);
            }
            else {
                *m_rawValue = value;
            }
        }

        void SetValue(std::size_t location, std::size_t size) {
            m_dataLoc = location;
            m_dataSize = size;
        }

        TagType Type() const { return m_tagType; }
        void SetType(TagType tag) { m_tagType = tag; }

        const GedcomNode* GetParent() const { return m_parent; }
        void SetParent(GedcomNode* parent) { m_parent = parent; }

        void AddChild(GedcomNode&& tag) {
            MutateChildren().push_back(std::move(tag));
        }

        const std::optional<uint32_t> GetId() const { return m_id; }
        void SetId(uint32_t id) { m_id = id; }

        const std::vector<GedcomNode>& GetChildren() const {
            // give back an empty vector if nullptr, no reason to differentiate between the two
            const static std::vector<GedcomNode> empty;
            return m_children ? *m_children : empty;
        }

        std::vector<GedcomNode>& MutateChildren() {
            if(m_children == nullptr) {
                m_children = std::make_unique<std::vector<GedcomNode>>();
            }

            return *m_children;
        }

    private:
        TagType m_tagType = INVALID_TAG;

        // 0 indicates that lazy data indices are not being used, 
        // if m_rawValue is nullptr and this is 0 then there is no data
        std::size_t m_dataSize = 0; 
        std::size_t m_dataLoc = 0;

        GedcomNode* m_parent = nullptr;
        
        // optional
        std::unique_ptr<std::vector<GedcomNode>> m_children = nullptr;
        std::unique_ptr<std::string> m_rawValue = nullptr;
        std::optional<uint32_t> m_id;
    };
}