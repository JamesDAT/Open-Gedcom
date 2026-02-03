// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>

namespace OpenGedcom {
    // basic types
    using TagType = uint32_t;
    using NodeId = uint32_t;
    constexpr TagType INVALID_TAG = 0;

    struct xref {
        uint32_t id;
        TagType type;
    };

    class GedcomTag {
    public:
        virtual ~GedcomTag() = default;

        // force constructor to take a value
        explicit GedcomTag(std::string_view value)
            : m_rawValue(value) {}

        const std::string& RawValue() const { return m_rawValue; }

        TagType Type() const { return m_tagType; }
        void SetType(TagType tag) { m_tagType = tag; }

        GedcomTag* Parent() const { return m_parent; }
        void SetParent(GedcomTag* parent) { m_parent = parent; }

        const std::vector<std::unique_ptr<GedcomTag>>& Children() const { return m_children; }
        std::vector<std::unique_ptr<GedcomTag>>& Children() { return m_children; }

    private:
        GedcomTag* m_parent = nullptr;
        std::vector<std::unique_ptr<GedcomTag>> m_children;

        std::string m_rawValue;
        TagType m_tagType = INVALID_TAG;
    };
}