// Copyright (c) 2025 Your Name
// SPDX-License-Identifier: MIT

#pragma once
#include <string_view>

namespace OpenGedcom {

    // basic types
    using EntityID = uint32_t;

    enum class RecordType {
        Individual,
        Family
    };

    // forward declares
    class Document;
    class IndividualView;
    class FamilyView;

    // internal storage
    struct IndividualRecord {
        EntityID id;
    };

    struct FamilyRecord {
        EntityID id;
    };

    // name indexing
    struct NameKey {
        std::string_view surname;
        std::string_view given;

        bool operator==(const NameKey& other) const noexcept;
    };

    struct NameKeyHash {
        std::size_t operator()(const NameKey& key) const noexcept;
    };
}