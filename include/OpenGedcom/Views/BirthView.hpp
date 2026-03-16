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

        std::optional<DateView> GetDate() const;
        std::optional<PlaceView> GetPlace() const;

    private:

    };
}