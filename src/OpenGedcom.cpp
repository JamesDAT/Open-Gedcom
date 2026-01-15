// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include <OpenGedcom/OpenGedcom.h>
#include "Parser/GedcomParser.h"

namespace OpenGedcom {
    Document::Document() = default;

    Document::~Document() = default;

    Document Document::ParseFile(const std::filesystem::path &path) {
        GedcomStorage storage;
        GedcomParser parser{path, storage};

        Document doc;
        doc.m_storage = std::move(storage);

        return std::move(doc);
    }
}

