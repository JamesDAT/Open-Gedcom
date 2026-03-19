// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/IndiView.hpp"
#include "OpenGedcom/OpenGedcom.hpp"
#include "TagTreeParser.hpp"

#include <format>

namespace OpenGedcom {
    using namespace OpenGedcom::Internal;

    IndiView::IndiView(const TagView& base) 
        : TagView(base)
    {

    }

    std::optional<std::string_view> IndiView::Name() const {
        return GetValueFromFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren());
    }

    TagView IndiView::SetName(std::string firstName, std::string lastName) {
        return SetName(std::format("{} /{}/", firstName, lastName));
    }

    TagView IndiView::SetName(std::string name) {
        if(auto nameTag = GetFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            auto nameView = TagView{m_document, nameTag.value()};
            nameView.SetValue(name);

            return nameView;
        }
        else {
            auto nameView = m_document->CreateTag<NameTag>(this);
            nameView.SetValue(name);

            return nameView;
        }
    }

    std::optional<std::string_view> IndiView::NamePrefix() const {
        return std::nullopt;
    }

    TagView IndiView::SetNamePrefix(std::string_view prefix) {
        return TagView{m_document, m_node}; // invalid placeholder
    }

    TagView IndiView::SetGivenName(std::string given) {
        auto nameTag = GetFirstOfType<NameTag>(m_document->GetRegistry(), m_node->GetChildren());

        if(auto givenTag = GetFirstOfType<GivenNamesTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            auto givenView = TagView{m_document, givenTag.value()};
            givenView.SetValue(given);

            return givenView;
        }
        else {
            auto givenView = m_document->CreateTag<GivenNamesTag>(this);
            givenView.SetValue(given);

            return givenView;
        }
    }

    TagView IndiView::SetSex(char sex) {
        if(auto sexTag = GetFirstOfType<SexTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            auto sexView = TagView{m_document, sexTag.value()};
            sexView.SetValue(std::string{sex});

            return sexView;
        }
        else {
            auto sexView = m_document->CreateTag<SexTag>(this);
            sexView.SetValue(std::string{sex});

            return sexView;
        }
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

    std::optional<char> IndiView::Sex() const {
        if(auto value = GetValueFromFirstOfType<SexTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            if(value->empty()) {
                return std::nullopt;
            }

            return value->at(0);
        }
        return std::nullopt;
    }

    std::vector<TagView> IndiView::Events() const {
        std::vector<TagView> events;
        auto registry = m_document->GetRegistry();

        for(auto& node : m_node->GetChildren()) {
            if(registry->HasTrait(node, TagTraits::Event)) {
                events.push_back(TagView{m_document, &node});
            }
        }

        return events;
    }
}