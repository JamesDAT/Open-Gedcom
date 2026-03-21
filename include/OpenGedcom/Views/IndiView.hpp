// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file IndiView.hpp
 * @brief View into Indi type tag
 */

#pragma once

#include "ViewBase.hpp"
#include <string>

namespace OpenGedcom {
    class IndiView : public TagView {
    public:
        using TagView::TagView;

        IndiView(const TagView& base) : TagView(base) {}

        //[[nodiscard]] std::optional<std::string_view> Name() const {}

        /// Use regular formatting, John Doe
        //TagView SetName(std::string firstName, std::string lastName) {}
        /// Use gedcom formatting, John /Doe/
        //TagView SetName(std::string name) {}

        //[[nodiscard]] std::optional<std::string_view> NamePrefix() const {}
        //TagView SetNamePrefix(std::string_view prefix) {}

        //[[nodiscard]] std::optional<std::string_view> GivenName() const {}
        //TagView SetGivenName(std::string given) {}

        //[[nodiscard]] std::optional<std::string_view> FirstName() const {}

        //[[nodiscard]] std::optional<std::string_view> LastName() const {}

        //[[nodiscard]] std::optional<char> Sex() const {}
        //TagView SetSex(char sex) {}

        //[[nodiscard]] std::vector<TagView> Events() const {}


    private:

    };
}