// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file DateView.hpp
 * @brief View into Date type tag
 */

#pragma once

#include "ViewBase.hpp"

namespace OpenGedcom {
    class DateView : public TagView {
    public:
        using TagView::TagView;

        std::string_view Date() const;
        std::optional<std::string_view> Time() const;

    private:

    };
}