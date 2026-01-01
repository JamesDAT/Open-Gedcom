// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <string>

namespace OpenGedcom {
    class ISourceReader {
    public:
        virtual ~ISourceReader() = default;

        virtual bool ReadChunk(std::string& out) = 0;

        constexpr static size_t CHUNK_SIZE = 64*1024; // 64KB chunks
    };
}