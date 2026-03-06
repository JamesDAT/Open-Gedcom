// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/OpenGedcom.h>
#include <iostream>
#include "OpenGedcom/GedcomObject.h"
#include "Parser/GedcomParser.h"

namespace OpenGedcom {
    Document::Document() = default;

    Document::~Document() = default;

    Document Document::ParseFile(const std::filesystem::path &path, bool lazyLoad) {
        GedcomStorage storage;
        GedcomParser parser{path, storage, lazyLoad};
        parser.Parse();

        Document doc;
        doc.m_storage = std::move(storage);

        return doc;
    }

    std::optional<IndividualView> Document::Individual(uint32_t id) {
        for(auto& tag : m_storage.Graph()) {
            if(m_storage.Registry().IsType<IndiTag>(tag)) {
                if(tag.GetId() == id) {
                    IndividualView individual{&tag};
                    return individual;
                }
            }
        }
        return std::nullopt;
    }
}

