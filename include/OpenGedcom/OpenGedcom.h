// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT


#pragma once
#include <filesystem>
#include <string_view>
#include <vector>
#include <unordered_map>

#include "GedcomViews.h"
#include "GedcomObject.h"

namespace OpenGedcom {
    class Document {
    public:
        /// @brief Read and parse a Gedcom file into the OpenGedcom Document format.
        /// @param path 
        //static Document ParseFile(const std::filesystem::path& path);

        Document();
        ~Document();

        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;

        Document(Document&&) noexcept;
        Document& operator=(Document&&) noexcept;

        //IndividualView Individual(EntityID id);
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

    private:
        // storage
        std::unordered_map<EntityID, IndividualRecord> m_individuals;
        std::unordered_map<EntityID, FamilyRecord> m_families;

        // id mappings
        std::unordered_map<std::string, EntityID> m_externalToInternal;
        std::vector<std::string> m_internalToExternal;

        // name index
        std::unordered_multimap<NameKey, EntityID, NameKeyHash> m_nameIndex;

        // id
        EntityID m_nextEntityID = 1;
        //EntityID AllocateID();

    };
}