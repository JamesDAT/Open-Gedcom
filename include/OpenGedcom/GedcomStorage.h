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

        const std::vector<std::unique_ptr<GedcomTag>>& Graph() const { return m_tags; }
        std::vector<std::unique_ptr<GedcomTag>>& Graph() { return m_tags; }

    private:
        // storage ownership
        std::vector<std::unique_ptr<GedcomTag>> m_tags;

        // stack
        std::vector<GedcomTag*> m_stack;

        TagRegistry m_registry;
    };
}