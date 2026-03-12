// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include "GedcomObject.h"
#include "GedcomRegistry.h"

#include <optional>

namespace OpenGedcom {
    // gedcom storage object
    class GedcomStorage {
    public:
        GedcomStorage() = default;

        // no copy
        GedcomStorage(const GedcomStorage&) = delete;
        GedcomStorage& operator=(const GedcomStorage&) = delete;

        // allow move
        GedcomStorage(GedcomStorage&&) noexcept = default;
        GedcomStorage& operator=(GedcomStorage&&) noexcept = default;

        // access the registry
        TagRegistry& Registry() { return m_registry; }
        const TagRegistry& Registry() const { return m_registry; }

        // parser emit function
        void Emit(int level, std::optional<uint32_t> xref, std::string_view tag, std::string_view value);
        void Emit(int level, std::optional<uint32_t> xref, std::string_view tag, std::size_t valIndex, std::size_t valSize);

        // indicates the current emit stream is finished
        void Flush();

        const std::vector<GedcomNode>& Graph() const { return m_tags; }
        std::vector<GedcomNode>& Graph() { return m_tags; }

    private:
        void Emit(int level, std::optional<uint32_t>& xref, GedcomNode&& node);

        // TODO: Split storage model to separate Indi, Family etc. 
        // cache locality between different types is not necessary,
        // pre checking these types also gets rid of type checking at search

        // storage ownership
        std::vector<GedcomNode> m_tags;

        // stack
        std::vector<GedcomNode*> m_stack;

        TagRegistry m_registry;
    };
}