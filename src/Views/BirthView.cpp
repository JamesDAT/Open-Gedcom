// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/BirthView.hpp"
#include "OpenGedcom/OpenGedcom.hpp"
#include "OpenGedcom/Tags/PlacesAddresses.hpp"
#include "TagTreeParser.hpp"

namespace OpenGedcom {
    using namespace OpenGedcom::Internal;

    std::optional<DateView> BirthView::GetDate() const {
        if(auto node = GetFirstOfType<DateTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            return DateView{m_document, node.value()};
        }

        return std::nullopt;
    }

    std::optional<PlaceView> BirthView::GetPlace() const {
        if(auto node = GetFirstOfType<PlaceTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            return PlaceView{m_document, node.value()};
        }

        return std::nullopt;
    }

    std::optional<std::string_view> BirthView::GetLocation() const {
        // search addr first then fallback on place

        if(auto addr = GetValueFromFirstOfType<AddressTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            return addr.value();
        }

        if(auto place = GetValueFromFirstOfType<PlaceTag>(m_document->GetRegistry(), m_node->GetChildren())) {
            return place.value();
        }

        return std::nullopt;
    }

}