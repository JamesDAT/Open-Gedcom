// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/ViewBase.hpp"
#include "OpenGedcom/OpenGedcom.hpp"

namespace OpenGedcom {
    std::string_view TagView::SetValue(std::string_view data) {
        auto value = m_document->GetStorage()->AddString(data);
        m_node->SetData(value);
        return value;
    }  
}