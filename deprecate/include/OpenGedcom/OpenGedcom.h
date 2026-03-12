// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT


#pragma once
#include <cstdint>
#include <filesystem>

#include "GedcomViews.h"
#include "GedcomStorage.h"

namespace OpenGedcom {

    class Document {
    public:
        /// @brief Read and parse a Gedcom file into the OpenGedcom Document format.
        /// @param path 
        static Document ParseFile(const std::filesystem::path& path, bool lazyLoad = true);

        Document();
        ~Document();

        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;

        Document(Document&&) noexcept;
        Document& operator=(Document&&) noexcept;

        std::optional<IndividualView> Individual(uint32_t id);
        //FamilyView Family(EntityID id);

        //bool HasIndividual(EntityID id) const noexcept;
        //bool HasFamily(EntityID id) const noexcept;

        //IndividualView IndividualByExternalID(std::string_view gedcomID);
        //FamilyView FamilyByExternalID(std::string_view gedcomID);

        //std::vector<IndividualView> FindIndividualsByName(std::string_view given, std::string_view surname);

        //EntityID CreateIndividual();
        //EntityID CreateFamily();

        //void LinkSpouse(EntityID family, EntityID individual);
        //void LinkChild(EntityID family, EntityID child);

        //void UnlinkSpouse(EntityID family, EntityID individual);
        //void UnlinkChild(EntityID family, EntityID individual);

        //void SaveFile(const std::filesystem::path& path) const;

        GedcomStorage& Storage() { return m_storage; }
    private:

        // storage
        GedcomStorage m_storage;

    };
}