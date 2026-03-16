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

        std::optional<std::string_view> Name() const;
        std::optional<std::string_view> GivenName() const;
        std::optional<std::string_view> FirstName() const;
        std::optional<std::string_view> LastName() const;

    private:

    };
}