// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <filesystem>

#include "Reader/GedcomReader.h"

namespace OpenGedcom {
    class GedcomParser {
    public:
        GedcomParser(const std::filesystem::path& path);
        ~GedcomParser();

        void Parse();

    private:
        GedcomReader m_reader;
        const std::filesystem::path& m_path;
    };
}