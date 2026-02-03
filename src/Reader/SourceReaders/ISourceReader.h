// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <string>
#include <optional>

namespace OpenGedcom {
    class ISourceReader {
    public:
        virtual ~ISourceReader() = default;

        virtual std::optional<std::string> ReadLine() = 0;

        constexpr static size_t CHUNK_SIZE = 64*1024; // 64KB chunks
    };
}