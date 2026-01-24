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
        GedcomStorage(GedcomStorage&&) = default;
        GedcomStorage& operator=(GedcomStorage&&) = default;

        // access the registry
        TagRegistry& Registry() { return m_registry; }
        const TagRegistry& Registry() const { return m_registry; }

        // parser emit function
        void Emit(int level, std::optional<uint32_t> xref, std::string_view tag, std::string_view value);

        const std::vector<GedcomNode*> GetGraph() const { return m_roots; };

    private:
        // storage ownership
        std::vector<std::unique_ptr<GedcomTag>> m_tags;
        std::vector<std::unique_ptr<GedcomNode>> m_nodes;

        // trees
        std::vector<GedcomNode*> m_levelStack;
        std::vector<GedcomNode*> m_roots;

        TagRegistry m_registry;
    };
}