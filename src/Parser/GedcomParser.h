// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <filesystem>

#include "Reader/GedcomReader.h"
#include "OpenGedcom/GedcomStorage.h"

namespace OpenGedcom {
    class GedcomParser {
    public:
        GedcomParser(const std::filesystem::path& path, GedcomStorage& storage);
        ~GedcomParser();

        void Parse();

    private:
        GedcomReader m_reader;
        GedcomStorage& m_storage;
        std::filesystem::path m_path;

        inline void ParseGedcomLine(std::string_view line);
    };
}