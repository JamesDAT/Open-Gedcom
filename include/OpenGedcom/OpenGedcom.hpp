// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file OpenGedcom.hpp
 * @brief Primary include into OpenGedcom
 *
 *
 * This file is the single include for projects using OpenGedcom, it will include all necessary headers,
 * and provides the Document object for Gedcom use
 */

#pragma once
#include "Internal/OpenGedcom.ipp"

#include "IReader.hpp"

#include "Internal/Registry.hpp"
#include "Internal/Storage.hpp"

// tags
#include "Tags/GedcomTags.hpp"

// views
#include "Views/GedcomViews.hpp"

// std
#include <optional>
#include <string>
#include <memory>
#include <vector>

namespace OpenGedcom {
    class Document {
    public:

        // Documents should be created through the static Parse functions
        Document(std::unique_ptr<Internal::Registry> registry, std::unique_ptr<Internal::Storage> storage);
        ~Document();

        // Prevent accidental copies, Document stores unique ownership objects
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;

        // Document can be moved
        Document(Document&&) noexcept = default;
        Document& operator=(Document&&) noexcept = default;

        /// @brief Parse Gedcom string into a new Document.
        ///
        /// ParseDOM will keep the whole Gedcom file in memory,
        /// it is extremely fast, zero copy, but has high memory usage
        ///
        /// @param[in] std::string rvalue, storage takes ownership of the string.
        /// @warning Do not pass temporary string literal, create a string object
        /// and move it in.
        /// @return New document with the parsed Gedcom data
        [[nodiscard]] static Document ParseDOM(std::string&& data);

        /// @brief Parse Gedcom string into a new Document.
        ///
        /// ParseCopy does not take ownership of the Gedcom string,
        /// instead it copies data as needed. It is slower than ParseDOM
        /// due to copies, and has high peak memory usage, but does not
        /// require the entire Gedcom file to be stored after parsing
        ///
        /// @param[in] std::string_view, zero copy view of the data
        /// @return New document with the parsed Gedcom data
        [[nodiscard]] static Document ParseCopy(std::string_view data);

        /// @brief Parse Gedcom strings into a new Document.
        ///
        /// ParseReader uses a user implemented IReader to read files.
        /// it reads the file in chunks and either creates copies, or
        /// optionally lazyLoads. In the case of lazyLoading it will keep
        /// the reader alive through the shared pointer. This method is
        /// recommended for large files, as it has the same low memory
        /// storage as ParseCopy without the peak memory usage during parsing.
        ///
        /// @param[in] User implemented IReader, optional lazyLoad flag, default false.
        /// @return New document with the parsed Gedcom data
        [[nodiscard]] static Document ParseReader(std::shared_ptr<IReader> reader, bool lazyLoad = false);
        
        [[nodiscard]] std::optional<IndiView> GetIndividual(uint32_t id);
        [[nodiscard]] std::vector<IndiView> GetIndividual(std::string_view name);

        template<Internal::GedcomTagType T>
        bool IsType(const TagView& view) {
            return m_registry->IsType<T>(*view.Get());
        }

        Internal::Registry* GetRegistry() {
            return m_registry.get();
        }

        Internal::Storage* GetStorage() {
            return m_storage.get();
        }

    private:
        // cannot be forward declared due to use in templates
        std::unique_ptr<Internal::Registry> m_registry;
        std::unique_ptr<Internal::Storage> m_storage;

    };
}

