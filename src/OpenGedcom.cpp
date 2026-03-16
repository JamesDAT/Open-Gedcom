// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/OpenGedcom.hpp"

#include "OpenGedcom/Views/IndiView.hpp"
#include "Parser/Parser.hpp"

namespace OpenGedcom {
    using namespace Internal;

    Document::Document(std::unique_ptr<Internal::Registry> registry, std::unique_ptr<Internal::Storage> storage) {
        m_registry = std::move(registry);
        m_storage = std::move(storage);
        
    }

    Document::~Document() {
        
    }

    Document Document::ParseDOM(std::string&& data) {
        auto registry = std::make_unique<Registry>();
        auto storage = std::make_unique<Storage>(registry.get(), std::move(data));

        Parser parser{storage.get(), registry.get(), false};
        parser.Parse(storage->GetOwnedString());

        return {std::move(registry), std::move(storage)};
    }

    Document Document::ParseCopy(std::string_view data) {
        auto registry = std::make_unique<Registry>();
        auto storage = std::make_unique<Storage>(registry.get());

        Parser parser{storage.get(), registry.get(), true};
        parser.Parse(data);

        return {std::move(registry), std::move(storage)};
    }

    Document Document::ParseReader(std::shared_ptr<IReader> reader, bool lazyLoad) {
        auto registry = std::make_unique<Registry>();
        auto storage = std::make_unique<Storage>(registry.get());

        Parser parser{storage.get(), registry.get(), true};

        return {std::move(registry), std::move(storage)};
    }

    std::optional<IndiView> Document::GetIndividual(uint32_t id) {
        for(auto& record : m_storage->Records()) {
            if(record.GetId() == id) {
                return IndiView{this, &record};
            }
        }

        return std::nullopt;
    }
}
