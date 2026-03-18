// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#include "OpenGedcom/Internal/RecordStorage.hpp"

namespace OpenGedcom::Internal {
    RecordStorage::RecordStorage() {

    }

    RecordStorage::~RecordStorage() {

    }

    void RecordStorage::Reserve(size_t minElements) {
        size_t required_chunks = (minElements + CHUNK_SIZE - 1) >> CHUNK_SHIFT;

        if (required_chunks <= m_data.size()) {
            return;
        }

        m_data.reserve(required_chunks);

        while (m_data.size() < required_chunks) {
            m_data.emplace_back();
        }
    }

    TagNode* RecordStorage::Add(TagNode&& node) {
        size_t chunkIndex = m_offset >> CHUNK_SHIFT;
        size_t offset = m_offset & CHUNK_MASK;

        if(chunkIndex >= m_data.size()) {
            m_data.emplace_back();
        }

        TagNode& slot = m_data[chunkIndex][offset];
        slot = std::move(node);

        ++m_offset;
        return &slot;
    }


    TagNode& RecordStorage::At(size_t index) {
        return m_data[ index >> CHUNK_SHIFT ][ index & CHUNK_MASK];
    }

    const TagNode& RecordStorage::At(size_t index) const {
        return m_data[ index >> CHUNK_SHIFT ][ index & CHUNK_MASK];
    }

    RecordStorage::iterator RecordStorage::begin() {
        return iterator(this, 0);
    }

    RecordStorage::iterator RecordStorage::end() {
        return iterator(this, m_offset);
    }
}