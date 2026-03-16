// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/ViewBase.hpp"
#include "OpenGedcom/OpenGedcom.hpp"

namespace OpenGedcom {
    std::string_view TagView::SetValue(std::string_view data) {
        return m_document->GetStorage()->AddString(data);
    }  
}