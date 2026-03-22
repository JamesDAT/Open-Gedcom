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
#include "Internal/StringArena.hpp"
#include "Internal/Xref.hpp"

// tags
#include "Tags/GedcomTags.hpp"

// views
#include "Views/GedcomViews.hpp"

// std
#include <deque>
#include <functional>
#include <optional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string_view>

namespace OpenGedcom {
    class Document {
    public:

        // Documents should be created through the static Parse functions
        Document();
        ~Document();

        // Prevent accidental copies, Document stores unique ownership objects
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;

        // Document can be moved
        Document(Document&&) noexcept = default;
        Document& operator=(Document&&) noexcept = default;

        /// @brief Parse Gedcom string into a new Document.
        ///
        /// ParseCopy does not take ownership of the Gedcom string,
        /// instead it copies data as needed. It is slower than ParseDOM
        /// due to copies, and has high peak memory usage, but does not
        /// require the entire Gedcom file to be stored after parsing
        ///
        /// @param[in] std::string_view, zero copy view of the data
        /// @return New document with the parsed Gedcom data
        [[nodiscard]] static Document Parse(std::string_view data);

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
        
        /// @brief Get an individual from their tag id
        /// @param[in] Id of the individual, omitting the type identifier (such as 'I')
        /// @return Returns an optional individual view depending on whether an individual with
        /// the tag exists
        [[nodiscard]] std::optional<IndiView> GetIndividual(uint32_t id);

        /// @brief Get all individuals with the exact name
        ///
        /// Finds all individuals with the exact name provided. It uses the exact character
        /// sequence found in the gedcom file under the NAME tag, it does not search Given
        /// names.
        ///
        /// @param[in] Exact name format for individuals to find
        /// @return A vector of individual views
        [[nodiscard]] std::vector<IndiView> GetIndividuals(std::string_view name);

        [[nodiscard]] TagView CreateTag(std::string_view tag, TagView* parent = nullptr);

        template<GedcomTagType T>
        [[nodiscard]] TagView CreateTag(TagView* parent = nullptr) {
            return CreateTag(m_registry.GetTypeString<T>(), parent);
        }

        /// @brief Check whether the tag type matches the type provided
        ///
        /// Checks within the registry stored in the document, make sure to only
        /// use the document that provided the view, to ensure the correct registry
        /// is used
        ///
        /// @param[in] Constant reference to a tag view
        /// @return true if the type matches, false otherwise
        template<GedcomTagType T>
        bool IsType(const TagView& view) {
            return m_registry.IsType<T>(*view.Get());
        }

        bool HasTrait(const TagView& view, TagTraits trait) {
            return m_registry.HasTrait(*view.Get(), trait);
        }

        /// @brief Get the stored registry
        Internal::Registry& GetRegistry() {
            return m_registry;
        }

        [[nodiscard]] std::string GetGedcomString();

    private:
        void ConvertNodeRecursive(int level, std::string& mutString, const Internal::TagNode& node);

        // cannot be forward declared due to use in templates
        Internal::Registry m_registry{};

        // ownership storage for value and name strings
        Internal::StringArena m_values{};
        Internal::StringArena m_names{};
        
        // records are defined as level 0 tags, tags are any non level 0
        std::deque<Internal::TagNode> m_records{};
        std::deque<Internal::TagNode> m_tags{};

        // cross pointers
        std::unordered_map<XrefType, Internal::TagNode*> m_xrefs{};
        
        // initialized based off originial document, and grown when new elements are pushed
        // it is not exact and is used to reduce allocations when saving
        size_t m_documentSizeEstimate = 0; 
    };
}

