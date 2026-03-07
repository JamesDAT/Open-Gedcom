// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

/// Gedcom views are meant as the primary axis for interacting with the internal gedcom objects.
/// The views aim to provide mechanisms to gain views to any relavent information on a tag. For instance Age() of a INDI tag
/// Failing this views provide a fallback to gain a pointer into the node storage, so tags can be manually found

#pragma once
#include "GedcomObject.h"
#include "GedcomRegistry.h"

#include <optional>
#include <string_view>
#include <vector>

namespace OpenGedcom {
    class TagView {
    public:
        TagView(GedcomNode* tag, TagRegistry* registry)
            : m_data(tag), m_registry(registry) {}

        virtual ~TagView() = default;

        const GedcomNode& Tag() const { return *m_data; }
        GedcomNode* Data() { return m_data; };
        const GedcomNode* Data() const { return m_data; }

        TagRegistry* Registry() { return m_registry; }
        const TagRegistry* Registry() const { return m_registry; }


    protected:
        GedcomNode* m_data;
        TagRegistry* m_registry;
    };

    class DateView : public TagView {
    public:
        using TagView::TagView;
        
        std::string_view Date() const;
        std::optional<std::string_view> Time() const;

        void SetDate(std::string_view date);
        void SetTime(std::string_view time);
    };

    class OccupationView : public TagView {
    public:
        using TagView::TagView;

        std::optional<DateView> Date() const;
        std::optional<std::string_view> Place() const;

        void SetPlace(std::string_view place);
    };

    class AddressView : public TagView {
    public:
        using TagView::TagView;

        std::optional<std::string_view> County() const;
        std::optional<std::string_view> State() const;
        std::optional<std::string_view> City() const;
        std::optional<std::string_view> Address() const;

        void SetCountry(std::string_view country);
        void SetState(std::string_view state);
        void SetCity(std::string_view city);
        void SetAddress(std::string_view address);
    };

    class EventView : TagView {
    public:
        using TagView::TagView;
        
        std::optional<AddressView> Address() const;
        std::optional<DateView> Date() const;
    };

    class IndividualView : public TagView {
    public:
        using TagView::TagView;

        std::optional<std::string_view> Given() const;
        std::optional<std::string_view> Surname() const;
        std::optional<char> Sex() const;
        std::optional<uint32_t> ID() const;

        std::vector<OccupationView> Occupations() const;
        std::vector<AddressView> Residence() const;
        std::vector<EventView> Events() const;


        void SetGiven(std::string_view given);
        void SetSurname(std::string_view surname);
        void SetAge(std::string_view age);
    };

    class FamilyView {

    };
}