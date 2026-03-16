// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file PlaceView.hpp
 * @brief View into Plac type tag
 */

#pragma once

#include "ViewBase.hpp"

namespace OpenGedcom {
    class PlaceView : public TagView {
    public:
        using TagView::TagView;

        std::string_view Place() const;

    private:

    };
}