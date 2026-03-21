// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file BirthView.hpp
 * @brief View into Birt type tag
 */

#pragma once

#include "OpenGedcom/Views/PlaceView.hpp"
#include "ViewBase.hpp"
#include "DateView.hpp"

namespace OpenGedcom {
    class BirthView : public TagView {
    public:
        using TagView::TagView;

        //[[nodiscard]] std::optional<DateView> GetDate() const {}
        //[[nodiscard]] std::optional<PlaceView> GetPlace() const {}

        //[[nodiscard]] std::optional<std::string_view> GetLocation() const {}

    private:

    };
}