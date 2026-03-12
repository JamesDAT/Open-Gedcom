// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file IReader.hpp
 * @brief Interface for readers, to be used in chunk parsing
 *
 *
 * This file provides the class interface for the IReader, the IReader allows users to create their own
 * file reader, with a unified interface for the parser to read string chunks.
 */

#pragma once

// std
#include <span>

namespace OpenGedcom {
    class IReader {
    public:
        virtual ~IReader() {}

        /// @brief Returns const character buffer
        ///
        /// This function should return a chunk of characters, the chunk can be any size.
        /// The chunk does not need to end in any particular place in the file, the parser will
        /// carry over what is necessary to parse the next chunk. The requirements are, characters
        /// must fit in a single char, or split, dealing with larger character sets is up to the implementation,
        /// chunks must be returned in file order, the parser relies on each chunk being contiguous within
        /// the file. The chunk should not remove any characters, such as '\n', as the parser requires
        /// them to work. The exception being characters that dont fit within a byte, they can be modified
        /// at the discretion of the implementation.
        ///
        virtual std::span<const char> GetChunk() = 0;

    };
}