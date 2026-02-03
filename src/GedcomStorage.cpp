// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/GedcomStorage.h>
#include <iostream>

namespace OpenGedcom {
    void GedcomStorage::Emit(int level, std::optional<uint32_t> xref, std::string_view tagName, std::string_view value) {
        TagType type = m_registry.Find(std::string(tagName));

        std::unique_ptr<GedcomTag> tag;

        if(type != INVALID_TAG) {
            tag = m_registry.Create(std::string(tagName), std::string(value));
        }
        else {
            std::cout << "Emitted INVALID_TAG: " << tagName << '\n';
            tag = std::make_unique<GedcomTag>(value);
            tag->SetType(INVALID_TAG);
        }
        
        // create tag
        GedcomTag* tagPtr = tag.get();
        
        if(level >= static_cast<int>(m_stack.size())) {
            m_stack.resize(level + 1, nullptr);
        }
        
        if(level == 0) {
            m_tags.push_back(std::move(tag));
            if(auto* record = dynamic_cast<RecordTag*>(tagPtr)) {
                if(xref != std::nullopt) {
                    record->SetId(xref.value());
                }
            }
        }
        else {
            GedcomTag* parent = m_stack[level - 1];
            
            tagPtr->SetParent(parent);
            parent->Children().push_back(std::move(tag));
        }
        
        m_stack[level] = tagPtr;
    }
}