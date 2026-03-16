// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/DateView.hpp"
#include "OpenGedcom/OpenGedcom.hpp"
#include "TagTreeParser.hpp"
#include <string_view>

namespace OpenGedcom {
    using namespace OpenGedcom::Internal;

    std::string_view DateView::Date() const {
        return m_node->GetData();
    }

    std::optional<std::string_view> DateView::Time() const {
        return GetValueFromFirstOfType<TimeTag>(m_document->GetRegistry(), m_node->GetChildren());
    }
}