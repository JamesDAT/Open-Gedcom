// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

// note for some reason the tab space count is massive on this file because something broke in vs-code :( dont know how to fix rn

#include "OpenGedcom/GedcomViews.h"
#include "TagTraversal.h"

namespace OpenGedcom {
        std::optional<std::string_view> IndividualView::Given() const {
                if(auto nameTag = Traverse::GetChild<NameTag>(this)) {
                        if(auto given = Traverse::GetChild<GivenNamesTag>(this->Registry(), nameTag.value())) {
                                return given.value()->RawValue();
                        }
                        
                        std::string_view fullName = nameTag.value()->RawValue();
                        size_t slash = fullName.find('/'); // marks beginning of surname

                        if(slash == std::string_view::npos)
                                return fullName;

                        return fullName.substr(0, slash > 0 && fullName[slash-1] == ' ' ? slash - 1 : slash); // return fullName up to slash-1
                }
                return std::nullopt;
        }


        std::optional<std::string_view> IndividualView::Surname() const {
                if(auto nameTag = Traverse::GetChild<NameTag>(this)) {
                        if(auto surname = Traverse::GetChild<SurnameTag>(this->Registry(), nameTag.value())) {
                                return surname.value()->RawValue();
                        }
                        
                        std::string_view fullName = nameTag.value()->RawValue();
                        size_t first = fullName.find('/'); // marks beginning of surname
                        size_t second = fullName.find('/', first+1);

                        if(first == std::string_view::npos || second == std::string_view::npos)
                                return "";

                        return fullName.substr(first + 1, second - first - 1); // return area between the two '/'
                }
                return std::nullopt;
        }

        std::optional<char> IndividualView::Sex() const {
                if(auto sexTag = Traverse::GetChild<SexTag>(this)) {
                        return sexTag.value()->RawValue()[0];
                }

                return std::nullopt;
        }

        std::optional<uint32_t> IndividualView::ID() const {
                return Data()->GetId();
        }

        std::vector<OccupationView> IndividualView::Occupations() const {
                std::vector<OccupationView> occupations;

                for(auto occupation : Traverse::GetChildren<OccupationTag>(this)) {
                        OccupationView occuview{const_cast<GedcomNode*>(occupation), const_cast<TagRegistry*>(Registry())};
                        occupations.push_back(occuview);
                }

                return occupations;
        }

        std::vector<AddressView> IndividualView::Residence() const {
                std::vector<AddressView> addresses;

                if(auto residence = Traverse::GetChild<ResidenceTag>(this)) {
                        for(auto address : Traverse::GetChildren<AddressTag>(this->Registry(), residence.value())) {
                                AddressView addrview{const_cast<GedcomNode*>(address), const_cast<TagRegistry*>(Registry())};
                                addresses.push_back(addrview);
                        }
                }

                return addresses;
        }

        /// Trait system not equipped to deal with this yet, requires registry rework to get the traits of a node type, as it requires reverse type searching
        std::vector<EventView> IndividualView::Events() const {
                std::vector<EventView> events;
                auto nodes = Traverse::GetChildren(this, TagTraits::Event);

                for(auto node : nodes) {
                        EventView eventView{const_cast<GedcomNode*>(node), const_cast<TagRegistry*>(Registry())};
                        events.push_back(eventView);
                }

                return events;
        }

        void IndividualView::SetGiven(std::string_view given) {

        }

        void IndividualView::SetSurname(std::string_view surname) {

        }

        void IndividualView::SetAge(std::string_view age) {
                
        }
}