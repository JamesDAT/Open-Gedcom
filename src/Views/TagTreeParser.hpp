// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file TagTreeParser.hpp
 * @brief Helper functions for parsing tag trees
 */

#include "OpenGedcom/Internal/Registry.hpp"
#include "OpenGedcom/Internal/TagNode.hpp"
#include <optional>
#include <span>
#include <string_view>

namespace OpenGedcom::Internal {

    template<GedcomTagType T>
    static std::optional<std::string_view> GetValueFromFirstOfType(Registry* registry, std::span<TagNode> nodes) {
        for(auto& node : nodes) {
            if(registry->IsType<T>(node)) {
                return node.GetData();
            }
        }

        return std::nullopt;
    }

    template<GedcomTagType T>
    static std::optional<TagNode*> GetFirstOfType(Registry* registry, std::span<TagNode> nodes) {
        for(auto& node : nodes) {
            if(registry->IsType<T>(node)) {
                return &node;
            }
        }

        return std::nullopt;
    }
}