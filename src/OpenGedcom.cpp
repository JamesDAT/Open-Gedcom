// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/OpenGedcom.h>
#include "OpenGedcom/GedcomObject.h"
#include "Parser/GedcomParser.h"

namespace OpenGedcom {
    Document::Document() = default;

    Document::~Document() = default;

    Document Document::ParseFile(const std::filesystem::path &path) {
        GedcomStorage storage;
        GedcomParser parser{path, storage};
        parser.Parse();

        Document doc;
        doc.m_storage = std::move(storage);

        return doc;
    }

    std::optional<IndividualView> Document::Individual(uint32_t id) {
        for(const auto& tag : m_storage.Graph()) {
            if(auto indi = m_storage.Registry().As<IndiTag>(tag.get())) {
                if(indi->Id() == id) {
                    IndividualView individual{indi};
                    return individual;
                }
            }
        }
        return std::nullopt;
    }
}

