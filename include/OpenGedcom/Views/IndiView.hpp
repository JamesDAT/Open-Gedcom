// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file IndiView.hpp
 * @brief View into Indi type tag
 */

#pragma once

#include "ViewBase.hpp"

namespace OpenGedcom {
    class IndiView : public TagView {
    public:
        using TagView::TagView;

        [[nodiscard]] std::optional<std::string_view> Name() const;
        [[nodiscard]] std::optional<std::string_view> GivenName() const;
        [[nodiscard]] std::optional<std::string_view> FirstName() const;
        [[nodiscard]] std::optional<std::string_view> LastName() const;

        [[nodiscard]] std::optional<char> Sex() const;

        [[nodiscard]] std::vector<TagView> Events() const;

    private:

    };
}