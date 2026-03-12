// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file OpenGedcom.hpp
 * @brief Primary interface into OpenGedcom
 *
 *
 * This file is the single include for projects using OpenGedcom, it will include all necessary headers,
 * and provides the Document object for Gedcom use
 */

#pragma once

namespace OpenGedcom {

    class Document {
    public:
        Document();
        ~Document();

        // Prevent accidental copies, Document stores unique ownership objects
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;

        // Document can be moved
        Document(Document&&) noexcept = default;
        Document& operator=(Document&&) noexcept = default;

    private:

    };
}

