// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/GedcomViews.h"

namespace OpenGedcom {
        std::string_view IndividualView::Given() const {

        }


        std::string_view IndividualView::Surname() const {

        }

        std::optional<std::string_view> IndividualView::Age() const {

        }

        std::optional<char> IndividualView::Sex() const {

        }

        std::optional<int> IndividualView::ID() const {

        }

        std::vector<OccupationView> IndividualView::Occupations() const {

        }

        std::vector<AddressView> IndividualView::Addresses() const {

        }

        std::vector<IndividualView> IndividualView::Children() const {

        }

        std::vector<IndividualView> IndividualView::Spouses() const {

        }

        std::vector<TagView> IndividualView::TagChildren() const {

        }

        void IndividualView::SetGiven(std::string_view given) {

        }

        void IndividualView::SetSurname(std::string_view surname) {

        }

        void IndividualView::SetAge(std::string_view age) {
            
        }
}