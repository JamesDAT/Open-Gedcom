// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace OpenGedcom {
    struct Line {
        std::string text;
        uint64_t lineNo;
    };

    class LineRingBuffer {
    public:
        explicit LineRingBuffer(size_t capacity)
            : buffer_(capacity) {}

        Line& write_slot() {
            return buffer_[write_pos_ % buffer_.size()];
        }

        void commit_write() {
            ++write_pos_;
        }

        Line& read_slot() {
            return buffer_[read_pos_ % buffer_.size()];
        }

        void commit_read() {
            ++read_pos_;
        }

    private:
        std::vector<Line> buffer_;
        size_t write_pos_ = 0;
        size_t read_pos_  = 0;
    };
}