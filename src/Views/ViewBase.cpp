// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Views/ViewBase.hpp"
#include "OpenGedcom/OpenGedcom.hpp"

namespace OpenGedcom {
    TagView::TagView(const TagView& origin) {
        m_node = origin.m_node;
        m_document = origin.m_document;
    }

    TagView& TagView::operator=(const TagView& other) {
        return *this;
    }

    std::string_view TagView::SetValue(std::string_view data) {
        auto value = m_document->GetStorage()->AddString(data);
        m_node->SetData(value);
        return value;
    }  

    std::vector<TagView> TagView::GetSubViews() const {
            std::vector<TagView> children;

            for(auto& node : m_node->GetChildren()) {
                children.push_back(TagView{m_document, &node});
            }

            return children;
        }

        std::optional<uint32_t> TagView::Id() const {
            if(m_node->GetId() == Internal::INVALID_ID) {
                return std::nullopt;
            }
            else {
                return m_node->GetId();
            }
        }
}