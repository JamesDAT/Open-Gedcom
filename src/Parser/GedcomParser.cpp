// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "GedcomParser.h"

namespace OpenGedcom {
    GedcomParser::GedcomParser(const std::filesystem::path& path) :
        m_path(path)
    {
        
    }

    void GedcomParser::Parse() {
        auto future = m_reader.ReadFile(m_path);





        future.wait();
    }

    GedcomParser::~GedcomParser() = default;
}