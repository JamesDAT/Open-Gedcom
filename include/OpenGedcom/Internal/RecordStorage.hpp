// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

/**
 * @file RecordStorage.hpp
 * @brief Data structure for storing records in a stable way
 */

#pragma once
#include "TagNode.hpp"
#include <array>
#include <cstddef>
#include <vector>

namespace OpenGedcom::Internal {
    class RecordStorage {
        class iterator;

    public:
        RecordStorage();
        ~RecordStorage();

        RecordStorage(const RecordStorage&) = delete;
        RecordStorage(RecordStorage&&) noexcept = default;

        void Reserve(size_t minElements);

        TagNode* Add(TagNode&& node);
        TagNode& At(size_t index);
        const TagNode& At(size_t index) const;
        
        size_t Size() const {
            return m_offset;
        }

        TagNode& operator[](const size_t index) {
            return At(index);
        }

        TagNode& Back() {
            return At(m_offset - 1);
        }

        TagNode& Front() {
            return At(0);
        }

        iterator begin();
        iterator end();

    private:
        static constexpr size_t CHUNK_SIZE = 512; // 16 KiB
        static constexpr size_t CHUNK_SHIFT = 9;
        static constexpr size_t CHUNK_MASK = CHUNK_SIZE - 1;


        std::vector<std::array<TagNode, CHUNK_SIZE>> m_data;
        size_t m_offset = 0;
    };

    class RecordStorage::iterator {
    public:
        using diffType = std::ptrdiff_t;
        using valType = TagNode;
        using reference = TagNode&;
        using pointer = TagNode*;
        using iteratorCategory = std::forward_iterator_tag;

        iterator(RecordStorage* owner, size_t index) 
            : m_owner(owner), m_index(index)
        {
            if (index >= owner->m_offset) {
                m_ptr = nullptr;
                m_chunkEnd = nullptr;
                return;
            }

            m_chunkIndex = index >> CHUNK_SHIFT;
            size_t offset = index & CHUNK_MASK;

            m_ptr = &owner->m_data[m_chunkIndex][offset];
            m_chunkEnd = owner->m_data[m_chunkIndex].data() + CHUNK_SIZE;
        }

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        iterator& operator++() {
            ++m_index;
            ++m_ptr;

            if (m_index >= m_owner->m_offset) {
                m_ptr = nullptr;
                return *this;
            }

            if (m_ptr == m_chunkEnd) {
                ++m_chunkIndex;
                m_ptr = m_owner->m_data[m_chunkIndex].data();
                m_chunkEnd = m_ptr + CHUNK_SIZE;
            }

            return *this;
        }

        bool operator==(const iterator& other) const {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const iterator& other) const {
            // use == overload of this type
            return !(*this == other);
        }

    private:
        RecordStorage* m_owner;
        size_t m_index;
        size_t m_chunkIndex;
        TagNode* m_ptr;
        TagNode* m_chunkEnd;
    };
}