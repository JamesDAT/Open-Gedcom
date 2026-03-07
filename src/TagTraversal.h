// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT
#pragma once
#include "OpenGedcom/GedcomObject.h"
#include "OpenGedcom/GedcomRegistry.h"
#include "OpenGedcom/GedcomViews.h"

namespace OpenGedcom {
    class Traverse {
    public:

        template<typename T>
        static inline std::optional<const GedcomNode*> GetChild(const TagView* view) {
            const auto* registry = view->Registry();
            const GedcomNode* node = view->Data();

            return GetChild<T>(registry, node);
        }

        template<typename T>
        static inline std::optional<const GedcomNode*> GetChild(const TagRegistry* registry, const GedcomNode* node) {
            for(auto& child : node->GetChildren()) {
                if (registry->IsType<T>(child)) {
                    return &child;
                }
            }

            return std::nullopt;
        }

        template<typename T>
        static inline std::vector<const GedcomNode*> GetChildren(const TagView* view) {
            const auto* registry = view->Registry();
            const GedcomNode* node = view->Data();

            return GetChildren<T>(registry, node);
        }

        template<typename T>
        static inline std::vector<const GedcomNode*> GetChildren(const TagRegistry* registry, const GedcomNode* node) {
            std::vector<const GedcomNode*> children{};

            for(auto& child : node->GetChildren()) {
                if (registry->IsType<T>(child)) {
                    children.push_back(&child);
                }
            }

            return children;
        }

    };
}