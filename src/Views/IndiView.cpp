// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/IndiView.hpp"
#include "OpenGedcom/OpenGedcom.hpp"
#include "TagTreeParser.hpp"

namespace OpenGedcom {
    using namespace OpenGedcom::Internal;

    std::optional<std::string_view> IndiView::Name() const {
        return GetValueFromFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren());
    }

    std::optional<std::string_view> IndiView::GivenName() const {
        return GetValueFromFirstOfType<GivenNamesTag>(m_document->GetRegistry(), m_node->GetChildren());
    }

    std::optional<std::string_view> IndiView::FirstName() const {
        if (auto value = GetValueFromFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            auto string = value.value();

            size_t slash = string.find_first_of('/');

            if(slash == std::string_view::npos) {
                return string;
            }

            return string.substr(0, slash > 0 && std::isblank(string[slash - 1]) ? slash - 1 : slash);
        }
        else {
            return std::nullopt;
        }
    }

    std::optional<std::string_view> IndiView::LastName() const {
        if (auto value = GetValueFromFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            auto string = value.value();

            size_t first = string.find_first_of('/');
            size_t second = string.find_last_of('/');

            if(first == std::string_view::npos || second == std::string_view::npos) {
                return std::nullopt;
            }

            return string.substr(first + 1, second - first - 1);
        }
        else {
            return std::nullopt;
        }
    }
}