// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT


#pragma once
#include <filesystem>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <unordered_multimap>

#include "GedcomViews.h"

namespace OpenGedcom {
    class Document {
    public:
        static Document ParseFile(const std::filesystem& path);

        Document();
        ~Document();

        GedcomDocument(const GedcomDocument&) = delete;
        GedcomDocument& operator=(const GedcomDocument&) = delete;

        GedcomDocument(GedcomDocument&&) noexcept;
        GedcomDocument& operator=(GedcomDocument&&) noexcept;

        IndividualView Individual(EntityID id);
        FamilyView Family(EntityID id);

        bool HasIndividual(EntityID id) const noexcept;
        bool HasFamily(EntityID id) const noexcept;

        IndividualView IndividualByExternalID(std::string_view gedcomID);
        FamilyView FamilyByExternalID(std::string_view gedcomID);

        std::vector<IndividualView> FindIndividualsByName(std::string_view given, std::string_view surname);

        EntityID CreateIndividual();
        EntityID CreateFamily();

        void LinkSpouse(EntityID family, EntityID individual);
        void LinkChild(EntityID family, EntityID child);

        void UnlinkSpouse(EntityID family, EntityID individual);
        void UnlinkChild(EntityID family, EntityID individual);

        void SaveFile(const std::filesystem& path) const;

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
        EntityID AllocateID();

    };
}