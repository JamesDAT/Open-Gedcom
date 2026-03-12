// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/OpenGedcom.hpp"

#include "Parser/Parser.hpp"

namespace OpenGedcom {
    using namespace Internal;

    Document::Document(Registry&& registry, Storage&& storage) {
        m_registry = registry;
        m_storage = storage;
    }

    Document::~Document() {
        
    }

    Document Document::ParseDOM(std::string&& data) {
        Registry registry{};
        Storage storage{};

        Parser parser{};
        parser.Parse(data);

        return {std::move(registry), std::move(storage)};
    }

    Document Document::ParseCopy(std::string_view data) {
        Registry registry{};
        Storage storage{};

        return {std::move(registry), std::move(storage)};
    }

    Document Document::ParseReader(std::shared_ptr<IReader> reader, bool lazyLoad) {
        Registry registry{};
        Storage storage{};

        return {std::move(registry), std::move(storage)};
    }
}
