// Copyright (c) 2025 James Hayden
// SPDX-License-Identifier: MIT

/// Gedcom views are meant as the primary axis for interacting with the internal gedcom objects.
/// The views aim to provide mechanisms to gain views to any relavent information on a tag. For instance Age() of a INDI tag
/// Failing this views provide a fallback to gain a pointer into the node storage, so tags can be manually found

#pragma once
#include "GedcomObject.h"

#include <optional>
#include <string_view>
#include <vector>

namespace OpenGedcom {
    class TagView {
    public:
        TagView(GedcomNode* tag)
            : m_data(tag) {}

        ~TagView() = default;

        const GedcomNode* Tag() const;
        GedcomNode* Data();

    protected:
        GedcomNode* m_data;
    };


    class DateView : public TagView {
    public:
        std::string_view Date() const;
        std::optional<std::string_view> Time() const;

        void SetDate(std::string_view date);
        void SetTime(std::string_view time);
    };

    class OccupationView : public TagView {
    public:
        std::optional<DateView> Date() const;
        std::optional<std::string_view> Place() const;

        void SetPlace(std::string_view place);
    };

    class AddressView : public TagView {
    public:
        std::optional<std::string_view> County();
        std::optional<std::string_view> State();
        std::optional<std::string_view> City();
        std::optional<std::string_view> Address();

        void SetCountry(std::string_view country);
        void SetState(std::string_view state);
        void SetCity(std::string_view city);
        void SetAddress(std::string_view address);
    };

    class IndividualView : public TagView {
    public:
        using TagView::TagView;

        std::string_view Given() const;
        std::string_view Surname() const;
        std::optional<std::string_view> Age() const;
        std::optional<char> Sex() const;
        std::optional<int> ID() const;

        std::vector<OccupationView> Occupations() const;
        std::vector<AddressView> Addresses() const;

        std::vector<IndividualView> Children() const;
        std::vector<IndividualView> Spouses() const;

        std::vector<TagView> TagChildren() const;


        void SetGiven(std::string_view given);
        void SetSurname(std::string_view surname);
        void SetAge(std::string_view age);
    };

    class FamilyView {

    };
}